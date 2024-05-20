
// MFCDlgTemplateDefault.h : PROJECT_NAME アプリケーションのメイン ヘッダー ファイルです
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH に対してこのファイルをインクルードする前に 'pch.h' をインクルードしてください"
#endif

#include "resource.h"		// メイン シンボル


// CMFCDlgTemplateDefaultApp:
// このクラスの実装については、MFCDlgTemplateDefault.cpp を参照してください
//

class CMFCDlgTemplateDefaultApp : public CWinApp
{
public:
	CMFCDlgTemplateDefaultApp();

// オーバーライド
public:
	virtual BOOL InitInstance();

// 実装

	DECLARE_MESSAGE_MAP()
};

extern CMFCDlgTemplateDefaultApp theApp;
