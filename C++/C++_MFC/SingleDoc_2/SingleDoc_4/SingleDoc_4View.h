
// SingleDoc_4View.h : CSingleDoc4View クラスのインターフェイス
//

#pragma once


class CSingleDoc4View : public CView
{
protected: // シリアル化からのみ作成します。
	CSingleDoc4View() noexcept;
	DECLARE_DYNCREATE(CSingleDoc4View)

// 属性
public:
	CSingleDoc4Doc* GetDocument() const;

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
	virtual ~CSingleDoc4View();
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
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // SingleDoc_4View.cpp のデバッグ バージョン
inline CSingleDoc4Doc* CSingleDoc4View::GetDocument() const
   { return reinterpret_cast<CSingleDoc4Doc*>(m_pDocument); }
#endif

