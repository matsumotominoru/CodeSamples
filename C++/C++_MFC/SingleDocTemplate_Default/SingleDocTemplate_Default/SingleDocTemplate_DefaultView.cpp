
// SingleDocTemplate_DefaultView.cpp : CSingleDocTemplateDefaultView クラスの実装
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS は、プレビュー、縮小版、および検索フィルター ハンドラーを実装している ATL プロジェクトで定義でき、
// そのプロジェクトとのドキュメント コードの共有を可能にします。
#ifndef SHARED_HANDLERS
#include "SingleDocTemplate_Default.h"
#endif

#include "SingleDocTemplate_DefaultDoc.h"
#include "SingleDocTemplate_DefaultView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSingleDocTemplateDefaultView

IMPLEMENT_DYNCREATE(CSingleDocTemplateDefaultView, CView)

BEGIN_MESSAGE_MAP(CSingleDocTemplateDefaultView, CView)
	// 標準印刷コマンド
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CSingleDocTemplateDefaultView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CSingleDocTemplateDefaultView コンストラクション/デストラクション

CSingleDocTemplateDefaultView::CSingleDocTemplateDefaultView() noexcept
{
	// TODO: 構築コードをここに追加します。

}

CSingleDocTemplateDefaultView::~CSingleDocTemplateDefaultView()
{
}

BOOL CSingleDocTemplateDefaultView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: この位置で CREATESTRUCT cs を修正して Window クラスまたはスタイルを
	//  修正してください。

	return CView::PreCreateWindow(cs);
}

// CSingleDocTemplateDefaultView 描画

void CSingleDocTemplateDefaultView::OnDraw(CDC* /*pDC*/)
{
	CSingleDocTemplateDefaultDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: この場所にネイティブ データ用の描画コードを追加します。
}


// CSingleDocTemplateDefaultView の印刷


void CSingleDocTemplateDefaultView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CSingleDocTemplateDefaultView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 既定の印刷準備
	return DoPreparePrinting(pInfo);
}

void CSingleDocTemplateDefaultView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 印刷前の特別な初期化処理を追加してください。
}

void CSingleDocTemplateDefaultView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 印刷後の後処理を追加してください。
}

void CSingleDocTemplateDefaultView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CSingleDocTemplateDefaultView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CSingleDocTemplateDefaultView の診断

#ifdef _DEBUG
void CSingleDocTemplateDefaultView::AssertValid() const
{
	CView::AssertValid();
}

void CSingleDocTemplateDefaultView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSingleDocTemplateDefaultDoc* CSingleDocTemplateDefaultView::GetDocument() const // デバッグ以外のバージョンはインラインです。
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSingleDocTemplateDefaultDoc)));
	return (CSingleDocTemplateDefaultDoc*)m_pDocument;
}
#endif //_DEBUG


// CSingleDocTemplateDefaultView メッセージ ハンドラー
