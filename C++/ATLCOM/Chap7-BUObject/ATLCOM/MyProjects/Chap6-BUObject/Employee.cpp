// Employee.cpp : CEmployee �̃C���v�������e�[�V����
#include "stdafx.h"
#include "BUObject.h"
#include "Employee.h"

/////////////////////////////////////////////////////////////////////////////
// CEmployee


STDMETHODIMP CEmployee::get_Name(BSTR *pVal)
{
	// TODO: ���̈ʒu�ɃC���v�������g�p�̃R�[�h��ǉ����Ă�������
   *pVal = m_bstrName.Copy();
	return S_OK;
}

STDMETHODIMP CEmployee::put_Name(BSTR newVal)
{
	// TODO: ���̈ʒu�ɃC���v�������g�p�̃R�[�h��ǉ����Ă�������
   m_bstrName = newVal;
	return S_OK;
}

STDMETHODIMP CEmployee::get_EmployeeID(long *pVal)
{
	// TODO: ���̈ʒu�ɃC���v�������g�p�̃R�[�h��ǉ����Ă�������
   *pVal = m_lEmployeeID;
	return S_OK;
}

STDMETHODIMP CEmployee::put_EmployeeID(long newVal)
{
	// TODO: ���̈ʒu�ɃC���v�������g�p�̃R�[�h��ǉ����Ă�������
   m_lEmployeeID = newVal;
	return S_OK;
}
