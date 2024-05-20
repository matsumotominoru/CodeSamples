
// CsLsvw.h : PROJECT_NAME アプリケーションのメイン ヘッダー ファイルです
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH に対してこのファイルをインクルードする前に 'pch.h' をインクルードしてください"
#endif

#include "resource.h"		// メイン シンボル


// CCsLsvwApp:
// このクラスの実装については、CsLsvw.cpp を参照してください
//

class CCsLsvwApp : public CWinApp
{
public:
	CCsLsvwApp();

// オーバーライド
public:
	virtual BOOL InitInstance();

// 実装

	DECLARE_MESSAGE_MAP()
};

extern CCsLsvwApp theApp;
