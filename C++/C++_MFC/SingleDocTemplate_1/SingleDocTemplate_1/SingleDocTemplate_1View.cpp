
// SingleDocTemplate_1View.cpp : CSingleDocTemplate1View クラスの実装
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS は、プレビュー、縮小版、および検索フィルター ハンドラーを実装している ATL プロジェクトで定義でき、
// そのプロジェクトとのドキュメント コードの共有を可能にします。
#ifndef SHARED_HANDLERS
#include "SingleDocTemplate_1.h"
#endif

#include "SingleDocTemplate_1Doc.h"
#include "SingleDocTemplate_1View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSingleDocTemplate1View

IMPLEMENT_DYNCREATE(CSingleDocTemplate1View, CView)

BEGIN_MESSAGE_MAP(CSingleDocTemplate1View, CView)
	// 標準印刷コマンド
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CSingleDocTemplate1View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CSingleDocTemplate1View コンストラクション/デストラクション

CSingleDocTemplate1View::CSingleDocTemplate1View() noexcept
{
	// TODO: 構築コードをここに追加します。

}

CSingleDocTemplate1View::~CSingleDocTemplate1View()
{
}

BOOL CSingleDocTemplate1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: この位置で CREATESTRUCT cs を修正して Window クラスまたはスタイルを
	//  修正してください。

	return CView::PreCreateWindow(cs);
}

// CSingleDocTemplate1View 描画

void CSingleDocTemplate1View::OnDraw(CDC* /*pDC*/)
{
	CSingleDocTemplate1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: この場所にネイティブ データ用の描画コードを追加します。
}


// CSingleDocTemplate1View の印刷


void CSingleDocTemplate1View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CSingleDocTemplate1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 既定の印刷準備
	return DoPreparePrinting(pInfo);
}

void CSingleDocTemplate1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 印刷前の特別な初期化処理を追加してください。
}

void CSingleDocTemplate1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 印刷後の後処理を追加してください。
}

void CSingleDocTemplate1View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CSingleDocTemplate1View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CSingleDocTemplate1View の診断

#ifdef _DEBUG
void CSingleDocTemplate1View::AssertValid() const
{
	CView::AssertValid();
}

void CSingleDocTemplate1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSingleDocTemplate1Doc* CSingleDocTemplate1View::GetDocument() const // デバッグ以外のバージョンはインラインです。
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSingleDocTemplate1Doc)));
	return (CSingleDocTemplate1Doc*)m_pDocument;
}
#endif //_DEBUG


// CSingleDocTemplate1View メッセージ ハンドラー
