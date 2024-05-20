
// MFCDlg_TakebashiQ_1Dlg.h : ヘッダー ファイル
//

#pragma once


// CMFCDlgTakebashiQ1Dlg ダイアログ
class CMFCDlgTakebashiQ1Dlg : public CDialogEx
{
// コンストラクション
public:
	CMFCDlgTakebashiQ1Dlg(CWnd* pParent = nullptr);	// 標準コンストラクター

// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCDLG_TAKEBASHIQ_1_DIALOG };
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
	afx_msg void OnBnClickedButton1();

	//エディットの状態を表すブール変数
	BOOL editCanWrite;
	//各コントロールのポインタ変数
	CButton *btn1;
	CEdit *edit1;
	CEdit edit2;
};
