// SetEventDlg.h : ヘッダー ファイル
//

#if !defined(AFX_SETEVENTDLG_H__7C57C7DD_7780_11D2_AB98_0000B4725554__INCLUDED_)
#define AFX_SETEVENTDLG_H__7C57C7DD_7780_11D2_AB98_0000B4725554__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSetEventDlg ダイアログ

class CSetEventDlg : public CDialog
{
// 構築
public:
	CSetEventDlg(CWnd* pParent = NULL);	// 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CSetEventDlg)
	enum { IDD = IDD_SETEVENT_DIALOG };
		// メモ: この位置に ClassWizard によってデータ メンバが追加されます。
	//}}AFX_DATA

	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CSetEventDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV のサポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	HICON m_hIcon;

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CSetEventDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnChangeEventname();
	afx_msg void OnCreate();
	afx_msg void OnSelchangeEvents();
	afx_msg void OnGo();
	afx_msg void OnStop();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_SETEVENTDLG_H__7C57C7DD_7780_11D2_AB98_0000B4725554__INCLUDED_)
