
// SingleDocTemplate_1.h : SingleDocTemplate_1 アプリケーションのメイン ヘッダー ファイル
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH に対してこのファイルをインクルードする前に 'pch.h' をインクルードしてください"
#endif

#include "resource.h"       // メイン シンボル


// CSingleDocTemplate1App:
// このクラスの実装については、SingleDocTemplate_1.cpp を参照してください
//

class CSingleDocTemplate1App : public CWinAppEx
{
public:
	CSingleDocTemplate1App() noexcept;


// オーバーライド
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 実装
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CSingleDocTemplate1App theApp;
