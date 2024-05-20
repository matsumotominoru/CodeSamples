// ColorObject.cpp : CColorObject のインプリメンテーション
#include "stdafx.h"
#include "Colors.h"
#include "ColorObject.h"

/////////////////////////////////////////////////////////////////////////////
// CColorObject


STDMETHODIMP CColorObject::get_Colors(VARIANT *pVal)
{
	// TODO: この位置にインプリメント用のコードを追加してください
	VariantInit(pVal);
	pVal->vt = VT_ARRAY | VT_BSTR;
	SAFEARRAY* psa;
	SAFEARRAYBOUND bounds = {m_vecColors.size(), 0};
	psa = SafeArrayCreate(VT_BSTR, 1, &bounds);

	BSTR* bstrArray;
	SafeArrayAccessData(psa, (void**)&bstrArray);
	std::vector<CComBSTR>::iterator it;
	int i = 0;
	for (it = m_vecColors.begin(); it != m_vecColors.end(); it++, i++)
	{
		bstrArray[i] = SysAllocString((*it).m_str);
	}
	SafeArrayUnaccessData(psa);
	pVal->parray = psa;

	ATLTRACE(_T("Returning SafeArray which")
			_T("has these members:\n"));
	DumpVector();
	return S_OK;
}

STDMETHODIMP CColorObject::put_Colors(VARIANT newVal)
{
	// TODO: この位置にインプリメント用のコードを追加してください
	if ((newVal.vt & VT_ARRAY) == 0)
		return E_INVALIDARG; // Not an array

	if ((newVal.vt & VT_BSTR) == 0)
		return E_INVALIDARG; // Not an array of BSTRs

	m_vecColors.clear();
	SAFEARRAY* psa = newVal.parray;
	BSTR* bstrArray;
	SafeArrayAccessData(psa, (void**)&bstrArray);

	// Assume just one dimension
	for (int i = 0; i < psa->rgsabound->cElements; i++)
	{
		m_vecColors.push_back(CComBSTR(bstrArray[i]));
	}

	SafeArrayUnaccessData(psa);
	ATLTRACE(_T("Changing SafeArray to have")
			_T("these members:\n"));
	DumpVector();
	return S_OK;
}

HRESULT CColorObject::FinalConstruct()
{
   m_vecColors.push_back(CComBSTR(L"Red"));
   m_vecColors.push_back(CComBSTR(L"Orange"));
   m_vecColors.push_back(CComBSTR(L"Yellow"));
   m_vecColors.push_back(CComBSTR(L"Green"));
   m_vecColors.push_back(CComBSTR(L"Blue"));
   m_vecColors.push_back(CComBSTR(L"Indigo"));
   m_vecColors.push_back(CComBSTR(L"Violet"));
   return S_OK;
}

void CColorObject::DumpVector()
{
#ifdef _DEBUG
   std::vector<CComBSTR>::iterator it;

   ATLTRACE(_T("[\n"));
   for (it = m_vecColors.begin(); it != m_vecColors.end(); it++)
   {
      ATLTRACE(_T("\t%ls,\n"), (*it).m_str);
   }
   ATLTRACE(_T("]\n"));
#endif
}