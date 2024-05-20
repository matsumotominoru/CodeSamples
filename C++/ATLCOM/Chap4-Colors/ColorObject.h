// ColorObject.h : CColorObject の宣言

#ifndef __COLOROBJECT_H_
#define __COLOROBJECT_H_

#include "resource.h"       // メイン シンボル
#include <vector>			// 標準ライブラリのvectorクラスを使う...ADD

/////////////////////////////////////////////////////////////////////////////
// CColorObject
class ATL_NO_VTABLE CColorObject : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CColorObject, &CLSID_ColorObject>,
	public IDispatchImpl<IColorObject, &IID_IColorObject, &LIBID_COLORSLib>
{
public:
	CColorObject()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_COLOROBJECT)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CColorObject)
	COM_INTERFACE_ENTRY(IColorObject)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

// IColorObject
public:
	STDMETHOD(get_Colors)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(put_Colors)(/*[in]*/ VARIANT newVal);

	HRESULT	FinalConstruct();
private:
	std::vector<CComBSTR> m_vecColors;
	void DumpVector();
};

#endif //__COLOROBJECT_H_
