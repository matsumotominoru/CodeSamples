
// MFCDlgTemplateDefaultDlg.h : ヘッダー ファイル
//

#pragma once


// CMFCDlgTemplateDefaultDlg ダイアログ
class CMFCDlgTemplateDefaultDlg : public CDialogEx
{
// コンストラクション
public:
	CMFCDlgTemplateDefaultDlg(CWnd* pParent = nullptr);	// 標準コンストラクター

// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCDLGTEMPLATEDEFAULT_DIALOG };
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
};
