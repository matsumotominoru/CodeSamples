
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

#include <math.h>//■追加

 //変数の定義■追加
#define g 9.8            //重力加速度
#define PI 3.14159     //円周率
#define d 0.072         //ボールの直径
#define dt 0.03         //計算時間間隔

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

	//■追加
    CPen pc1(PS_SOLID, 1, RGB(0, 125, 128)); //ペンの初期化
    CPen pc3(PS_SOLID, 2, RGB(0, 0, 255));

    CPen *oldp = pDC->SelectObject(&pc1); //ペンの変更

    int x0 = 50, y0 = 380, xsp = 600, ysp = 300; //作図範囲
    int xp, yp;
    int ss=0;
    char buf[80];
    double xmax = 120, ymax = 50; //各変数
    double a, cd, l;
    double x, y, v0, vi0, t, th;
    double xd, yd, x2d, y2d, r, m;

    cd = 0.4; //空気抵抗係数
    l = 1.25 / g; //空気密度
    m = 0.146 / g; //ボールの質量

    x = y = t = 0;
    vi0 = 150; //初速度
    th = 45; //打ち上げ角度

    v0 = vi0 * 1000.0 / 3600.0;
    th = th * PI / 180.0;
    a = d * d * PI / 4.0;
    xd = v0 * cos(th);
    yd = v0 * sin(th);

    //軸の表示
    pDC->SelectObject(&pc3);

    pDC->MoveTo(x0, y0); pDC->LineTo(x0 + xsp, y0);
    pDC->MoveTo(x0, y0); pDC->LineTo(x0, y0 - ysp);

    pDC->SetTextColor(RGB(0, 0, 255));
    pDC->TextOut(60, 0, "空気抵抗を受けるボールの放物運動計算プログラム by T.SATOW "); //文字出力
    pDC->SetTextColor(RGB(0, 65, 0));
    sprintf_s(buf, "ボールの重さ:%.2lfg 初速度:%.1lfkm/h 打ち上げ角度:%.1lf°", m * 1000.0 * g, vi0, th * 180.0 / PI);
    pDC->TextOut(100, 20, buf);

    pDC->SelectObject(&pc1);
    while (y >= 0) {
        xp = (int)(x0 + x * xsp / xmax);
        yp = (int)(y0 - y * ysp / ymax);
        pDC->Ellipse(xp - 3, yp - 3, xp + 3, yp + 3); //左上と右下に接する楕円

        r = 0.5 * l * a * cd; //運動方程式の解
        ss = (int)_sgn(xd, ss);
        x2d = -r * (xd * xd) / m * ss;
        xd += x2d * dt;
        x += xd * dt;
        ss = (int)_sgn(yd, ss);
        y2d = -r * yd * yd / m * ss - g;
        yd += y2d * dt;
        y += yd * dt;
        t += dt;
        timewait(1000); //時間待ち
    }

    pDC->SetTextColor(RGB(250, 52, 50));
    sprintf_s(buf, "到達距離= %.2fm", x);
    pDC->TextOut(120, 40, buf); //文字出力


    pDC->SelectObject(oldp); //ペンを元に戻す
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

//記号変更■追加
double CSingleDoc3View::_sgn(double dd, int s)
{
    if (dd < 0) s = -1;
    else if (dd == 0) s = 0;
    else s = 1;
    return(s);
}

//時間待■追加
void CSingleDoc3View::timewait(int n)
{
    int a, i, j, m = 1000;

    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            a = i;
        }
    }
}