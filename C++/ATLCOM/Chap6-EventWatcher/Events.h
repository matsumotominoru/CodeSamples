// Events.h : CEvents ÇÃêÈåæ

#ifndef __EVENTS_H_
#define __EVENTS_H_

#include "resource.h"       // ÉÅÉCÉì ÉVÉìÉ{Éã
#include "EventWatcherCP.h"
#include "EventCtrlCP.h"



/////////////////////////////////////////////////////////////////////////////
// CEvents
class ATL_NO_VTABLE CEvents : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CEvents, &CLSID_Events>,
	public IConnectionPointContainerImpl<CEvents>,
	public IEvents,
	public CProxy_IEventSinkEvents< CEvents >
{
public:
	CEvents(): m_dwInterval(500),
               m_strEventName(NULL),
               m_hThread(NULL),
               m_hDie(NULL),
               m_hEvent(NULL),
               m_bEventState(false)

	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_EVENTS)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CEvents)
	COM_INTERFACE_ENTRY(IEvents)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
//	COM_INTERFACE_ENTRY(IEventSink)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CEvents)
//CONNECTION_POINT_ENTRY(DIID__IEventSinkEvents)

CONNECTION_POINT_ENTRY(DIID__IEventSinkEvents)
END_CONNECTION_POINT_MAP()


// IEvents
public:
	STDMETHOD(SetInterval)(/*[in]*/ LONG lInterval);
	STDMETHOD(WatchEvent)(/*[in,string]*/ wchar_t* strEventName);
	void FinalRelease();
private:
   static unsigned __stdcall Watch(LPVOID pThis);
   LPWSTR m_strEventName;
   DWORD  m_dwInterval;
   HANDLE m_hThread;
   HANDLE m_hDie;
   HANDLE m_hEvent;
   BOOL m_bEventState;

// IEventSink
 
	STDMETHOD(OnEventSet)(BSTR bstrEventName)
	{
		return E_NOTIMPL;
	}
	STDMETHOD(OnEventReset)(BSTR bstrEventName)
	{
		return E_NOTIMPL;
	}
};

#endif //__EVENTS_H_
