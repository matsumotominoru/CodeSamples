// SetEventDlg.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "SetEvent.h"
#include "SetEventDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetEventDlg ダイアログ

CSetEventDlg::CSetEventDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSetEventDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSetEventDlg)
		// メモ: この位置に ClassWizard によってメンバの初期化が追加されます。
	//}}AFX_DATA_INIT
	// メモ: LoadIcon は Win32 の DestroyIcon のサブシーケンスを要求しません。
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSetEventDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetEventDlg)
		// メモ: この場所には ClassWizard によって DDX と DDV の呼び出しが追加されます。
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSetEventDlg, CDialog)
	//{{AFX_MSG_MAP(CSetEventDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_EVENTNAME, OnChangeEventname)
	ON_BN_CLICKED(IDC_CREATE, OnCreate)
	ON_LBN_SELCHANGE(IDC_EVENTS, OnSelchangeEvents)
	ON_BN_CLICKED(IDC_GO, OnGo)
	ON_BN_CLICKED(IDC_STOP, OnStop)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSetEventDlg メッセージ ハンドラ

BOOL CSetEventDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// このダイアログ用のアイコンを設定します。フレームワークはアプリケーションのメイン
	// ウィンドウがダイアログでない時は自動的に設定しません。
	SetIcon(m_hIcon, TRUE);			// 大きいアイコンを設定
	SetIcon(m_hIcon, FALSE);		// 小さいアイコンを設定
	
	// TODO: 特別な初期化を行う時はこの場所に追加してください。
	
	return TRUE;  // TRUE を返すとコントロールに設定したフォーカスは失われません。
}

// もしダイアログボックスに最小化ボタンを追加するならば、アイコンを描画する
// コードを以下に記述する必要があります。MFC アプリケーションは document/view
// モデルを使っているので、この処理はフレームワークにより自動的に処理されます。

void CSetEventDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 描画用のデバイス コンテキスト

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// クライアントの矩形領域内の中央
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// アイコンを描画します。
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// システムは、ユーザーが最小化ウィンドウをドラッグしている間、
// カーソルを表示するためにここを呼び出します。
HCURSOR CSetEventDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CSetEventDlg::OnChangeEventname() 
{
	// TODO: これが RICHEDIT コントロールの場合、コントロールは、 lParam マスク
	// 内での論理和の ENM_CHANGE フラグ付きで CRichEditCrtl().SetEventMask()
	// メッセージをコントロールへ送るために CDialog::OnInitDialog() 関数をオーバー
	// ライドしない限りこの通知を送りません。
	
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
   CButton* pButton = (CButton*)GetDlgItem(IDC_CREATE);
   ASSERT(pButton);
   CWnd* pEdit = GetDlgItem(IDC_EVENTNAME);
   ASSERT(pEdit);
   CString strEvent;
   pEdit->GetWindowText(strEvent);
   pButton->EnableWindow(!strEvent.IsEmpty());
	
}

void CSetEventDlg::OnCreate() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
   CListBox* pList = (CListBox*)GetDlgItem(IDC_EVENTS);
   ASSERT(pList);
   CWnd* pEdit = GetDlgItem(IDC_EVENTNAME);
   ASSERT(pEdit);

   CString strEvent;
   pEdit->GetWindowText(strEvent);

   if (LB_ERR == pList->FindString(0, strEvent))
   {
      // Does not exist so we can add it
      HANDLE hEvent = CreateEvent(NULL, true, false, strEvent);

      if (hEvent)
      {
         int pos = pList->AddString(strEvent);
         pList->SetItemData(pos, (DWORD)hEvent);
         pList->SetCurSel(pos);
         OnSelchangeEvents();
      }
   }
	
}

void CSetEventDlg::OnSelchangeEvents() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
   CListBox* pList = (CListBox*)GetDlgItem(IDC_EVENTS);
   ASSERT(pList);

   CStatic* pIcon = (CStatic*)GetDlgItem(IDC_STATUS);
   ASSERT(pIcon);

   HANDLE hEvent = (HANDLE)pList->GetItemData(pList->GetCurSel());
   HICON hIcon;

   // Get the status of the event
   if (WAIT_OBJECT_0 == WaitForSingleObject(hEvent,0))
   {
      // Event is set
      hIcon = AfxGetApp()->LoadIcon(IDI_GO);
      CButton* pButton = (CButton*)GetDlgItem(IDC_GO);
      ASSERT(pButton);
      pButton->SetCheck(1);
      pButton = (CButton*)GetDlgItem(IDC_STOP);
      ASSERT(pButton);
      pButton->SetCheck(0);
   }
   else
   {
      // Event is not set
      hIcon = AfxGetApp()->LoadIcon(IDI_STOP);
      CButton* pButton = (CButton*)GetDlgItem(IDC_STOP);
      ASSERT(pButton);
      pButton->SetCheck(1);
      pButton = (CButton*)GetDlgItem(IDC_GO);
      ASSERT(pButton);
      pButton->SetCheck(0);
   }

   pIcon->SetIcon(hIcon);
	
}

void CSetEventDlg::OnGo() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
   CListBox* pList = (CListBox*)GetDlgItem(IDC_EVENTS);
   ASSERT(pList);

   CStatic* pIcon = (CStatic*)GetDlgItem(IDC_STATUS);
   ASSERT(pIcon);

   HANDLE hEvent = (HANDLE)pList->GetItemData(pList->GetCurSel());
   SetEvent(hEvent);

   HICON hIcon = AfxGetApp()->LoadIcon(IDI_GO);
   pIcon->SetIcon(hIcon);

}

void CSetEventDlg::OnStop() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
   CListBox* pList = (CListBox*)GetDlgItem(IDC_EVENTS);
   ASSERT(pList);

   CStatic* pIcon = (CStatic*)GetDlgItem(IDC_STATUS);
   ASSERT(pIcon);

   HANDLE hEvent = (HANDLE)pList->GetItemData(pList->GetCurSel());
   ResetEvent(hEvent);

   HICON hIcon = AfxGetApp()->LoadIcon(IDI_STOP);
   pIcon->SetIcon(hIcon);
	
}

void CSetEventDlg::OnClose() 
{
	// TODO: この位置にメッセージ ハンドラ用のコードを追加するかまたはデフォルトの処理を呼び出してください
   // Release all the event objects
   CListBox* pList = (CListBox*)GetDlgItem(IDC_EVENTS);
   ASSERT(pList);

   int count = pList->GetCount();
   count--;

   while (count>=0)
   {
      HANDLE hEvent = (HANDLE)pList->GetItemData(count--);
      CloseHandle(hEvent);
   }
   CDialog::OnClose();
	
	CDialog::OnClose();
}
