// Events.cpp : CEvents のインプリメンテーション
#include "stdafx.h"
#include "EventWatcher.h"
#include "Events.h"
#include <process.h>
//#include "..\EventCtrl\EventCtrl_i.c"

/////////////////////////////////////////////////////////////////////////////
// CEvents


STDMETHODIMP CEvents::WatchEvent(wchar_t *strEventName)
{
	// TODO: この位置にインプリメント用のコードを追加してください
   HANDLE hEvent;
#ifdef WINNT
   hEvent = OpenEventW(EVENT_ALL_ACCESS, false, strEventName);
#else
   USES_CONVERSION;
   hEvent = OpenEvent(EVENT_ALL_ACCESS, false, W2A(strEventName));
#endif

   if (hEvent == NULL)
      return E_POINTER;

   m_bEventState = (WAIT_OBJECT_0 == WaitForSingleObject(hEvent, 0));

   if (m_hThread != NULL)
   {
      // Thread is already active, so suspend it and change the values
      SuspendThread(m_hThread);

      delete [] m_strEventName;
      m_strEventName = new  WCHAR[wcslen(strEventName)+1];
      wcscpy(m_strEventName, strEventName);
      CloseHandle(m_hEvent);
      m_hEvent = hEvent;
      ResumeThread(m_hThread);

      return S_OK;
   }

   // Set up the values
   m_hEvent = hEvent;
   m_hDie = CreateEvent(NULL, true, false, NULL);
   m_strEventName = new WCHAR[wcslen(strEventName)+1];
   wcscpy(m_strEventName, strEventName);

   // Start thread to watch this event
   unsigned threadID;
   m_hThread = (HANDLE)_beginthreadex( NULL, 0, Watch,
                                       reinterpret_cast<void*>(this),
                                       0, &threadID );
	return S_OK;
}

STDMETHODIMP CEvents::SetInterval(LONG lInterval)
{
	// TODO: この位置にインプリメント用のコードを追加してください
   if (lInterval < 100)
      return E_FAIL;

   m_dwInterval = lInterval;

	return S_OK;
}

unsigned __stdcall CEvents::Watch(LPVOID pThis)
{
   CEvents* pThisObject = static_cast<CEvents*>(pThis);
   CoInitializeEx(NULL, COINIT_MULTITHREADED);

   while(true)
   {
      if (WAIT_OBJECT_0 == WaitForSingleObject(pThisObject->m_hDie, 0))
         break;
      
      if (WAIT_TIMEOUT == WaitForSingleObject(pThisObject->m_hEvent, 0))
      {
         // Event is not signalled

         if (pThisObject->m_bEventState)
         {
            // Previously signaled, state changed
            pThisObject->m_bEventState = false;
            pThisObject->Fire_OnEventReset(CComBSTR(pThisObject->m_strEventName));
         }

      }
      else
      {
         // Event is signalled

		  if (!pThisObject->m_bEventState)
         {
            // Previously not signaled, state changed
            pThisObject->m_bEventState = true;
            pThisObject->Fire_OnEventSet(CComBSTR(pThisObject->m_strEventName));
         }

      }
      Sleep(pThisObject->m_dwInterval);
   }

   CoUninitialize();
   return 0;
}

void CEvents::FinalRelease()
{
   // Tell the thread to die
   SetEvent(m_hDie);

   // Wait for it to die
   WaitForSingleObject(m_hThread, INFINITE);

   if (m_strEventName)
      delete [] m_strEventName;
   CloseHandle(m_hDie);
   CloseHandle(m_hEvent);
   CloseHandle(m_hThread);
}
