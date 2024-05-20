
// SingleDoc_4View.cpp : CSingleDoc4View クラスの実装
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS は、プレビュー、縮小版、および検索フィルター ハンドラーを実装している ATL プロジェクトで定義でき、
// そのプロジェクトとのドキュメント コードの共有を可能にします。
#ifndef SHARED_HANDLERS
#include "SingleDoc_4.h"
#endif

#include "SingleDoc_4Doc.h"
#include "SingleDoc_4View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSingleDoc4View

IMPLEMENT_DYNCREATE(CSingleDoc4View, CView)

BEGIN_MESSAGE_MAP(CSingleDoc4View, CView)
	// 標準印刷コマンド
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CSingleDoc4View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// CSingleDoc4View コンストラクション/デストラクション

CSingleDoc4View::CSingleDoc4View() noexcept
{
	// TODO: 構築コードをここに追加します。

}

CSingleDoc4View::~CSingleDoc4View()
{
}

BOOL CSingleDoc4View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: この位置で CREATESTRUCT cs を修正して Window クラスまたはスタイルを
	//  修正してください。

	return CView::PreCreateWindow(cs);
}

// CSingleDoc4View 描画

void CSingleDoc4View::OnDraw(CDC* pDC)
{
	CSingleDoc4Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: この場所にネイティブ データ用の描画コードを追加します。
	static int counter = 1;//■追加

	if (counter % 2 == 1) {
		pDC->TextOut(0, 0, "おはよう");
		counter++;
	}
	else if (counter % 2 == 0) {
		pDC->TextOut(0, 0, "こんにちは");
		counter++;
		//■追加終
	}
}


// CSingleDoc4View の印刷


void CSingleDoc4View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CSingleDoc4View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 既定の印刷準備
	return DoPreparePrinting(pInfo);
}

void CSingleDoc4View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 印刷前の特別な初期化処理を追加してください。
}

void CSingleDoc4View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 印刷後の後処理を追加してください。
}

void CSingleDoc4View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CSingleDoc4View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CSingleDoc4View の診断

#ifdef _DEBUG
void CSingleDoc4View::AssertValid() const
{
	CView::AssertValid();
}

void CSingleDoc4View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSingleDoc4Doc* CSingleDoc4View::GetDocument() const // デバッグ以外のバージョンはインラインです。
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSingleDoc4Doc)));
	return (CSingleDoc4Doc*)m_pDocument;
}
#endif //_DEBUG


// CSingleDoc4View メッセージ ハンドラー


void CSingleDoc4View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ここにメッセージ ハンドラー コードを追加するか、既定の処理を呼び出します。
	Invalidate();//■追加 クライアント領域を無効化します。その直後、OnDraw関数が呼び出されます。
	CView::OnLButtonDown(nFlags, point);
}
