﻿
// SingleDocTemplate_DefaultView.h : CSingleDocTemplateDefaultView クラスのインターフェイス
//

#pragma once


class CSingleDocTemplateDefaultView : public CView
{
protected: // シリアル化からのみ作成します。
	CSingleDocTemplateDefaultView() noexcept;
	DECLARE_DYNCREATE(CSingleDocTemplateDefaultView)

// 属性
public:
	CSingleDocTemplateDefaultDoc* GetDocument() const;

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
	virtual ~CSingleDocTemplateDefaultView();
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

#ifndef _DEBUG  // SingleDocTemplate_DefaultView.cpp のデバッグ バージョン
inline CSingleDocTemplateDefaultDoc* CSingleDocTemplateDefaultView::GetDocument() const
   { return reinterpret_cast<CSingleDocTemplateDefaultDoc*>(m_pDocument); }
#endif

