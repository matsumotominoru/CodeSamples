
// SingleDocTemplate_1View.h : CSingleDocTemplate1View クラスのインターフェイス
//

#pragma once


class CSingleDocTemplate1View : public CView
{
protected: // シリアル化からのみ作成します。
	CSingleDocTemplate1View() noexcept;
	DECLARE_DYNCREATE(CSingleDocTemplate1View)

// 属性
public:
	CSingleDocTemplate1Doc* GetDocument() const;

// 操作
public:

// オーバーライド
public:
	virtual void OnDraw(CDC* pDC);  // このビューを描画するためにオーバーライドされます。
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 実装
public:
	virtual ~CSingleDocTemplate1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成された、メッセージ割り当て関数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // SingleDocTemplate_1View.cpp のデバッグ バージョン
inline CSingleDocTemplate1Doc* CSingleDocTemplate1View::GetDocument() const
   { return reinterpret_cast<CSingleDocTemplate1Doc*>(m_pDocument); }
#endif

