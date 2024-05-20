// Employee.cpp : CEmployee のインプリメンテーション
#include "stdafx.h"
#include "BUObject.h"
#include "Employee.h"

/////////////////////////////////////////////////////////////////////////////
// CEmployee


STDMETHODIMP CEmployee::get_Name(BSTR *pVal)
{
	// TODO: この位置にインプリメント用のコードを追加してください
   *pVal = m_bstrName.Copy();
	return S_OK;
}

STDMETHODIMP CEmployee::put_Name(BSTR newVal)
{
	// TODO: この位置にインプリメント用のコードを追加してください
   m_bstrName = newVal;
	return S_OK;
}

STDMETHODIMP CEmployee::get_EmployeeID(long *pVal)
{
	// TODO: この位置にインプリメント用のコードを追加してください
   *pVal = m_lEmployeeID;
	return S_OK;
}

STDMETHODIMP CEmployee::put_EmployeeID(long newVal)
{
	// TODO: この位置にインプリメント用のコードを追加してください
   m_lEmployeeID = newVal;
	return S_OK;
}
