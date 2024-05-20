
// MFCDlg_2.h : PROJECT_NAME アプリケーションのメイン ヘッダー ファイルです
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH に対してこのファイルをインクルードする前に 'pch.h' をインクルードしてください"
#endif

#include "resource.h"		// メイン シンボル


// CMFCDlg2App:
// このクラスの実装については、MFCDlg_2.cpp を参照してください
//

class CMFCDlg2App : public CWinApp
{
public:
	CMFCDlg2App();

// オーバーライド
public:
	virtual BOOL InitInstance();

// 実装

	DECLARE_MESSAGE_MAP()
};

extern CMFCDlg2App theApp;
