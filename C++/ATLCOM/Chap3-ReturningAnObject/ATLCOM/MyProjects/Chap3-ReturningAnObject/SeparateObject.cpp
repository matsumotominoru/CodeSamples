// SeparateObject.cpp : CSeparateObject �̃C���v�������e�[�V����
#include "stdafx.h"
#include "ReturningAnObject.h"
#include "SeparateObject.h"

/////////////////////////////////////////////////////////////////////////////
// CSeparateObject


STDMETHODIMP CSeparateObject::Display()
{
	// TODO: ���̈ʒu�ɃC���v�������g�p�̃R�[�h��ǉ����Ă�������
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
