
// MFCDlg_TakebashiQ_1Dlg.cpp : 実装ファイル
//

#include "pch.h"
#include "framework.h"
#include "MFCDlg_TakebashiQ_1.h"
#include "MFCDlg_TakebashiQ_1Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// アプリケーションのバージョン情報に使われる CAboutDlg ダイアログ

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

// 実装
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCDlgTakebashiQ1Dlg ダイアログ



CMFCDlgTakebashiQ1Dlg::CMFCDlgTakebashiQ1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCDLG_TAKEBASHIQ_1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCDlgTakebashiQ1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT2, edit2);
}

BEGIN_MESSAGE_MAP(CMFCDlgTakebashiQ1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMFCDlgTakebashiQ1Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCDlgTakebashiQ1Dlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CMFCDlgTakebashiQ1Dlg メッセージ ハンドラー

BOOL CMFCDlgTakebashiQ1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// "バージョン情報..." メニューをシステム メニューに追加します。

	// IDM_ABOUTBOX は、システム コマンドの範囲内になければなりません。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// このダイアログのアイコンを設定します。アプリケーションのメイン ウィンドウがダイアログでない場合、
	//  Framework は、この設定を自動的に行います。
	SetIcon(m_hIcon, TRUE);			// 大きいアイコンの設定
	SetIcon(m_hIcon, FALSE);		// 小さいアイコンの設定

	// TODO: 初期化をここに追加します。
	editCanWrite = TRUE;
	btn1 = (CButton *)GetDlgItem(IDOK);
	edit1 = (CEdit *)GetDlgItem(IDC_EDIT1);

	return TRUE;  // フォーカスをコントロールに設定した場合を除き、TRUE を返します。
}

void CMFCDlgTakebashiQ1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// ダイアログに最小化ボタンを追加する場合、アイコンを描画するための
//  下のコードが必要です。ドキュメント/ビュー モデルを使う MFC アプリケーションの場合、
//  これは、Framework によって自動的に設定されます。

void CMFCDlgTakebashiQ1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 描画のデバイス コンテキスト

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// クライアントの四角形領域内の中央
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// アイコンの描画
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ユーザーが最小化したウィンドウをドラッグしているときに表示するカーソルを取得するために、
//  システムがこの関数を呼び出します。
HCURSOR CMFCDlgTakebashiQ1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//書き込み可能ボタンをクリック
void CMFCDlgTakebashiQ1Dlg::OnBnClickedOk()
{
	if (editCanWrite) {//キャプションが書き込み可能のとき
		btn1->SetWindowText("ReadOnly");
		//EditCtrlをDisableにする
		edit1->EnableWindow(FALSE);
		edit2.EnableWindow(FALSE);
		//EditCtrlのテキスト設定
		edit1->SetWindowText("書き込みできません");
		edit2.SetWindowText("書き込みできません");

		editCanWrite = FALSE;
	}
	else {//キャプションがReadOnlyのとき
		btn1->SetWindowText("書き込み可能");
		//EditCtrlをEnableとする。
		edit1->EnableWindow(TRUE);
		edit2.EnableWindow(TRUE);
		//EditCtrlを空欄にする
		edit1->SetWindowText("");
		edit2.SetWindowText("");

		editCanWrite = TRUE;
	}
}

//コピーボタンをクリック
void CMFCDlgTakebashiQ1Dlg::OnBnClickedButton1()
{
	CString tempStr = "";
	//EditCtrlのテキストを変数strに入れる。
	edit1->GetWindowText(tempStr);
	edit2.SetWindowTextA(tempStr);
}
