// EventControl.h : Declaration of the CEventControl

#ifndef __EVENTCONTROL_H_
#define __EVENTCONTROL_H_

#include "resource.h"       // ÉÅÉCÉì ÉVÉìÉ{Éã
#include <atlctl.h>
#import "..\EventWatcher\EventWatcher.tlb" no_namespace, no_implementation

/////////////////////////////////////////////////////////////////////////////
// CEventControl
class ATL_NO_VTABLE CEventControl : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public IEventSink,
	public CComControl<CEventControl>,
	public IPersistStreamInitImpl<CEventControl>,
	public IOleControlImpl<CEventControl>,
	public IOleObjectImpl<CEventControl>,
	public IOleInPlaceActiveObjectImpl<CEventControl>,
	public IViewObjectExImpl<CEventControl>,
	public IOleInPlaceObjectWindowlessImpl<CEventControl>,
	public IConnectionPointContainerImpl<CEventControl>,
	public IPersistStorageImpl<CEventControl>,
	public ISpecifyPropertyPagesImpl<CEventControl>,
	public IQuickActivateImpl<CEventControl>,
	public IDataObjectImpl<CEventControl>,
	public IProvideClassInfo2Impl<&CLSID_EventControl, &DIID__IEventSinkEvents, &LIBID_EVENTCTRLLib>,
	public IPropertyNotifySinkCP<CEventControl>,
	public CComCoClass<CEventControl, &CLSID_EventControl>
{
public:
	CEventControl() : m_dwCookie(0)
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_EVENTCONTROL)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CEventControl)
	COM_INTERFACE_ENTRY(IEventSink)
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
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY(ISpecifyPropertyPages)
	COM_INTERFACE_ENTRY(IQuickActivate)
	COM_INTERFACE_ENTRY(IPersistStorage)
	COM_INTERFACE_ENTRY(IDataObject)
	COM_INTERFACE_ENTRY(IProvideClassInfo)
	COM_INTERFACE_ENTRY(IProvideClassInfo2)
END_COM_MAP()

BEGIN_PROP_MAP(CEventControl)
	PROP_DATA_ENTRY("_cx", m_sizeExtent.cx, VT_UI4)
	PROP_DATA_ENTRY("_cy", m_sizeExtent.cy, VT_UI4)
	// Example entries
	// PROP_ENTRY("Property Description", dispid, clsid)
	// PROP_PAGE(CLSID_StockColorPage)
END_PROP_MAP()

BEGIN_CONNECTION_POINT_MAP(CEventControl)
	CONNECTION_POINT_ENTRY(IID_IPropertyNotifySink)
END_CONNECTION_POINT_MAP()

BEGIN_MSG_MAP(CEventControl)
	CHAIN_MSG_MAP(CComControl<CEventControl>)
	DEFAULT_REFLECTION_HANDLER()
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);



// IViewObjectEx
	DECLARE_VIEW_STATUS(VIEWSTATUS_SOLIDBKGND | VIEWSTATUS_OPAQUE)

// IEventSink
public:
	STDMETHOD(OnEventReset)(/*[in]*/ BSTR bstrEventName);
	STDMETHOD(OnEventSet)(/*[in]*/ BSTR bstrEventName);

	HRESULT OnDraw(ATL_DRAWINFO& di)
	{
	   RECT& rc = *(RECT*)di.prcBounds;
	   Rectangle(di.hdcDraw, rc.left,  rc.top, rc.right, rc.bottom);
	   DrawText(di.hdcDraw, m_strEventStatus, -1, &rc,
		  DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		return S_OK;
	}

	HRESULT FinalConstruct()
	{
		m_strEventStatus = new TCHAR[14 * sizeof(TCHAR)];
		lstrcpy(m_strEventStatus, _T("Uninitialized"));
		return S_OK;
	}

	void FinalRelease()
	{
		delete [] m_strEventStatus;
	}
private:
	LPTSTR	m_strEventStatus;
	IEventsPtr	m_ptr;
	DWORD	m_dwCookie;
	void	DisconnectServer();
public:
   HRESULT InPlaceActivate(LONG iVerb, const RECT* prcPosRect);
   STDMETHOD(Close)(DWORD dwSaveOption);
};

#endif //__EVENTCONTROL_H_
