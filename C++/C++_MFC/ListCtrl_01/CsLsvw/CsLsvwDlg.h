
// CsLsvwDlg.h : ヘッダー ファイル
//

#pragma once


// CCsLsvwDlg ダイアログ
class CCsLsvwDlg : public CDialogEx
{
// コンストラクション
public:
	CCsLsvwDlg(CWnd* pParent = nullptr);	// 標準コンストラクター

// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CSLSVW_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV サポート


// 実装
protected:
	HICON m_hIcon;

	// 生成された、メッセージ割り当て関数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_listctrl;
	CImageList m_myIconLarge;//リストビューに表示させる大きいアイコン
	CImageList m_myIconSmall;//リストビューに表示させる小さいアイコン
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnNMDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);//リストコントロールをダブルクリック
};
