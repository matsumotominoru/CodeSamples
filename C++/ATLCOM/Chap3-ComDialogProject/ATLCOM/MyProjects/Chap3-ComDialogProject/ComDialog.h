// ComDialog.h : CComDialog の宣言

#ifndef __COMDIALOG_H_
#define __COMDIALOG_H_

#include "resource.h"       // メイン シンボル
#include <atlhost.h>
#include "ComDialogProject.h"

/////////////////////////////////////////////////////////////////////////////
// CComDialog
class CComDialog : 
	public CDialogImpl<CComDialog>,					// ..ADD
	public CComObjectRootEx<CComSingleThreadModel>,	// ..ADD
	public CComCoClass<CComDialog, &CLSID_ComDialog>,// ..ADD
	public IComDialog								// ..ADD
	// public CAxDialogImpl<CComDialog>				// ..DELETE
{
public:
	CComDialog()
	{
	}

	~CComDialog()
	{
	}

	enum { IDD = IDD_COMDIALOG };

DECLARE_REGISTRY_RESOURCEID(IDR_ComDialog)	// ..ADD
DECLARE_NOT_AGGREGATABLE(CComDialog)		// ..ADD
DECLARE_CLASSFACTORY_SINGLETON(CComDialog)	// ..ADD

BEGIN_MSG_MAP(CComDialog)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	COMMAND_ID_HANDLER(IDOK, OnOK)
	COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
END_MSG_MAP()

BEGIN_COM_MAP(CComDialog)					// ..ADD
	COM_INTERFACE_ENTRY(IComDialog)			// ..ADD
END_COM_MAP()								// ..ADD

	// Called as the last step in constructing your COM object
	HRESULT FinalConstruct()
	{
		// Create the window for the dialog as soon as 
		// the object is constructed
		if (Create(NULL))
			return S_OK;
		else
			return HRESULT_FROM_WIN32(GetLastError());
	}
	
	// Called as the last step before deleting your object
	void FinalRelease()		
	{
		// Destroy the window when the object is released.
		// We don't want our window procedure to be called after
		// the object's deleted
		DestroyWindow();	
	}

// IComDialog
public:
	STDMETHOD(get_Visible)(/*[out, retval]*/ VARIANT_BOOL* pbVisible);	// We use VARIANT_BOOL for 
	STDMETHOD(put_Visible)(/*[in]*/ VARIANT_BOOL bVisible);				// compatibility with Visual Basic
	// Inline helper to minimize BOOL, bool, VARIANT_BOOL confusion
	// With VARIANT_BOOLs, VARIANT_TRUE is -1 and VARIANT_FALSE is 0.
	// With BOOL, TRUE is 1 and FALSE is 0 (bool promotions to int also follow this line)
	VARIANT_BOOL IsVisible()
	{
		// We use CWindow::IsWindowVisible() to determine if the window is visible.
		// IsWindowVisible() returns a BOOL.
		return IsWindowVisible() ? VARIANT_TRUE : VARIANT_FALSE;
	}

// ハンドラのプロトタイプ:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		return 1;  // システムにフォーカスを設定させます
	}

	LRESULT OnOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		put_Visible(VARIANT_FALSE);
		//EndDialog(wID);	// ..DELETE
		return 0;
	}

	LRESULT OnCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		// OnCancel() hanldes the Close button too
		put_Visible(VARIANT_FALSE);
		//EndDialog(wID);	// ..DELETE
		return 0;
	}
};

#endif //__COMDIALOG_H_
