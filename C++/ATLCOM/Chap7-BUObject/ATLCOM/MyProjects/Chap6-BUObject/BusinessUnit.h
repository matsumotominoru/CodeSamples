// BusinessUnit.h : CBusinessUnit ÇÃêÈåæ

#ifndef __BUSINESSUNIT_H_
#define __BUSINESSUNIT_H_

#include "resource.h"       // ÉÅÉCÉì ÉVÉìÉ{Éã

/////////////////////////////////////////////////////////////////////////////
// CBusinessUnit
class ATL_NO_VTABLE CBusinessUnit : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CBusinessUnit, &CLSID_BusinessUnit>,
	public IDispatchImpl<IBusinessUnit, &IID_IBusinessUnit, &LIBID_BUOBJECTLib>
{
public:
	CBusinessUnit()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_BUSINESSUNIT)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CBusinessUnit)
	COM_INTERFACE_ENTRY(IBusinessUnit)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

HRESULT FinalConstruct();

// IBusinessUnit
public:
	STDMETHOD(get_Developers)(/*[out, retval]*/ LPDISPATCH *pVal);
	STDMETHOD(get_Secretary)(/*[out, retval]*/ LPDISPATCH *pVal);
	STDMETHOD(put_Secretary)(/*[in]*/ LPDISPATCH newVal);
	STDMETHOD(get_Manager)(/*[out, retval]*/ LPDISPATCH *pVal);
	STDMETHOD(put_Manager)(/*[in]*/ LPDISPATCH newVal);
private:
   CComQIPtr<IEmployee, &IID_IEmployee> m_pManager;
   CComQIPtr<IEmployee, &IID_IEmployee> m_pSecretary;
   CComPtr<IDeveloperCollection> m_pDevelopers;

};

#endif //__BUSINESSUNIT_H_
