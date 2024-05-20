
// SingleDoc_3View.h : CSingleDoc3View クラスのインターフェイス
//

#pragma once


class CSingleDoc3View : public CView
{
protected: // シリアル化からのみ作成します。
	CSingleDoc3View() noexcept;
	DECLARE_DYNCREATE(CSingleDoc3View)

// 属性
public:
	CSingleDoc3Doc* GetDocument() const;

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
	virtual ~CSingleDoc3View();
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

#ifndef _DEBUG  // SingleDoc_3View.cpp のデバッグ バージョン
inline CSingleDoc3Doc* CSingleDoc3View::GetDocument() const
   { return reinterpret_cast<CSingleDoc3Doc*>(m_pDocument); }
#endif

