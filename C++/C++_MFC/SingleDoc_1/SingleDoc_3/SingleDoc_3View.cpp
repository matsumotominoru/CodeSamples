
// SingleDoc_3View.cpp : CSingleDoc3View クラスの実装
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS は、プレビュー、縮小版、および検索フィルター ハンドラーを実装している ATL プロジェクトで定義でき、
// そのプロジェクトとのドキュメント コードの共有を可能にします。
#ifndef SHARED_HANDLERS
#include "SingleDoc_3.h"
#endif

#include "SingleDoc_3Doc.h"
#include "SingleDoc_3View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSingleDoc3View

IMPLEMENT_DYNCREATE(CSingleDoc3View, CView)

BEGIN_MESSAGE_MAP(CSingleDoc3View, CView)
	// 標準印刷コマンド
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CSingleDoc3View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CSingleDoc3View コンストラクション/デストラクション

CSingleDoc3View::CSingleDoc3View() noexcept
{
	// TODO: 構築コードをここに追加します。

}

CSingleDoc3View::~CSingleDoc3View()
{
}

BOOL CSingleDoc3View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: この位置で CREATESTRUCT cs を修正して Window クラスまたはスタイルを
	//  修正してください。

	return CView::PreCreateWindow(cs);
}

// CSingleDoc3View 描画

void CSingleDoc3View::OnDraw(CDC* pDC)
{
	CSingleDoc3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: この場所にネイティブ データ用の描画コードを追加します。
	CPen myPen(PS_SOLID, 1, RGB(0, 0, 255));//ペンを確保。実線で太さ1の青。
	CPen *oldPen = pDC->SelectObject(&myPen);//古いペン保存と新ペン登録
	pDC->MoveTo(10, 10);//直線の開始位置
	pDC->LineTo(100, 100);//指定の点まで直線を書く。
	pDC->SelectObject(oldPen);//古いペンに戻す。
}


// CSingleDoc3View の印刷


void CSingleDoc3View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CSingleDoc3View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 既定の印刷準備
	return DoPreparePrinting(pInfo);
}

void CSingleDoc3View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 印刷前の特別な初期化処理を追加してください。
}

void CSingleDoc3View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 印刷後の後処理を追加してください。
}

void CSingleDoc3View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CSingleDoc3View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CSingleDoc3View の診断

#ifdef _DEBUG
void CSingleDoc3View::AssertValid() const
{
	CView::AssertValid();
}

void CSingleDoc3View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSingleDoc3Doc* CSingleDoc3View::GetDocument() const // デバッグ以外のバージョンはインラインです。
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSingleDoc3Doc)));
	return (CSingleDoc3Doc*)m_pDocument;
}
#endif //_DEBUG


// CSingleDoc3View メッセージ ハンドラー
