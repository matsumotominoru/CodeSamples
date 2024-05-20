
// MFCDlg_TakebashiQ_1.h : PROJECT_NAME アプリケーションのメイン ヘッダー ファイルです
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH に対してこのファイルをインクルードする前に 'pch.h' をインクルードしてください"
#endif

#include "resource.h"		// メイン シンボル


// CMFCDlgTakebashiQ1App:
// このクラスの実装については、MFCDlg_TakebashiQ_1.cpp を参照してください
//

class CMFCDlgTakebashiQ1App : public CWinApp
{
public:
	CMFCDlgTakebashiQ1App();

// オーバーライド
public:
	virtual BOOL InitInstance();

// 実装

	DECLARE_MESSAGE_MAP()
};

extern CMFCDlgTakebashiQ1App theApp;
