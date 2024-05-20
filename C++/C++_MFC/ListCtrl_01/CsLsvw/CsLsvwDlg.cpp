
// CsLsvwDlg.cpp : 実装ファイル
//タイル表示を使っているため、Unicodeでないとビルドできない。

#include "pch.h"
#include "framework.h"
#include "CsLsvw.h"
#include "CsLsvwDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCsLsvwDlg ダイアログ



CCsLsvwDlg::CCsLsvwDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CSLSVW_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCsLsvwDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_listctrl);
}

BEGIN_MESSAGE_MAP(CCsLsvwDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CCsLsvwDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CCsLsvwDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CCsLsvwDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CCsLsvwDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CCsLsvwDlg::OnBnClickedButton5)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &CCsLsvwDlg::OnNMDblclkList1)
END_MESSAGE_MAP()


// CCsLsvwDlg メッセージ ハンドラー

BOOL CCsLsvwDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// このダイアログのアイコンを設定します。アプリケーションのメイン ウィンドウがダイアログでない場合、
	//  Framework は、この設定を自動的に行います。
	SetIcon(m_hIcon, TRUE);			// 大きいアイコンの設定
	SetIcon(m_hIcon, FALSE);		// 小さいアイコンの設定

	// TODO: 初期化をここに追加します。
        //----------------------------------------■ここから追加
    // ラージアイコンリストの作成

    //ビットマップIDB_BITMAP1はサイズが32のアイコンが4つある。
    m_myIconLarge.Create(IDB_BITMAP1, 32, 4, RGB(255, 255, 255));
    //大きいアイコンをリストビューに登録する。
    m_listctrl.SetImageList(&m_myIconLarge, LVSIL_NORMAL);

    // スモールアイコンリストの作成
    m_myIconSmall.Create(IDB_BITMAP2, 16, 4, RGB(255, 255, 255));
    m_listctrl.SetImageList(&m_myIconSmall, LVSIL_SMALL);


    // 詳細表示のときのコラムのヘッダの設定
    LVCOLUMN myColumn;                           // 列情報を保持するオブジェクト
    myColumn.mask = LVCF_TEXT | LVCF_WIDTH;        // タイトル、列幅を有効にする

    RECT myRect;
    m_listctrl.GetClientRect(&myRect);                // リストビューサイズを得る

    //一列目の設定
    myColumn.cx = (myRect.right - myRect.left) / 3;   // 横幅の1/3を表題にする
    myColumn.pszText = _T("プログラム名");            // 列タイトル文字列
    m_listctrl.InsertColumn(0, &myColumn);            // 0列目を確保する

    //二列目の設定
    myColumn.cx = (myRect.right - myRect.left) * 2 / 3; // 横幅の2/3を説明にする
    myColumn.pszText = _T("説明");                    // 列タイトル文字列
    m_listctrl.InsertColumn(1, &myColumn);            // 1列目を確保する


    // リストビューにアイテムを設定する
    static LVITEM myITEM;                    // 初期値をクリアするためにstaticを使用

    myITEM.mask = LVIF_TEXT | LVIF_IMAGE;      // pszTextとiImageを有効にする
    myITEM.iItem = 0;                        // 項目0
    myITEM.iSubItem = 0;                     // 列0
    myITEM.pszText = _T("ノートパッド");     // タイトル文字列
    myITEM.iImage = 0;                       // 表示させるｱｲｺﾝ番号
    m_listctrl.InsertItem(&myITEM);          // 設定する
    myITEM.mask = LVIF_TEXT;                 // pszTextを有効にする
    myITEM.iSubItem = 1;                     // 列1
    myITEM.pszText = _T("文書編集をします"); // 説明文字列
    m_listctrl.SetItem(&myITEM);             // 設定する

    myITEM.mask = LVIF_TEXT | LVIF_IMAGE;
    myITEM.iItem = 1;
    myITEM.iSubItem = 0;
    myITEM.pszText = _T("MS-DOS");
    myITEM.iImage = 1;
    m_listctrl.InsertItem(&myITEM);
    myITEM.mask = LVIF_TEXT;
    myITEM.iSubItem = 1;
    myITEM.pszText = _T("DOS窓を開きます");
    m_listctrl.SetItem(&myITEM);

    myITEM.mask = LVIF_TEXT | LVIF_IMAGE;
    myITEM.iItem = 2;
    myITEM.iSubItem = 0;
    myITEM.pszText = _T("文字コード");
    myITEM.iImage = 2;
    m_listctrl.InsertItem(&myITEM);
    myITEM.mask = LVIF_TEXT;
    myITEM.iSubItem = 1;
    myITEM.pszText = _T("文字コードを表示します");
    m_listctrl.SetItem(&myITEM);

    myITEM.mask = LVIF_TEXT | LVIF_IMAGE;
    myITEM.iItem = 3;
    myITEM.iSubItem = 0;
    myITEM.pszText = _T("電卓");
    myITEM.iImage = 3;
    m_listctrl.InsertItem(&myITEM);
    myITEM.mask = LVIF_TEXT;
    myITEM.iSubItem = 1;
    myITEM.pszText = _T("電卓計算をします");
    m_listctrl.SetItem(&myITEM);

    // LVS_EX_TWOCLICKACTIVATE指定で項目をダブルクリックしたときメッセージを送るようになる
    // LVS_EX_FULLROWSELECT指定で詳細表示のときクリックすると、行全部反転表示するようになる。
    m_listctrl.SetExtendedStyle(LVS_EX_TWOCLICKACTIVATE | LVS_EX_FULLROWSELECT);

    //タイル表示の時の設定
    // タイル表示のときにSubItemの情報を表示するように指定
    LVTILEINFO lvti;

    for (int i = 0; i < 4; i++) {
        // 引数の構造体の大きさ。構造体LVTILEINFOの最後の要素
        // フォーマット指定piColFmtはここでは使用しないので、その分の大きさを減らす
#if _WIN32_WINNT >= 0x0600 // Vista以降なら
        lvti.cbSize = sizeof(lvti) - sizeof(lvti.piColFmt);
#else
        lvti.cbSize = sizeof(lvti);
#endif
        lvti.iItem = i; // i番目のItemの設定
        lvti.cColumns = 1; // 表示するデータ桁(SubItem)の数(=puColumnsに指定する配列の要素数)
        UINT idx[] = { 1 };
        lvti.puColumns = idx;
        m_listctrl.SetTileInfo(&lvti);// どの桁(SubItem)を表示するかを配列で指定
    }

    OnBnClickedButton1();  // 大きいアイコンを最初に表示
    //----------------------------------------■ここまで追加
	return TRUE;  // フォーカスをコントロールに設定した場合を除き、TRUE を返します。
}

// ダイアログに最小化ボタンを追加する場合、アイコンを描画するための
//  下のコードが必要です。ドキュメント/ビュー モデルを使う MFC アプリケーションの場合、
//  これは、Framework によって自動的に設定されます。

void CCsLsvwDlg::OnPaint()
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
HCURSOR CCsLsvwDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCsLsvwDlg::OnBnClickedButton1()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
        //----------------------------------------■ここから追加
    m_listctrl.SetView(LV_VIEW_ICON);//大きいアイコンで表示
    //----------------------------------------■ここまで追加

}


void CCsLsvwDlg::OnBnClickedButton2()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
        //----------------------------------------■ここから追加
    m_listctrl.SetView(0);
    m_listctrl.SetView(LV_VIEW_SMALLICON);//小さいアイコンで表示
    //----------------------------------------■ここまで追加
}


void CCsLsvwDlg::OnBnClickedButton3()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
        //----------------------------------------■ここから追加
    m_listctrl.SetView(LV_VIEW_LIST);//一覧表示(リスト)
    //----------------------------------------■ここまで追加
}


void CCsLsvwDlg::OnBnClickedButton4()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
        //----------------------------------------■ここから追加
    m_listctrl.SetView(LV_VIEW_DETAILS);//詳細表示(レポート)
    //----------------------------------------■ここまで追加
}


void CCsLsvwDlg::OnBnClickedButton5()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
        //----------------------------------------■ここから追加
    m_listctrl.SetView(LV_VIEW_TILE);//タイル表示(デザイン画面での設定不可、ユニコードのみ)
    //----------------------------------------■ここまで追加
}


void CCsLsvwDlg::OnNMDblclkList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	//LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
        //----------------------------------------■ここから追加
    int i;
    HINSTANCE ret;
    //現在カーソルの下にある項目を取得する。
    i = m_listctrl.GetHotItem();
    switch (i) {
    case 0:
        ret = ShellExecute(m_hWnd, _T("open"), _T("notepad.exe"), NULL, NULL, SW_SHOW);
        if (ret <= (HINSTANCE)32) AfxMessageBox(_T("ノートパッドを起動できません."), MB_OK);
        break;
    case 1:
        ret = ShellExecute(m_hWnd, _T("open"), _T("cmd.exe"), NULL, NULL, SW_SHOW);
        if (ret <= (HINSTANCE)32) AfxMessageBox(_T("DOS窓を開くことができません."), MB_OK);
        break;
    case 2:
        ret = ShellExecute(m_hWnd, _T("open"), _T("charmap.exe"), NULL, NULL, SW_SHOW);
        if (ret <= (HINSTANCE)32) AfxMessageBox(_T("文字コード表を起動できません."), MB_OK);
        break;
    case 3:
        ret = ShellExecute(m_hWnd, _T("open"), _T("calc.exe"), NULL, NULL, SW_SHOW);
        if (ret <= (HINSTANCE)32) AfxMessageBox(_T("電卓を起動できません."), MB_OK);
        break;
    }
    //----------------------------------------■ここまで追加
	*pResult = 0;
}
