
// MFCDlg_3.h : PROJECT_NAME アプリケーションのメイン ヘッダー ファイルです
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH に対してこのファイルをインクルードする前に 'pch.h' をインクルードしてください"
#endif

#include "resource.h"		// メイン シンボル


// CMFCDlg3App:
// このクラスの実装については、MFCDlg_3.cpp を参照してください
//

class CMFCDlg3App : public CWinApp
{
public:
	CMFCDlg3App();

// オーバーライド
public:
	virtual BOOL InitInstance();

// 実装

	DECLARE_MESSAGE_MAP()
};

extern CMFCDlg3App theApp;
