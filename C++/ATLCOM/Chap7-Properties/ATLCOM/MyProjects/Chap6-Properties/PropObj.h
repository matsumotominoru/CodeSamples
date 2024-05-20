// PropObj.h : CPropObj ÇÃêÈåæ

#ifndef __PROPOBJ_H_
#define __PROPOBJ_H_

#include "resource.h"       // ÉÅÉCÉì ÉVÉìÉ{Éã

/////////////////////////////////////////////////////////////////////////////
// CPropObj
class ATL_NO_VTABLE CPropObj : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CPropObj, &CLSID_PropObj>,
   public CComControl<CPropObj>,			// ADD
   public IPersistStreamInitImpl<CPropObj>,	// ADD
	public IDispatchImpl<IPropObj, &IID_IPropObj, &LIBID_PROPERTIESLib>
{
public:
	CPropObj(): m_ObjNumber(0)
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_PROPOBJ)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CPropObj)
	COM_INTERFACE_ENTRY(IPropObj)
	COM_INTERFACE_ENTRY(IDispatch)
   COM_INTERFACE_ENTRY_IMPL(IPersistStreamInit)	// ADD
   COM_INTERFACE_ENTRY_IMPL_IID(IID_IPersistStream, IPersistStreamInit)	// ADD

END_COM_MAP()

BEGIN_PROPERTY_MAP(CPropObj)
   PROP_ENTRY("ObjString", 1, CLSID_NULL)
   PROP_ENTRY("ObjNumber", 2, CLSID_NULL)
END_PROPERTY_MAP()

BEGIN_MSG_MAP(CPropObj)
END_MSG_MAP()


// IPropObj
public:
	STDMETHOD(get_ObjNumber)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_ObjNumber)(/*[in]*/ long newVal);
	STDMETHOD(get_ObjString)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_ObjString)(/*[in]*/ BSTR newVal);
private:					// ADD
   CComBSTR m_ObjString;	// ADD
   long m_ObjNumber;		// ADD

};

#endif //__PROPOBJ_H_
