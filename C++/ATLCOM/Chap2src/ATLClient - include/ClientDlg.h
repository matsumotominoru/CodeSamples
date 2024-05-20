// ClientDlg.h : CClientDlg の宣言

#ifndef __CLIENTDLG_H_
#define __CLIENTDLG_H_

#include "resource.h"       // メイン シンボル
#include <atlhost.h>

#include "..\Simple.h"	// インクルードする

/////////////////////////////////////////////////////////////////////////////
// CClientDlg
class CClientDlg : 
	public CAxDialogImpl<CClientDlg>
{
public:
	CClientDlg()
	{
	}

	~CClientDlg()
	{
	}

	enum { IDD = IDD_CLIENTDLG };

BEGIN_MSG_MAP(CClientDlg)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	COMMAND_ID_HANDLER(IDOK, OnOK)
	COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
END_MSG_MAP()
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

		ICalcEaster* p = NULL;
		HRESULT hr = CoCreateInstance(CLSID_CalcEaster, NULL, CLSCTX_ALL,
                                 IID_ICalcEaster, (void**)&p);

		if (SUCCEEDED(hr))
		{
			p->put_Year(GetDlgItemInt(IDC_YEAR));
			p->CalculateEaster();

			short Day = -1;
		    short Month = -1;

	      // We should really check the return values of the next two method calls
	      // but the logic would get quite messy
	      hr = p->get_Day(&Day);
	      hr = p->get_Month(&Month);

	      TCHAR buff[255] = {0};
	      wsprintf(buff, _T("Easter: %d/%d in %d"), Day, Month,
               GetDlgItemInt(IDC_YEAR));
	      MessageBox(buff, _T("Calculation"));

	      p->Release();
	   }
	   else
	   {
	      // Don't Release() the pointer if CoCreateInstance() failed
	      TCHAR buff[255] = {0};
	      wsprintf(buff, _T("Error: 0x%x "), hr);
	      MessageBox(buff, _T("Error") );
	   }
		return 0;
	}

	LRESULT OnCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		DestroyWindow();
		PostQuitMessage(0);
		return 0;
	}
};

#endif //__CLIENTDLG_H_
