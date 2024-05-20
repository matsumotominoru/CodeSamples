// BusinessUnit.cpp : CBusinessUnit のインプリメンテーション
#include "stdafx.h"
#include "BUObject.h"
#include "BusinessUnit.h"

#include "BusinessUnit.h"
#include "Employee.h"
#include "DeveloperCollection.h"

/////////////////////////////////////////////////////////////////////////////
// CBusinessUnit


STDMETHODIMP CBusinessUnit::get_Manager(LPDISPATCH *pVal)
{
	// TODO: この位置にインプリメント用のコードを追加してください
   *pVal = m_pManager;
   (*pVal)->AddRef();
	return S_OK;
}

STDMETHODIMP CBusinessUnit::put_Manager(LPDISPATCH newVal)
{
	// TODO: この位置にインプリメント用のコードを追加してください
   m_pManager = newVal;
	return S_OK;
}

STDMETHODIMP CBusinessUnit::get_Secretary(LPDISPATCH *pVal)
{
	// TODO: この位置にインプリメント用のコードを追加してください
   *pVal = m_pSecretary;
   (*pVal)->AddRef();
	return S_OK;
}

STDMETHODIMP CBusinessUnit::put_Secretary(LPDISPATCH newVal)
{
	// TODO: この位置にインプリメント用のコードを追加してください
   m_pSecretary = newVal;
	return S_OK;
}

STDMETHODIMP CBusinessUnit::get_Developers(LPDISPATCH *pVal)
{
	// TODO: この位置にインプリメント用のコードを追加してください
   *pVal = m_pDevelopers;
   (*pVal)->AddRef();
	return S_OK;
}
HRESULT CBusinessUnit::FinalConstruct()
{
   HRESULT hr;
   CComObject<CDeveloperCollection>* pDevs;
   hr = CComObject<CDeveloperCollection>::CreateInstance(&pDevs);
   if (FAILED(hr))
      return hr;
   m_pDevelopers = pDevs;

   CComObject<CEmployee>* pEmp;
   hr = CComObject<CEmployee>::CreateInstance(&pEmp);
   if (FAILED(hr))
      return hr;
   pEmp->put_Name(CComBSTR(_T("<vacant>")));
   m_pManager = pEmp;

   hr = CComObject<CEmployee>::CreateInstance(&pEmp);
   if (FAILED(hr))
      return hr;
   pEmp->put_Name(CComBSTR(_T("<vacant>")));
   m_pSecretary = pEmp;

   return hr;
}
