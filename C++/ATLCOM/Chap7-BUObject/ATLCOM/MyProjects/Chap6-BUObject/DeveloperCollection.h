// DeveloperCollection.h : CDeveloperCollection ÇÃêÈåæ

#ifndef __DEVELOPERCOLLECTION_H_
#define __DEVELOPERCOLLECTION_H_

#include "resource.h"       // ÉÅÉCÉì ÉVÉìÉ{Éã
#include <map>
#include "Employee.h"
#pragma warning(disable : 4786)

struct BSTRless : std::binary_function<CComBSTR, CComBSTR, bool>
{
   bool operator()(const CComBSTR& _X, const CComBSTR& _Y) const
   {
      return (wcscmp(_X.m_str, _Y.m_str) > 0);
   }
};

/////////////////////////////////////////////////////////////////////////////
// CDeveloperCollection
class ATL_NO_VTABLE CDeveloperCollection : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CDeveloperCollection, &CLSID_DeveloperCollection>,
	public IDispatchImpl<IDeveloperCollection, &IID_IDeveloperCollection, &LIBID_BUOBJECTLib>
{
public:
	CDeveloperCollection()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_DEVELOPERCOLLECTION)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CDeveloperCollection)
	COM_INTERFACE_ENTRY(IDeveloperCollection)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

// IDeveloperCollection
public:
	STDMETHOD(get__NewEnum)(/*[out, retval]*/ LPUNKNOWN *pVal);
	STDMETHOD(Item)(/*[in]*/ VARIANT Index, /*[out, retval]*/ LPVARIANT pItem);
	STDMETHOD(get_Count)(/*[out, retval]*/ long *pVal);
	STDMETHOD(Add)(/*[in]*/ IEmployee* pEmployee);
   void FinalRelease();

private:
   std::map<CComBSTR, IEmployee*, BSTRless> m_map;
   void GetEmployee(IEmployee* pEmployee,
                    CComBSTR& bstrName, long& pEmployeeID);

};

#endif //__DEVELOPERCOLLECTION_H_
