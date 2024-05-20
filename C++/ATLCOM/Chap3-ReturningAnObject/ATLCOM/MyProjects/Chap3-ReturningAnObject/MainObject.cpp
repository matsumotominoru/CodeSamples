// MainObject.cpp : CMainObject のインプリメンテーション
#include "stdafx.h"
#include "ReturningAnObject.h"
#include "MainObject.h"
#include "SeparateObject.h"	//..ADD

/////////////////////////////////////////////////////////////////////////////
// CMainObject


STDMETHODIMP CMainObject::Display()
{
	// TODO: この位置にインプリメント用のコードを追加してください
	MessageBox(NULL, 
		_T("IMainObject::Display()"), 
		_T("IMainObject::Display()"), MB_OK);
	return S_OK;
}

STDMETHODIMP CMainObject::CreateSeparateObject(ISeparateObject **ppSep)
{
	// TODO: この位置にインプリメント用のコードを追加してください
	*ppSep = NULL;
	// If we're not interested in keeping a pointer to the objects created
	// by this function, we can use CComCreator<>::CreateInstance() to return
	// the interface pointer directly to the client.
	//
	// CComCreator<> takes the type of object to create as its template parameter.
	// In this case, we create objects of type CComObject<CSeparateObject>.
	//
	// CComCreator<>::CreateInstance() is a static function that takes the outer
	// unknown, the interface ID, and the indirect pointer to the interface.
	// This is the same function used by standard ATL projects to create instances
	// of your coclasses.
	//
	// Using CComCreator<>::CreateInstance() is more efficient than calling CoCreateInstance()
	// but the results are equivalent
	return	CComCreator< CComObject<CSeparateObject> >::CreateInstance(
		NULL, IID_ISeparateObject, reinterpret_cast<void**>(ppSep) );
	return S_OK;
}

STDMETHODIMP CMainObject::CreateAndInitializeSeparateObject(ISeparateObject **ppSep)
{
	// TODO: この位置にインプリメント用のコードを追加してください
	*ppSep = NULL;
	// You may need to initialize your object before returning it to
	// the client. You can do that like this:

	// Declare a CComObject<> pointer using your class as the template parameter
	CComObject<CSeparateObject>* pSub;

	// Call the static CComObject<>::CreateInstance() member,
	// passing a pointer to your pointer. This creates an instance of your
	// CComObject<> class, without any references counted on it.
	HRESULT hr = CComObject<CSeparateObject>::CreateInstance(&pSub);

	// Check the return result, and pass it back to the client on failure
	if (FAILED(hr))
		return hr;

	// Initialize the object according to your own rules
	pSub->m_bInitialized = true;

	// Call QueryInterface() to get the interface pointer to pass back to the client
	hr = pSub->QueryInterface(IID_ISeparateObject,
		reinterpret_cast<void**>(ppSep));

	// If the QueryInterface() failed, delete the object
	if (FAILED(hr))
		delete pSub;

	// Return the HRESULT
	return hr;
}
