// URLPage.cpp : CURLPage のインプリメンテーション
#include "stdafx.h"
#include "URLTree.h"
#include "URLPage.h"
#include <tchar.h>

/////////////////////////////////////////////////////////////////////////////
// CURLPage

LRESULT CURLPage::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam,
                               BOOL& bHandled)
{
   USES_CONVERSION;
   CComPtr<IURLTreeView> pURL;
   m_ppUnk[0]->QueryInterface(IID_IURLTreeView,
                              reinterpret_cast<void**>(&pURL));

   CWindow wndValues(GetDlgItem(IDC_VALUES));
   CComVariant var;

   if (SUCCEEDED(pURL->get_URLs(&var)))
   {
      if (var.vt != (VT_BSTR | VT_ARRAY))
         return 0;

      BSTR* bstrArray;
      SafeArrayAccessData(var.parray, (void**)&bstrArray);

      for (UINT x = 0; 
         x < var.parray->rgsabound->cElements;
         x++)
      {
         wndValues.SendMessage(LB_ADDSTRING, 0, 
                               (LPARAM)(LPCTSTR)OLE2T(bstrArray[x]));
      }

      SafeArrayUnaccessData(var.parray);
   }

   return 0;
}

LRESULT CURLPage::OnNameChange(WORD wNotify, WORD wID, HWND hWnd,
                               BOOL& bHandled)
{
   CWindow wndName(GetDlgItem(IDC_NAME));
   CWindow bnAdd(GetDlgItem(IDC_ADD));

   bnAdd.EnableWindow(wndName.GetWindowTextLength() > 0);

   CWindow bnRemove(GetDlgItem(IDC_REMOVE));
   bnRemove.EnableWindow(FALSE);
   return 0;
}

LRESULT CURLPage::OnAddItem(WORD wNotify, WORD wID, HWND hWnd,
                            BOOL& bHandled)
{
   CWindow wndName(GetDlgItem(IDC_NAME));
   CWindow wndURL(GetDlgItem(IDC_URL));
   CWindow wndValues(GetDlgItem(IDC_VALUES));

   int nameSize = wndName.GetWindowTextLength() + 1;
   int urlSize = wndURL.GetWindowTextLength() + 1;
   LPTSTR strName = new TCHAR[nameSize + urlSize];
   wndName.GetWindowText(strName, nameSize);
   wndName.SetWindowText("");
   lstrcat(strName, _T(","));
   LPTSTR strURL = new TCHAR[urlSize];
   wndURL.GetWindowText(strURL, urlSize);
   wndURL.SetWindowText("");
   lstrcat(strName, strURL);

   wndValues.SendMessage(LB_ADDSTRING, 0, (LPARAM)(LPCTSTR)strName);
   SetDirty(TRUE);
   // Need to do the next line for VB
   m_pPageSite->OnStatusChange(
                       PROPPAGESTATUS_DIRTY | PROPPAGESTATUS_VALIDATE);

   delete [] strName;
   delete [] strURL;
   return 0;
}

LRESULT CURLPage::OnSelChange(WORD wNotify, WORD wID, HWND hWnd, 
                               BOOL& bHandled)
{
   CWindow(GetDlgItem(IDC_REMOVE)).EnableWindow(TRUE);
   return 0;
}

LRESULT CURLPage::OnRemoveItem(WORD wNotify, WORD wID, HWND hWnd,
                               BOOL& bHandled)
{
   CWindow wndName(GetDlgItem(IDC_NAME));
   CWindow wndURL(GetDlgItem(IDC_URL));
   CWindow wndValues(GetDlgItem(IDC_VALUES));

   int idx = wndValues.SendMessage(LB_GETCURSEL, 0, 0);
   if (idx == -1)
      return 0;

   int textSize = wndValues.SendMessage(LB_GETTEXTLEN, (WPARAM)idx, 0);
   LPTSTR str = new TCHAR[textSize + 1];
   wndValues.SendMessage(LB_GETTEXT, (WPARAM)idx, (LPARAM)(LPCTSTR)str);
   wndValues.SendMessage(LB_DELETESTRING, (WPARAM)idx, 0);

   LPTSTR ptr;
   ptr = _tcsstr(str, _T(","));
   if (ptr)
   {
      *ptr = 0;
      ptr++;
   }

   wndName.SetWindowText(str);
   if (ptr)
      wndURL.SetWindowText(ptr);

   SetDirty(TRUE);
   // Need to do this line for VB
   m_pPageSite->OnStatusChange(
                             PROPPAGESTATUS_DIRTY | PROPPAGESTATUS_VALIDATE);

   delete [] str;
   return 0;
}
