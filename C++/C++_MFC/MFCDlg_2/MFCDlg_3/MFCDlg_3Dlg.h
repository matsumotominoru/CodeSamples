﻿
// MFCDlg_3Dlg.h : ヘッダー ファイル
//

#pragma once


// CMFCDlg3Dlg ダイアログ
class CMFCDlg3Dlg : public CDialogEx
{
// コンストラクション
public:
	CMFCDlg3Dlg(CWnd* pParent = nullptr);	// 標準コンストラクター

// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCDLG_3_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV サポート


// 実装
protected:
	HICON m_hIcon;

	// 生成された、メッセージ割り当て関数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CEdit m_edit1;
	CButton m_btn1;
	CEdit m_edit2;
	CButton m_btn2;
};
