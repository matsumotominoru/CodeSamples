
// MFCApplication1Dlg.cpp : 実装ファイル

#include "pch.h"
#include "framework.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//■追加 ダイアログIDD_DIALOG1
class CAddDlg : public CDialogEx
{
public:
	CAddDlg();

	// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1};
#endif

protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV サポート

// 実装
protected:
	DECLARE_MESSAGE_MAP()
public:
};

CAddDlg::CAddDlg() : CDialogEx(IDD_DIALOG1)
{
}

void CAddDlg::DoDataExchange(CDataExchange *pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAddDlg, CDialogEx)
END_MESSAGE_MAP()


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
public:
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


// CMFCApplication1Dlg ダイアログ
CMFCApplication1Dlg::CMFCApplication1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCApplication1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


BOOL CMFCApplication1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//①0のときエラーメッセージを出してプログラムを停止する。0でないときは何もしない。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);//システムメニュー項目IDが16の倍数でないときプログラムを停止
	ASSERT(IDM_ABOUTBOX < 0xF000);//システムメニューIDが61440以上のときプログラムを停止
	ASSERT((IDM_DIALOG1 & 0xFFF0) == IDM_DIALOG1);
	ASSERT(IDM_DIALOG1 < 0xF000);
	ASSERT((IDM_TEST & 0xFFF0) == IDM_TEST);
	ASSERT(IDM_TEST < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		CString strAboutMenu_2;

		//④リソースのString Tableの項目を読み取る。
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);//読み込めなかったときはプログラムを停止
		bNameValid = strAboutMenu_2.LoadString(IDS_DIALOG1);
		ASSERT(bNameValid);

		//②システムメニューの項目を追加
		if (!strAboutMenu.IsEmpty())
		{
			//第一引数は追加する項目の種類、第二引数はシステムメニュー項目ID、第三引数は文字列
			pSysMenu->AppendMenu(MF_SEPARATOR);//仕切りを追加
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);//文字列を追加。
		}
		if (!strAboutMenu_2.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_DIALOG1, strAboutMenu_2);
		}
		pSysMenu->AppendMenu(MF_SEPARATOR);
		pSysMenu->AppendMenu(MF_STRING, IDM_TEST, _T("テスト"));

	}

	SetIcon(m_hIcon, TRUE);			// 大きいアイコンの設定
	SetIcon(m_hIcon, FALSE);		// 小さいアイコンの設定

	return TRUE;  // フォーカスをコントロールに設定した場合を除き、TRUE を返します。
}

//システムメニューの項目をクリックしたとき
void CMFCApplication1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	CString str = _T("");
	str.Format(_T("%d\n"), nID);
	TRACE(str);

	//③システムメニューの追加項目を記述
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
		TRACE("A\n");
	}
	else if ((nID & 0xFFF0) == IDM_DIALOG1) {
		CAddDlg dlgAdd;
		dlgAdd.DoModal();
		TRACE("B\n");
	}
	else if ((nID & 0xFFF0) == IDM_TEST) {
		AfxMessageBox(_T("テスト\n"));
		TRACE("C\n");
	}

	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
		TRACE("Z\n");
	}
}

void CMFCApplication1Dlg::OnPaint()
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

HCURSOR CMFCApplication1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
