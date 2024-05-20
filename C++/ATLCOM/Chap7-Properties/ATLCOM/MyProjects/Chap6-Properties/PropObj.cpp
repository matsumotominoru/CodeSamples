// PropObj.cpp : CPropObj �̃C���v�������e�[�V����
#include "stdafx.h"
#include "Properties.h"
#include "PropObj.h"

/////////////////////////////////////////////////////////////////////////////
// CPropObj


STDMETHODIMP CPropObj::get_ObjString(BSTR *pVal)
{
	// TODO: ���̈ʒu�ɃC���v�������g�p�̃R�[�h��ǉ����Ă�������
   ATLTRACE(_T("ObjString returning: %ls\n"), m_ObjString);
   *pVal = m_ObjString.Copy();
	return S_OK;
}

STDMETHODIMP CPropObj::put_ObjString(BSTR newVal)
{
	// TODO: ���̈ʒu�ɃC���v�������g�p�̃R�[�h��ǉ����Ă�������
   ATLTRACE(_T("ObjString assigned to: %ls\n"), newVal);
   m_ObjString = newVal;
	return S_OK;
}

STDMETHODIMP CPropObj::get_ObjNumber(long *pVal)
{
	// TODO: ���̈ʒu�ɃC���v�������g�p�̃R�[�h��ǉ����Ă�������
   ATLTRACE(_T("ObjNumber returning: %ld\n"), m_ObjNumber);
   *pVal = m_ObjNumber;

	return S_OK;
}

STDMETHODIMP CPropObj::put_ObjNumber(long newVal)
{
	// TODO: ���̈ʒu�ɃC���v�������g�p�̃R�[�h��ǉ����Ă�������
   ATLTRACE(_T("ObjNumber assigned to: %ld\n"), newVal);
   m_ObjNumber = newVal;

	return S_OK;
}
