// Employee.h : CEmployee ÇÃêÈåæ

#ifndef __EMPLOYEE_H_
#define __EMPLOYEE_H_

#include "resource.h"       // ÉÅÉCÉì ÉVÉìÉ{Éã

/////////////////////////////////////////////////////////////////////////////
// CEmployee
class ATL_NO_VTABLE CEmployee : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CEmployee, &CLSID_Employee>,
	public IDispatchImpl<IEmployee, &IID_IEmployee, &LIBID_BUOBJECTLib>
{
public:
	CEmployee(): m_lEmployeeID(0)
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_EMPLOYEE)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CEmployee)
	COM_INTERFACE_ENTRY(IEmployee)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

// IEmployee
public:
	STDMETHOD(get_EmployeeID)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_EmployeeID)(/*[in]*/ long newVal);
	STDMETHOD(get_Name)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_Name)(/*[in]*/ BSTR newVal);
private:
   CComBSTR m_bstrName;
   long     m_lEmployeeID;

};

#endif //__EMPLOYEE_H_
