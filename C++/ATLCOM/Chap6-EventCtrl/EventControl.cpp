// EventControl.cpp : CEventControl のインプリメンテーション

#include "stdafx.h"
#include "EventCtrl.h"
#include "EventControl.h"
#import "..\EventWatcher\EventWatcher.tlb" no_namespace, implementation_only
/////////////////////////////////////////////////////////////////////////////
// CEventControl


STDMETHODIMP CEventControl::OnEventSet(BSTR bstrEventName)
{
	// TODO: この位置にインプリメント用のコードを追加してください
   USES_CONVERSION;
   LPTSTR strEvt = OLE2T(bstrEventName);
   delete [] m_strEventStatus;

   // Save space for name and message
   m_strEventStatus = new TCHAR[lstrlen(strEvt) + 8];
   wsprintf(m_strEventStatus, _T("%s is SET"), strEvt);
   FireViewChange();
	return S_OK;
}

STDMETHODIMP CEventControl::OnEventReset(BSTR bstrEventName)
{
	// TODO: この位置にインプリメント用のコードを追加してください

   USES_CONVERSION;
   LPTSTR strEvt = OLE2T(bstrEventName);
   delete [] m_strEventStatus;

   // Save space for name and message
   m_strEventStatus = new TCHAR[lstrlen(strEvt) + 10];
   wsprintf(m_strEventStatus, _T("%s is RESET"), strEvt);
   FireViewChange();
	return S_OK;
}

HRESULT CEventControl::InPlaceActivate(LONG iVerb, const RECT* prcPosRect)
{
   HRESULT hr;
   hr = CComControlBase::InPlaceActivate(iVerb, prcPosRect);

   if (FAILED(hr) || iVerb != OLEIVERB_SHOW)
      return hr;

   // _com_ptr_t does not use CoCreateInstanceEx(), so we need
   // to do it and attach
   MULTI_QI qi[1] = {&__uuidof(IEventsPtr), NULL, S_OK};
   hr = CoCreateInstanceEx(__uuidof(Events), NULL, CLSCTX_ALL, NULL, 1, qi);

   if (SUCCEEDED(hr))
   {
      if (m_dwCookie)
         DisconnectServer();

      try
      {
         m_ptr.Attach(reinterpret_cast<IEvents*>(qi[0].pItf));

         // The event name
         LPWSTR strEventName = L"Test";

         // Make connection
         hr = AtlAdvise(m_ptr, this->GetUnknown(), IID_IEventSink,
            &m_dwCookie);
         if (FAILED(hr))
            _com_issue_error(hr);
         m_ptr->WatchEvent(strEventName);
      }
      catch (_com_error e)
      {
         ATLTRACE(_T("Cannot create server, %x"), e.Error());
         return e.Error();
      }
   }
   return 0;
}

void CEventControl::DisconnectServer()
{
   if (m_dwCookie)
      AtlUnadvise(m_ptr, IID_IEventSink, m_dwCookie);
   m_dwCookie = 0;
}

STDMETHODIMP CEventControl::Close(DWORD dwSaveOption)
{
   HRESULT hr;
   hr = IOleObjectImpl<CEventControl>::Close(dwSaveOption);
   if (m_dwCookie)
      DisconnectServer();
   return hr;
}
