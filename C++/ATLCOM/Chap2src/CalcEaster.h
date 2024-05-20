// CalcEaster.h : CCalcEaster ÇÃêÈåæ

#ifndef __CALCEASTER_H_
#define __CALCEASTER_H_

#include "resource.h"       // ÉÅÉCÉì ÉVÉìÉ{Éã

/////////////////////////////////////////////////////////////////////////////
// CCalcEaster
class ATL_NO_VTABLE CCalcEaster : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CCalcEaster, &CLSID_CalcEaster>,
	public IDispatchImpl<ICalcEaster, &IID_ICalcEaster, &LIBID_SIMPLELib>
{
public:
	CCalcEaster():m_Year(-1),m_Month(-1),m_Day(-1)
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_CALCEASTER)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CCalcEaster)
	COM_INTERFACE_ENTRY(ICalcEaster)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

private:
	short	m_Year;
	short	m_Month;
	short	m_Day;

// ICalcEaster
public:
	STDMETHOD(CalculateEaster)();
	STDMETHOD(get_Day)(/*[out, retval]*/ short *pVal);
	STDMETHOD(get_Month)(/*[out, retval]*/ short *pVal);
	STDMETHOD(get_Year)(/*[out, retval]*/ short *pVal);
	STDMETHOD(put_Year)(/*[in]*/ short newVal);
};

#endif //__CALCEASTER_H_
