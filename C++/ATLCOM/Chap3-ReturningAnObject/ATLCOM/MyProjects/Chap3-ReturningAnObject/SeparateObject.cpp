// SeparateObject.cpp : CSeparateObject のインプリメンテーション
#include "stdafx.h"
#include "ReturningAnObject.h"
#include "SeparateObject.h"

/////////////////////////////////////////////////////////////////////////////
// CSeparateObject


STDMETHODIMP CSeparateObject::Display()
{
	// TODO: この位置にインプリメント用のコードを追加してください
	if (!m_bInitialized)
		MessageBox(NULL, 
			_T("ISeparateObject::Display()"), 
			_T("ISeparateObject::Display()"),
			MB_OK);
	else
		MessageBox(NULL, 
			_T("ISeparateObject::Display() - Initialized"), 
			_T("ISeparateObject::Display() - Initialized"),
			MB_OK);
	return S_OK;
}
