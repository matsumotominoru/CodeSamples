// SeparateObject.h : CSeparateObject ÇÃêÈåæ

#ifndef __SEPARATEOBJECT_H_
#define __SEPARATEOBJECT_H_

#include "resource.h"       // ÉÅÉCÉì ÉVÉìÉ{Éã

/////////////////////////////////////////////////////////////////////////////
// CSeparateObject
class ATL_NO_VTABLE CSeparateObject : 
	public CComObjectRootEx<CComSingleThreadModel>,
//	public CComCoClass<CSeparateObject, &CLSID_SeparateObject>,
	public IDispatchImpl<ISeparateObject, &IID_ISeparateObject, &LIBID_RETURNINGANOBJECTLib>
{
public:
	CSeparateObject():m_bInitialized(false)
	{
	}

//DECLARE_REGISTRY_RESOURCEID(IDR_SEPARATEOBJECT)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CSeparateObject)
	COM_INTERFACE_ENTRY(ISeparateObject)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

// ISeparateObject
public:
	STDMETHOD(Display)();
	bool	m_bInitialized;
};

#endif //__SEPARATEOBJECT_H_
