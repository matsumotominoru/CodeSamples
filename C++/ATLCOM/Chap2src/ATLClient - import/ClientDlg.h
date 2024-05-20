// ClientDlg.h : CClientDlg �̐錾

#ifndef __CLIENTDLG_H_
#define __CLIENTDLG_H_

#include "resource.h"       // ���C�� �V���{��
#include <atlhost.h>

#import "..\Simple.tlb"		// �C���|�[�g����

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
// �n���h���̃v���g�^�C�v:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		return 1;  // �V�X�e���Ƀt�H�[�J�X��ݒ肳���܂�
	}

	LRESULT OnOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{

	    try
		{
			SIMPLELib::ICalcEasterPtr p( __uuidof(SIMPLELib::CalcEaster) );

			p->Year = GetDlgItemInt(IDC_YEAR);
			p->CalculateEaster();

			TCHAR buff[255] = {0};
			wsprintf(buff, _T("Easter: %d/%d in %d"), p->Day, p->Month, p->Year);
			MessageBox(buff, _T("Calculation"));
		}
		catch (const _com_error& Err)
		{
			TCHAR buff[255] = {0};
			wsprintf(buff, _T("Error: 0x%x "), Err.Error());
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
