// Auto.h : CAuto ÇÃêÈåæ

#ifndef __AUTO_H_
#define __AUTO_H_

#include "resource.h"       // ÉÅÉCÉì ÉVÉìÉ{Éã

/////////////////////////////////////////////////////////////////////////////
// CAuto
class ATL_NO_VTABLE CAuto : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CAuto, &CLSID_Auto>,
	public ISupportErrorInfo,
	public IDispatchImpl<IAuto, &IID_IAuto, &LIBID_AUTOMATIONLib>,
    public IDispatchImpl<IAuto2, &IID_IAuto2, &LIBID_AUTOMATIONLib>
{
public:
	CAuto()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_AUTO)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CAuto)
	COM_INTERFACE_ENTRY(IAuto)
	COM_INTERFACE_ENTRY(IAuto2)
	COM_INTERFACE_ENTRY2(IDispatch,IAuto)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IAuto
public:

// IAuto2
public:
	STDMETHOD(Value2)(/*[in]*/ LONG lVal);
	STDMETHOD(Value)(/*[in]*/ LONG lVal);
	STDMETHOD(GetGender)(/*[in]*/ BSTR bstrName, /*[out, retval]*/ BSTR* bstrGender);
	STDMETHOD(Greeting)(/*[in]*/ BSTR bstrName, /*[out,retval]*/ BSTR* bstrGreeting);
};

#endif //__AUTO_H_
