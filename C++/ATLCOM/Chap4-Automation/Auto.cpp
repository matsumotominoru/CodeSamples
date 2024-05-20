// Auto.cpp : CAuto のインプリメンテーション
#include "stdafx.h"
#include "Automation.h"
#include "Auto.h"
#pragma warning(disable : 4530)
#include <string>
/////////////////////////////////////////////////////////////////////////////
// CAuto

STDMETHODIMP CAuto::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IAuto,
		&IID_IAuto2
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CAuto::Greeting(BSTR bstrName, BSTR *bstrGreeting)
{
	// TODO: この位置にインプリメント用のコードを追加してください
   SYSTEMTIME st;
   GetLocalTime(&st);
   TCHAR strTime[23];
   wsprintf(strTime, _T("The time is %02d:%02d:%02d "),
      st.wHour, st.wMinute, st.wSecond);
   CComBSTR bstrRet(strTime);
   bstrRet += bstrName;
   *bstrGreeting = bstrRet.Copy();
	return S_OK;
}

STDMETHODIMP CAuto::GetGender(BSTR bstrName, BSTR *bstrGender)
{
	// TODO: この位置にインプリメント用のコードを追加してください
   if (bstrName == NULL)
      return E_INVALIDARG;
   *bstrGender = NULL;

   std::basic_string<WCHAR> strWholeName(bstrName);
   std::basic_string<WCHAR> strTitle;
   std::basic_string<WCHAR> strName;

   strTitle = strWholeName.substr(0, 3);
   std::basic_string<WCHAR>::size_type pos;
   pos = strWholeName.find(L' ');
   if (pos == std::basic_string<WCHAR>::npos)
      return E_INVALIDARG;
   strName = strWholeName.substr(pos + 1);

   CComBSTR bstrRet(L"The gender of ");
   bstrRet += strName.c_str();
   bstrRet += L" is ";

   if (strTitle.compare(L"Mr ") == 0)
      bstrRet += "male";
   else if (strTitle.compare(L"Mrs") == 0 ||
            strTitle.compare(L"Mis") == 0 ||
            strTitle.compare(L"Ms ") == 0)
      bstrRet += "female";
   else
      bstrRet += "unknown";

   *bstrGender = bstrRet.Copy();

	return S_OK;
}

STDMETHODIMP CAuto::Value(LONG lVal)
{
	// TODO: この位置にインプリメント用のコードを追加してください
   if (lVal < 0)
   {
      TCHAR str[256];
      wsprintf(str, _T("IAuto: %ld is too small, use a value > 0"), lVal);
      Error(str, IID_IAuto);
      return E_FAIL;
   }
	return S_OK;
}

STDMETHODIMP CAuto::Value2(LONG lVal)
{
	// TODO: この位置にインプリメント用のコードを追加してください
   if (lVal > 0)
   {
      TCHAR str[256];
      wsprintf(str, _T("IAuto2: %ld is too big, use a value < 0"), lVal);
      Error(str, IID_IAuto2);
      return E_FAIL;
   }
	return S_OK;
}
