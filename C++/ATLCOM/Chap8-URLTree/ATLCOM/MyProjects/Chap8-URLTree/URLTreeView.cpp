// URLTreeView.cpp : CURLTreeView のインプリメンテーション

#include "stdafx.h"
#include "URLTree.h"
#include "URLTreeView.h"
#include <wchar.h>
#include <initguid.h>
#include <exDisp.h>

#pragma comment(lib, "comctl32.lib")

/////////////////////////////////////////////////////////////////////////////
// CURLTreeView
/*
CURLTreeView::CURLTreeView() :	
	m_ctlSysTreeView32(_T("SysTreeView32"), this, 1),
	m_ctlEdit(_T("EDIT"), this, 2)
{
	m_tmHeight = 0;
	m_bWindowOnly = TRUE;
}
*/
LRESULT CURLTreeView::OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	RECT rc;
	GetWindowRect(&rc);
	rc.right -= rc.left;
	rc.bottom -= rc.top;
	rc.top = rc.left = 0;
	rc.bottom -= m_tmHeight;
	InitCommonControls();
//		m_ctlSysTreeView32.Create(m_hWnd, rc);
    m_ctlSysTreeView32.Create(m_hWnd, rc, NULL, 
                     WS_CHILD | WS_VISIBLE | WS_BORDER |
                     TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS);

   rc.top = rc.bottom;
	rc.bottom = m_tmHeight;
	m_ctlEdit.Create(m_hWnd, rc, NULL,
                    WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL);
   HBITMAP hBitmap;
   m_hImageList = ImageList_Create(16, 16, ILC_COLOR, 2, 10);
   hBitmap = LoadBitmap(_Module.GetResourceInstance(),
                        MAKEINTRESOURCE(IDB_IMAGE));
   m_iImage = ImageList_Add(m_hImageList, hBitmap,(HBITMAP)0);
   DeleteObject(hBitmap);
   hBitmap = LoadBitmap(_Module.GetResourceInstance(),
                        MAKEINTRESOURCE(IDB_SELECT));
   m_iSelect = ImageList_Add(m_hImageList, hBitmap,(HBITMAP)0);
   DeleteObject(hBitmap);
   TreeView_SetImageList(m_ctlSysTreeView32.m_hWnd,
                         m_hImageList, TVSIL_NORMAL);

   FillTree();

		return 0;
}

HRESULT CURLTreeView::OnDraw(ATL_DRAWINFO& di)
{
   int caps = GetDeviceCaps(di.hdcDraw, TECHNOLOGY);
   if (caps != DT_RASDISPLAY)
   {
      RECT& rc = *(RECT*)di.prcBounds;
      Rectangle(di.hdcDraw, rc.left, rc.top, rc.right, rc.bottom);
      int len = m_ctlEdit.GetWindowTextLength();
      LPTSTR str = new TCHAR[len + 1];
      m_ctlEdit.GetWindowText(str, len);

      SIZE size;
      ::GetTextExtentPoint32(di.hdcDraw, str, len, &size);
      if (size.cx > (rc.right - rc.left))
         size.cx = rc.left;
      else
         size.cx = (rc.left + rc.right - size.cx) / 2;

      if (size.cy > (rc.bottom - rc.top))
         size.cy = rc.top;
      else
         size.cy = (rc.top + rc.bottom - size.cy) / 2;

      ExtTextOut(di.hdcDraw, size.cx, size.cy, ETO_CLIPPED, &rc, 
         str, lstrlen(str), NULL);

      delete [] str;
   }
   return S_OK;
}


STDMETHODIMP CURLTreeView::SetObjectRects(LPCRECT prcPos,LPCRECT prcClip)
//STDMETHOD(SetObjectRects)(LPCRECT prcPos,LPCRECT prcClip)
{
		IOleInPlaceObjectWindowlessImpl<CURLTreeView>::SetObjectRects(prcPos, prcClip);
		int cx, cy;
		cx = prcPos->right - prcPos->left;
		cy = prcPos->bottom - prcPos->top;
	   cy -= m_tmHeight;
		::SetWindowPos(m_ctlSysTreeView32.m_hWnd, NULL, 0,
			0, cx, cy, SWP_NOZORDER | SWP_NOACTIVATE);
	   ::SetWindowPos(m_ctlEdit.m_hWnd, NULL, 0,
       cy, cx, m_tmHeight, SWP_NOZORDER | SWP_NOACTIVATE);

		return S_OK;
}

STDMETHODIMP CURLTreeView::get_URLs(VARIANT *pVal)
{
	// TODO: この位置にインプリメント用のコードを追加してください
   VariantInit(pVal);
   pVal->vt = VT_ARRAY | VT_BSTR;
   SAFEARRAY* psa;
   SAFEARRAYBOUND bounds = {m_URLs.size(), 0};
   psa = SafeArrayCreate(VT_BSTR, 1, &bounds);

   BSTR* bstrArray;
   SafeArrayAccessData(psa, (void**)&bstrArray);
   std::vector<CComBSTR>::iterator it;
   int i = 0;
   for (it = m_URLs.begin(); it != m_URLs.end(); it++, i++)
   {
      bstrArray[i] = (*it).Copy();
   }   
   SafeArrayUnaccessData(psa);
   pVal->parray = psa;

	return S_OK;
}

STDMETHODIMP CURLTreeView::put_URLs(VARIANT newVal)
{
	// TODO: この位置にインプリメント用のコードを追加してください
   if (newVal.vt != (VT_BSTR | VT_ARRAY))
      return E_INVALIDARG;

   m_URLs.clear();
   BSTR* bstrArray;
   SafeArrayAccessData(newVal.parray, (void**)&bstrArray);

   for (int x = 0; 
      x < newVal.parray->rgsabound->cElements; 
      x++)
   {
      m_URLs.push_back(CComBSTR(bstrArray[x]));
   }

   SafeArrayUnaccessData(newVal.parray);
   FillTree();
   SetDirty(TRUE);

	return S_OK;
}

LRESULT CURLTreeView::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam,
                             BOOL& bHandled)
{
   if (m_tmHeight == 0)
   {
      HDC hdc = m_ctlEdit.GetDC();
      TEXTMETRIC tm;
      ::GetTextMetrics(hdc, &tm);
      ReleaseDC(hdc);
      m_tmHeight = tm.tmHeight;
   }
   WORD nWidth = LOWORD(lParam);
   WORD nHeight = HIWORD(lParam);
   nHeight -= m_tmHeight;
   ::SetWindowPos(m_ctlSysTreeView32.m_hWnd,
      NULL, 0, 0, nWidth, nHeight, 
      SWP_NOZORDER | SWP_NOACTIVATE);
   ::SetWindowPos(m_ctlEdit.m_hWnd, NULL, 0,
      nHeight, nWidth, m_tmHeight,
      SWP_NOZORDER | SWP_NOACTIVATE);
   return 0;
}

void CURLTreeView::FinalRelease()
{
   ImageList_Destroy(m_hImageList);
}

void CURLTreeView::FillTree()
{
   TreeView_DeleteAllItems(m_ctlSysTreeView32.m_hWnd);

   std::vector<CComBSTR>::iterator it;
   HTREEITEM hRoot = TreeView_GetRoot(m_ctlSysTreeView32.m_hWnd);
   for (it = m_URLs.begin(); it < m_URLs.end(); it++)
   {
      LPWSTR strBranch =  new WCHAR[(*it).Length() + 1];
      LPWSTR strURL;
      
      wcscpy(strBranch, (*it).m_str);

      if ((strURL = wcschr(strBranch, L',')) != NULL)
      {
         *strURL = 0;
         strURL++;
         TVAddItem(hRoot, strBranch, strURL, m_iImage, m_iSelect);
      }
      delete [] strBranch;
   }
   m_ctlEdit.SetWindowText((LPCTSTR)_T(""));
}
void CURLTreeView::TVAddItem(HTREEITEM hParent, LPWSTR strBranch,
                             LPWSTR strURL, int iImage, int iSelect)
{
   USES_CONVERSION;

   // Get a pointer to the first forward slash in the branch string
   LPWSTR ptr = wcschr(strBranch, L'/');

   // If the ptr is NULL, there are no forward slashes, so the contents
   // of strBranch must be the final item to add.
   // Once that's done, we can return from the function
   if (ptr == NULL)
   {
      // End of the string, add the item!
      TVAddItemCore(hParent, strBranch, strURL, iImage, iSelect);
      return;
   }

   // Create a string with the first part of the branch
   // and ensure that it's null-terminated
   LPWSTR strParent = new WCHAR[1 + ptr - strBranch];
   wcsncpy(strParent, strBranch, ptr - strBranch);
   strParent[ptr - strBranch] = 0;

   // Find child with the name contained in strParent
   HTREEITEM hItem;
   hItem = TreeView_GetChild(m_ctlSysTreeView32.m_hWnd, hParent);

   if (hItem == NULL)
   {
      // If there are no children, add the new item here
      hItem = TVAddItemCore(hParent, strParent, NULL, iImage, iSelect);
   }

   // Now loop through all the children and see 
   // if we can find the item already in the tree
   LPTSTR strCmp = new TCHAR[m_cbMaxSize];
   while (hItem)
   {
      TVITEM thisItem;
      thisItem.mask = TVIF_HANDLE | TVIF_TEXT;
      thisItem.pszText = strCmp;
      thisItem.cchTextMax = m_cbMaxSize;
      thisItem.hItem = hItem;

      TreeView_GetItem(m_ctlSysTreeView32.m_hWnd, &thisItem);
      if (lstrcmp(W2T(strParent), strCmp) == 0)
      {
         // Here we've found the item, so we call TVAddItem() recursively
         // with the handle of the item and the latest position in the branch
         TVAddItem(hItem, ptr + 1, strURL, iImage, iSelect);
         break;
      }
      else
      {
         HTREEITEM nextItem =
                TreeView_GetNextSibling(m_ctlSysTreeView32.m_hWnd, hItem);
         if (nextItem == NULL)
         {
            // If we get here, the item isn't there so we need to add it,
            // then we can call TVAddItem() recursively
            HTREEITEM hNewItem =
                  TVAddItemCore(hParent, strParent, NULL, iImage, iSelect);
            TVAddItem(hNewItem, ptr + 1, strURL, iImage, iSelect);
            break;
         }
         else
         {
            hItem = nextItem;
         }
      }
   } // while (hItem)

   delete [] strParent;
   delete [] strCmp;
}
HTREEITEM CURLTreeView::TVAddItemCore(HTREEITEM hParent, LPWSTR strItem,
                             LPWSTR strURL, int iImage, int iSelect)
{
   USES_CONVERSION;
   TVITEM tvi;
   tvi.mask = TVIF_TEXT;
   tvi.pszText = W2T(strItem);

   // Update the max size member
   // This member is used to create strings large
   // enough to hold the text for any of the items
   int cbSize = wcslen(strItem) + 1;
   if (cbSize > m_cbMaxSize)
      m_cbMaxSize = cbSize;

   if (strURL)
   {
      tvi.mask |= TVIF_PARAM;
      cbSize = wcslen(strURL) + 1;
      LPTSTR newStr = new TCHAR[cbSize];
      lstrcpy(newStr, W2T(strURL));
      tvi.lParam = (LPARAM)newStr;
   }

   if (iImage != -1)
   {
      tvi.mask |= TVIF_IMAGE;
      tvi.iImage = iImage;
   }

   if (iSelect != -1)
   {
      tvi.mask |= TVIF_SELECTEDIMAGE;
      tvi.iSelectedImage = iSelect;
   }

   TVINSERTSTRUCT tvins;
   tvins.item = tvi;
   tvins.hInsertAfter = TVI_LAST;
   tvins.hParent = hParent;

   return TreeView_InsertItem(m_ctlSysTreeView32.m_hWnd, &tvins);
}

LRESULT CURLTreeView::OnDeleteItem(int idCtrl, LPNMHDR pnmh, BOOL& bHandled)
{
   NMTREEVIEW* pnmtv = (NMTREEVIEW*) pnmh;
   if (pnmtv->itemOld.lParam != NULL)
      delete [] (LPTSTR)pnmtv->itemOld.lParam;
   return 0;
}

LRESULT CURLTreeView::OnSelChanged(int idCtrl, LPNMHDR pnmh, BOOL& bHandled)
{
   NMTREEVIEW* pnmtv = (NMTREEVIEW*) pnmh;
   TVITEM tvi = pnmtv->itemNew;
   tvi.mask = TVIF_HANDLE | TVIF_PARAM;

   if (!TreeView_GetItem(m_ctlSysTreeView32.m_hWnd, &tvi))
      return 0;

   m_ctlEdit.SetWindowText((LPCTSTR)tvi.lParam);

   return 0;
}

LRESULT CURLTreeView::OnLButtonDblClk(
   UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
   TVITEM tvi;
   tvi.hItem = TreeView_GetSelection(m_ctlSysTreeView32.m_hWnd);
   LPTSTR str = new TCHAR[m_cbMaxSize];
   tvi.mask = TVIF_TEXT | TVIF_HANDLE | TVIF_PARAM;
   tvi.pszText = str;
   tvi.cchTextMax = m_cbMaxSize;

   if (!TreeView_GetItem(m_ctlSysTreeView32.m_hWnd, &tvi))
   {
      delete [] str;
      return 0;
   }

   m_ctlEdit.SetWindowText((LPCTSTR)tvi.lParam);

   if (lstrlen((LPTSTR)tvi.lParam) > 0)
   {
      // Create browser object
      HRESULT hr;
      CComPtr<IWebBrowserApp> pNav;
      hr = CoCreateInstance(
         CLSID_InternetExplorer, NULL,
         CLSCTX_ALL, IID_IWebBrowserApp,
         reinterpret_cast<void**>(&pNav));
      if (SUCCEEDED(hr))
      {
         CComVariant varZero(0);
         CComVariant varNull("");
         hr = pNav->put_Visible(true);
         hr = pNav->Navigate(
            CComBSTR((LPCTSTR)tvi.lParam),
            &varZero, &varNull, &varNull,
            &varNull);
      }
   }

   delete [] str;

   return 0;
}
STDMETHODIMP CURLTreeView::Save(LPPROPERTYBAG pPropBag, BOOL fClearDirty,
                                BOOL fSaveAllProperties)
{
   // First say how many items
   CComVariant var = (long)m_URLs.size();
   HRESULT hr = pPropBag->Write(L"noItems", &var);
   if (FAILED(hr))
      return hr;

   short item = 0;
   OLECHAR strParam[8];
   std::vector<CComBSTR>::iterator it;
   for (it = m_URLs.begin(); it < m_URLs.end(); it++)
   {
      item++;
      swprintf(strParam, L"Item%d", item);
      var = (*it);
      hr = pPropBag->Write(strParam, &var);
      if (FAILED(hr))
         return hr;
   }
   return IPersistPropertyBagImpl<CURLTreeView>::Save(
                                  pPropBag, fClearDirty, fSaveAllProperties);
}

STDMETHODIMP CURLTreeView::Load(LPPROPERTYBAG pPropBag, LPERRORLOG pErrorLog)
{
   CComVariant var;
   HRESULT hr;
   var.vt = VT_I4;
   hr = pPropBag->Read(L"noItems", &var, pErrorLog);
   if (FAILED(hr))
      return hr;
   if (var.vt != VT_I4)
      return E_INVALIDARG;

   long items = var.iVal;
   var.Clear();

   OLECHAR strParam[8];
   for (long idx = 1; idx <= items; idx++)
   {
      swprintf(strParam, L"Item%d", idx);
      hr = pPropBag->Read(strParam, &var, pErrorLog);
      if (FAILED(hr))
         return hr;
      if (var.vt == VT_BSTR)
         m_URLs.push_back(CComBSTR(var.bstrVal));
      var.Clear();
   }
   return IPersistPropertyBagImpl<CURLTreeView>::Load(pPropBag, pErrorLog);
}
STDMETHODIMP CURLTreeView::SetInterfaceSafetyOptions(
   REFIID riid, DWORD dwSupportedOptions, DWORD dwEnabledOptions)
{
   if (riid == IID_IPersistPropertyBag)
   {
      if (dwEnabledOptions != INTERFACESAFE_FOR_UNTRUSTED_DATA)
         return E_FAIL;
      return S_OK;
   }
//   return IObjectSafetyImpl<CURLTreeView>::SetInterfaceSafetyOptions(
//                                riid, dwSupportedOptions, dwEnabledOptions);
   return IObjectSafetyImpl<CURLTreeView, 
	   INTERFACESAFE_FOR_UNTRUSTED_DATA>::SetInterfaceSafetyOptions(
                         riid, dwSupportedOptions, dwEnabledOptions);

}
STDMETHODIMP CURLTreeView::Save(LPSTREAM pStm, BOOL fClearDirty)
{
   // Add all strings together and serialize
   CComBSTR bstr = "";
   std::vector<CComBSTR>::iterator it;
   for (it = m_URLs.begin(); it < m_URLs.end(); it++)
   {
      if (it != m_URLs.begin())
         bstr.Append(L"|");
      bstr += (*it);
   }

   bstr.WriteToStream(pStm);
   m_bRequiresSave = FALSE;
   return IPersistStreamInitImpl<CURLTreeView>::Save(pStm, fClearDirty);
}

STDMETHODIMP CURLTreeView::Load(LPSTREAM pStm)
{
   m_URLs.clear();
   CComBSTR bstr;
   bstr.ReadFromStream(pStm);
   LPOLESTR ptr = bstr;
   LPOLESTR str = ptr;
   while (ptr)
   {
      ptr = wcschr(str, L'|');
      if (ptr)
      {
         *ptr = 0;
         ptr++;
      }

      CComBSTR newStr;
      newStr = str;
      m_URLs.push_back(str);
      str = ptr;
   }

   return IPersistStreamInitImpl<CURLTreeView>::Load(pStm);
}
