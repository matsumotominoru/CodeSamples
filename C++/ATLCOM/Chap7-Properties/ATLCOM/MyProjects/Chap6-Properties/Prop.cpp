// Prop.cpp : CProp のインプリメンテーション

#include "stdafx.h"
#include "Properties.h"
#include "Prop.h"

/////////////////////////////////////////////////////////////////////////////
// CProp


STDMETHODIMP CProp::get_String(BSTR *pVal)
{
	// TODO: この位置にインプリメント用のコードを追加してください
   ATLTRACE(_T("String returning: %ls\n"), m_bstrString);
   *pVal = SysAllocString(m_bstrString.m_str);
	return S_OK;
}

STDMETHODIMP CProp::put_String(BSTR newVal)
{
	// TODO: この位置にインプリメント用のコードを追加してください
   ATLTRACE(_T("String assigned to: %ls\n"), newVal);
   m_bstrString = newVal;
   SysFreeString(newVal);
   SetDirty(true);
   SendOnDataChange();
   FireViewChange();

	return S_OK;
}

STDMETHODIMP CProp::get_Number(long *pVal)
{
	// TODO: この位置にインプリメント用のコードを追加してください
   ATLTRACE(_T("Number returning: %ld\n"), m_lNumber);
   *pVal = m_lNumber;
	return S_OK;
}

STDMETHODIMP CProp::put_Number(long newVal)
{
	// TODO: この位置にインプリメント用のコードを追加してください
   m_lNumber = newVal;
   SetDirty(true);
   SendOnDataChange();
   FireViewChange();
	return S_OK;
}

STDMETHODIMP CProp::InitNew()
{
   if (m_bInitialized)
      return E_UNEXPECTED;
   m_bstrCaption = "Caption";
   m_bstrString = "String";
   m_lNumber = -99;
   m_Obj = new CComObject<CPropObj>;
   m_Obj->put_ObjString(SysAllocString(L"ObjString"));
   m_Obj->put_ObjNumber(-999);

   SetDirty(true);
   m_bInitialized = true;
   return S_OK;
}

STDMETHODIMP CProp::Load(LPSTREAM pStm)
{
   if (m_bInitialized)
      return E_UNEXPECTED;
   else
   {
      m_bInitialized = true;
      return IPersistStreamInitImpl<CProp>::Load(pStm);
   }
}

LRESULT CProp::OnClick(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
   long lNum;
   get_Number(&lNum);
   lNum++;
   put_Number(lNum);
   return 0;
}

STDMETHODIMP CProp::get_Obj(LPDISPATCH *pVal)
{
	// TODO: この位置にインプリメント用のコードを追加してください
   CComBSTR str;
   long num;
   GetPropObj(str, &num);
   ATLTRACE(_T("Obj returning: %ls, %ld\n"), str, num);
   *pVal = m_Obj;
   (*pVal)->AddRef();
	return S_OK;
}

STDMETHODIMP CProp::put_Obj(LPDISPATCH newVal)
{
	// TODO: この位置にインプリメント用のコードを追加してください
   // Will release any held pointer
   m_Obj = newVal;

   CComBSTR str;
   long num;
   GetPropObj(str, &num);
   ATLTRACE(_T("Obj assigned to: %ls, %ld\n"), str, num);

   SetDirty(true);
   SendOnDataChange();
   FireViewChange();

	return S_OK;
}

bool CProp::GetPropObj(CComBSTR& bstr, long* lVal)
{
   if (!m_Obj)
      return false;

   m_Obj->get_ObjString(&bstr);
   m_Obj->get_ObjNumber(lVal);

   return true;
}
