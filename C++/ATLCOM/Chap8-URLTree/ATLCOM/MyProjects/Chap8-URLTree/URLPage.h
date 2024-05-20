// URLPage.h : CURLPage の宣言

#ifndef __URLPAGE_H_
#define __URLPAGE_H_

#include "resource.h"       // メイン シンボル

EXTERN_C const CLSID CLSID_URLPage;

/////////////////////////////////////////////////////////////////////////////
// CURLPage
class ATL_NO_VTABLE CURLPage :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CURLPage, &CLSID_URLPage>,
	public IPropertyPageImpl<CURLPage>,
	public CDialogImpl<CURLPage>
{
public:
	CURLPage() 
	{
		m_dwTitleID = IDS_TITLEURLPage;
		m_dwHelpFileID = IDS_HELPFILEURLPage;
		m_dwDocStringID = IDS_DOCSTRINGURLPage;
	}

	enum {IDD = IDD_URLPAGE};

DECLARE_REGISTRY_RESOURCEID(IDR_URLPAGE)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CURLPage) 
	COM_INTERFACE_ENTRY(IPropertyPage)
END_COM_MAP()

BEGIN_MSG_MAP(CURLPage)
	CHAIN_MSG_MAP(IPropertyPageImpl<CURLPage>)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	COMMAND_HANDLER(IDC_NAME, EN_CHANGE, OnNameChange)
	COMMAND_ID_HANDLER(IDC_ADD, OnAddItem)
	COMMAND_HANDLER(IDC_VALUES, LBN_SELCHANGE, OnSelChange)
	COMMAND_ID_HANDLER(IDC_REMOVE, OnRemoveItem)

END_MSG_MAP()
// ハンドラのプロトタイプ:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	STDMETHOD(Apply)(void)
	{
		ATLTRACE(_T("CURLPage::Apply\n"));
/*
		for (UINT i = 0; i < m_nObjects; i++)
		{
			// ここで何か処理を行ってください
			// ICircCtl* pCirc;
			// m_ppUnk[i]->QueryInterface(IID_ICircCtl, (void**)&pCirc);
			// pCirc->put_Caption(CComBSTR("something special"));
			// pCirc->Release();
		}
		m_bDirty = FALSE;
*/
   USES_CONVERSION;
   CWindow wndValues(GetDlgItem(IDC_VALUES));
   int count = 0;
   int idx = wndValues.SendMessage(LB_GETCOUNT, 0, 0);

   CComVariant var;
   var.vt = VT_ARRAY | VT_BSTR;
   SAFEARRAY* psa;
   SAFEARRAYBOUND bounds = {idx, 0};
   psa = SafeArrayCreate(VT_BSTR, 1, &bounds);
   BSTR* bstrArray;
   SafeArrayAccessData(psa, (void**)&bstrArray);

   while (count < idx)
   {
      int textSize = wndValues.SendMessage(LB_GETTEXTLEN, (WPARAM)count, 0);
      LPTSTR str = new TCHAR[textSize + 1];
      wndValues.SendMessage(LB_GETTEXT, (WPARAM)count, (LPARAM)(LPCTSTR)str);
      bstrArray[count] = SysAllocString(T2OLE(str));
      delete [] str;
      count++;
   }

   SafeArrayUnaccessData(psa);
   var.parray = psa;

   CComPtr<IURLTreeView> pURL;
   m_ppUnk[0]->QueryInterface(IID_IURLTreeView, (void**)&pURL);
   pURL->put_URLs(var);

   m_bDirty = FALSE;


		return S_OK;
	}
	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam,
                     BOOL& bHandled);
	LRESULT OnNameChange(WORD wNotify, WORD wID, HWND hWnd, BOOL& bHandled);
	LRESULT OnAddItem(WORD wNotify, WORD wID, HWND hWnd, BOOL& bHandled);
	LRESULT OnSelChange(WORD wNotify, WORD wID, HWND hWnd, BOOL& bHandled);
	LRESULT OnRemoveItem(WORD wNotify, WORD wID, HWND hWnd, BOOL& bHandled);

};

#endif //__URLPAGE_H_
