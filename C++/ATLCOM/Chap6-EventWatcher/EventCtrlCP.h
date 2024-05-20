#ifndef _EVENTCTRLCP_H_
#define _EVENTCTRLCP_H_

#import "I:\ATLCOM\MyProjects\EventCtrl\Debug\EventCtrl.dll" raw_interfaces_only, raw_native_types, no_namespace, named_guids	//"Import typelib"


template <class T>
class CProxy_IEventSinkEvents : public IConnectionPointImpl<T, &DIID__IEventSinkEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	HRESULT Fire_OnEventSet(
		BSTR bstrEventName)
	{
		T* pT = (T*)this;
		pT->Lock();
		HRESULT ret;
		IUnknown** pp = m_vec.begin();
		while (pp < m_vec.end())
		{
			if (*pp != NULL)
			{
				IEventSink* pIEventSink = reinterpret_cast<IEventSink*>(*pp);
				ret = pIEventSink->OnEventSet(bstrEventName);
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
	HRESULT Fire_OnEventReset(
		BSTR bstrEventName)
	{
		T* pT = (T*)this;
		pT->Lock();
		HRESULT ret;
		IUnknown** pp = m_vec.begin();
		while (pp < m_vec.end())
		{
			if (*pp != NULL)
			{
				IEventSink* pIEventSink = reinterpret_cast<IEventSink*>(*pp);
				ret = pIEventSink->OnEventReset(bstrEventName);
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
};

#endif