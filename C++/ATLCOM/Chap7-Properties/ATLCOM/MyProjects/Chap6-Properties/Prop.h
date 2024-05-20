// Prop.h : Declaration of the CProp

#ifndef __PROP_H_
#define __PROP_H_

#include "resource.h"       // ÉÅÉCÉì ÉVÉìÉ{Éã
#include "PropObj.h"			// ADD
#include <atlctl.h>



/////////////////////////////////////////////////////////////////////////////
// CProp
class ATL_NO_VTABLE CProp : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CStockPropImpl<CProp, IProp, &IID_IProp, &LIBID_PROPERTIESLib>,
	public CComControl<CProp>,
	public IPersistStreamInitImpl<CProp>,
	public IOleControlImpl<CProp>,
	public IOleObjectImpl<CProp>,
	public IOleInPlaceActiveObjectImpl<CProp>,
	public IViewObjectExImpl<CProp>,
	public IOleInPlaceObjectWindowlessImpl<CProp>,
	public IPersistStorageImpl<CProp>,
	public IPersistPropertyBagImpl<CProp>,  // ADD
	public ISpecifyPropertyPagesImpl<CProp>,
	public IQuickActivateImpl<CProp>,
	public IDataObjectImpl<CProp>,
	public IProvideClassInfo2Impl<&CLSID_Prop, NULL, &LIBID_PROPERTIESLib>,
	public CComCoClass<CProp, &CLSID_Prop>
{
public:
	CProp(): m_clrForeColor(0), m_clrBackColor(0xffffff), m_lNumber(0),m_bInitialized(false)
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_PROP)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CProp)
	COM_INTERFACE_ENTRY(IProp)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY_IMPL(IPersistPropertyBag)	// ADD
	COM_INTERFACE_ENTRY(IViewObjectEx)
	COM_INTERFACE_ENTRY(IViewObject2)
	COM_INTERFACE_ENTRY(IViewObject)
	COM_INTERFACE_ENTRY(IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY(IOleInPlaceObject)
	COM_INTERFACE_ENTRY2(IOleWindow, IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY(IOleInPlaceActiveObject)
	COM_INTERFACE_ENTRY(IOleControl)
	COM_INTERFACE_ENTRY(IOleObject)
	COM_INTERFACE_ENTRY(IPersistStreamInit)
	COM_INTERFACE_ENTRY2(IPersist, IPersistStreamInit)
	COM_INTERFACE_ENTRY(ISpecifyPropertyPages)
	COM_INTERFACE_ENTRY(IQuickActivate)
	COM_INTERFACE_ENTRY(IPersistStorage)
	COM_INTERFACE_ENTRY(IDataObject)
	COM_INTERFACE_ENTRY(IProvideClassInfo)
	COM_INTERFACE_ENTRY(IProvideClassInfo2)
END_COM_MAP()

BEGIN_PROP_MAP(CProp)
//	PROP_DATA_ENTRY("_cx", m_sizeExtent.cx, VT_UI4)
//	PROP_DATA_ENTRY("_cy", m_sizeExtent.cy, VT_UI4)
//	PROP_ENTRY("BackColor", DISPID_BACKCOLOR, CLSID_StockColorPage)
//	PROP_ENTRY("Caption", DISPID_CAPTION, CLSID_NULL)
//	PROP_ENTRY("ForeColor", DISPID_FORECOLOR, CLSID_StockColorPage)
	// Example entries
	// PROP_ENTRY("Property Description", dispid, clsid)
	// PROP_PAGE(CLSID_StockColorPage)
   PROP_ENTRY("BackColor", DISPID_BACKCOLOR, CLSID_StockColorPage)
   PROP_ENTRY("ForeColor", DISPID_FORECOLOR, CLSID_StockColorPage)
   PROP_ENTRY("Caption", DISPID_CAPTION, CLSID_NULL)
   PROP_ENTRY("String", 1, CLSID_NULL)
   PROP_ENTRY("Number", 2, CLSID_NULL)
   PROP_ENTRY("PropObj", 3, CLSID_NULL)	// ADD


END_PROP_MAP()

BEGIN_MSG_MAP(CProp)
	CHAIN_MSG_MAP(CComControl<CProp>)
	DEFAULT_REFLECTION_HANDLER()
	MESSAGE_HANDLER(WM_LBUTTONDOWN, OnClick)
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

   LRESULT OnClick(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

// IViewObjectEx
//	DECLARE_VIEW_STATUS(VIEWSTATUS_SOLIDBKGND | VIEWSTATUS_OPAQUE)
// IViewObjectEx
   STDMETHOD(GetViewStatus)(DWORD* pdwStatus)
   {
      ATLTRACE(_T("IViewObjectExImpl::GetViewStatus\n"));
      *pdwStatus = VIEWSTATUS_SOLIDBKGND | VIEWSTATUS_OPAQUE;
      return S_OK;
   }

// IPersistStreamInit
   STDMETHOD(InitNew)();
   STDMETHOD(Load)(LPSTREAM pStm);
   bool m_bInitialized;



// IProp
public:
	STDMETHOD(get_Obj)(/*[out, retval]*/ LPDISPATCH *pVal);
	STDMETHOD(put_Obj)(/*[in]*/ LPDISPATCH newVal);
	STDMETHOD(get_Number)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_Number)(/*[in]*/ long newVal);
	STDMETHOD(get_String)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_String)(/*[in]*/ BSTR newVal);

	HRESULT OnDraw(ATL_DRAWINFO& di)
	{
//		Rectangle(di.hdcDraw, rc.left, rc.top, rc.right, rc.bottom);
/*
		SetTextAlign(di.hdcDraw, TA_CENTER|TA_BASELINE);
		LPCTSTR pszText = _T("ATL 3.0 : Prop");
		TextOut(di.hdcDraw, 
			(rc.left + rc.right) / 2, 
			(rc.top + rc.bottom) / 2, 
			pszText, 
			lstrlen(pszText));
*/
   USES_CONVERSION;
   int iMode = SetMapMode(di.hdcDraw, MM_TEXT);
   RECT& rc = *(RECT*)di.prcBounds;

   COLORREF clrFront, clrBack;
   HBRUSH hOldBrush, hBrush;
   HPEN hOldPen, hPen;

   OleTranslateColor(m_clrBackColor, NULL, &clrBack);
   OleTranslateColor(m_clrForeColor, NULL, &clrFront);

   hBrush = CreateSolidBrush(clrBack);
   hOldBrush = (HBRUSH)SelectObject(di.hdcDraw, hBrush);
   hPen = CreatePen(PS_SOLID, 1, clrFront);
   hOldPen = (HPEN)SelectObject(di.hdcDraw, hPen);

   Rectangle(di.hdcDraw, rc.left, rc.top, rc.right, rc.bottom);

   SetTextColor(di.hdcDraw, clrFront);
   SetBkColor(di.hdcDraw, clrBack);

   CComBSTR bstrText;
   bstrText = _T("Caption: ");
   bstrText += m_bstrCaption;
   ExtTextOut(di.hdcDraw, rc.left + 2, 2 + rc.top, ETO_CLIPPED, 
      &rc, OLE2T(bstrText.m_str), bstrText.Length(), NULL);

   bstrText = _T("String: ");
   bstrText += m_bstrString;
   ExtTextOut(di.hdcDraw, rc.left + 2, 2 + rc.top + 25, ETO_CLIPPED,
      &rc, OLE2T(bstrText.m_str), bstrText.Length(), NULL);

   bstrText = _T("Number: ");
   TCHAR szNum[12];
   wsprintf(szNum, _T("%ld"), m_lNumber);
   bstrText += szNum;
   ExtTextOut(di.hdcDraw, rc.left + 2, 2 + rc.top + 50, ETO_CLIPPED,
      &rc, OLE2T(bstrText.m_str), bstrText.Length(), NULL);

   bstrText = _T("Embedded Object");
   ExtTextOut(di.hdcDraw, rc.left + 2, 2 + rc.top + 75, ETO_CLIPPED, &rc,
      OLE2T(bstrText.m_str), bstrText.Length(), NULL);

   bstrText = _T("  .ObjString: ");
   CComBSTR str;
   long num;
   GetPropObj(str, &num);
   bstrText += str;
   ExtTextOut(di.hdcDraw, rc.left + 2, 2 + rc.top + 100, ETO_CLIPPED, &rc,
      OLE2T(bstrText.m_str), bstrText.Length(), NULL);

   bstrText = _T("  .ObjNumber: ");
   wsprintf(szNum, _T("%ld"), num);
   bstrText += szNum;
   ExtTextOut(di.hdcDraw, rc.left + 2, 2 + rc.top + 125, ETO_CLIPPED, &rc,
      OLE2T(bstrText.m_str), bstrText.Length(), NULL);

   SelectObject(di.hdcDraw, hOldBrush);
   DeleteObject(hBrush);
   SelectObject(di.hdcDraw, hOldPen);
   DeleteObject(hPen);
   SetMapMode(di.hdcDraw, iMode);


		return S_OK;
	}

	OLE_COLOR m_clrBackColor;
	CComBSTR m_bstrCaption;
	OLE_COLOR m_clrForeColor;
   CComBSTR m_bstrString;
   long m_lNumber;
   CComQIPtr<IPropObj, &IID_IPropObj> m_Obj;

private:
   bool GetPropObj(CComBSTR& bstr, long* lVal);


};

#endif //__PROP_H_
