// SetEvent.h : SETEVENT アプリケーションのメイン ヘッダー ファイルです。
//

#if !defined(AFX_SETEVENT_H__7C57C7DB_7780_11D2_AB98_0000B4725554__INCLUDED_)
#define AFX_SETEVENT_H__7C57C7DB_7780_11D2_AB98_0000B4725554__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// メイン シンボル

/////////////////////////////////////////////////////////////////////////////
// CSetEventApp:
// このクラスの動作の定義に関しては SetEvent.cpp ファイルを参照してください。
//

class CSetEventApp : public CWinApp
{
public:
	CSetEventApp();

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CSetEventApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// インプリメンテーション

	//{{AFX_MSG(CSetEventApp)
		// メモ - ClassWizard はこの位置にメンバ関数を追加または削除します。
		//        この位置に生成されるコードを編集しないでください。
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_SETEVENT_H__7C57C7DB_7780_11D2_AB98_0000B4725554__INCLUDED_)
