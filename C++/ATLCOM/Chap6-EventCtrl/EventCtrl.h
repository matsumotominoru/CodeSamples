/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Sun Jan 24 17:38:55 1999
 */
/* Compiler settings for I:\ATLCOM\MyProjects\EventCtrl\EventCtrl.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __EventCtrl_h__
#define __EventCtrl_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IEventSink_FWD_DEFINED__
#define __IEventSink_FWD_DEFINED__
typedef interface IEventSink IEventSink;
#endif 	/* __IEventSink_FWD_DEFINED__ */


#ifndef ___IEventSinkEvents_FWD_DEFINED__
#define ___IEventSinkEvents_FWD_DEFINED__
typedef interface _IEventSinkEvents _IEventSinkEvents;
#endif 	/* ___IEventSinkEvents_FWD_DEFINED__ */


#ifndef __EventControl_FWD_DEFINED__
#define __EventControl_FWD_DEFINED__

#ifdef __cplusplus
typedef class EventControl EventControl;
#else
typedef struct EventControl EventControl;
#endif /* __cplusplus */

#endif 	/* __EventControl_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IEventSink_INTERFACE_DEFINED__
#define __IEventSink_INTERFACE_DEFINED__

/* interface IEventSink */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEventSink;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("43D25519-B364-11D2-AC0F-0000B4725554")
    IEventSink : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OnEventSet( 
            /* [in] */ BSTR bstrEventName) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OnEventReset( 
            /* [in] */ BSTR bstrEventName) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEventSinkVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEventSink __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEventSink __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEventSink __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnEventSet )( 
            IEventSink __RPC_FAR * This,
            /* [in] */ BSTR bstrEventName);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnEventReset )( 
            IEventSink __RPC_FAR * This,
            /* [in] */ BSTR bstrEventName);
        
        END_INTERFACE
    } IEventSinkVtbl;

    interface IEventSink
    {
        CONST_VTBL struct IEventSinkVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEventSink_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEventSink_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEventSink_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEventSink_OnEventSet(This,bstrEventName)	\
    (This)->lpVtbl -> OnEventSet(This,bstrEventName)

#define IEventSink_OnEventReset(This,bstrEventName)	\
    (This)->lpVtbl -> OnEventReset(This,bstrEventName)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IEventSink_OnEventSet_Proxy( 
    IEventSink __RPC_FAR * This,
    /* [in] */ BSTR bstrEventName);


void __RPC_STUB IEventSink_OnEventSet_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IEventSink_OnEventReset_Proxy( 
    IEventSink __RPC_FAR * This,
    /* [in] */ BSTR bstrEventName);


void __RPC_STUB IEventSink_OnEventReset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEventSink_INTERFACE_DEFINED__ */



#ifndef __EVENTCTRLLib_LIBRARY_DEFINED__
#define __EVENTCTRLLib_LIBRARY_DEFINED__

/* library EVENTCTRLLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_EVENTCTRLLib;

#ifndef ___IEventSinkEvents_DISPINTERFACE_DEFINED__
#define ___IEventSinkEvents_DISPINTERFACE_DEFINED__

/* dispinterface _IEventSinkEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__IEventSinkEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("43D2551A-B364-11D2-AC0F-0000B4725554")
    _IEventSinkEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IEventSinkEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            _IEventSinkEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            _IEventSinkEvents __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            _IEventSinkEvents __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            _IEventSinkEvents __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            _IEventSinkEvents __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            _IEventSinkEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            _IEventSinkEvents __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } _IEventSinkEventsVtbl;

    interface _IEventSinkEvents
    {
        CONST_VTBL struct _IEventSinkEventsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IEventSinkEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _IEventSinkEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _IEventSinkEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _IEventSinkEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _IEventSinkEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _IEventSinkEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _IEventSinkEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IEventSinkEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_EventControl;

#ifdef __cplusplus

class DECLSPEC_UUID("A0BA7627-771B-11D2-AB96-0000B4725554")
EventControl;
#endif
#endif /* __EVENTCTRLLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long __RPC_FAR *, unsigned long            , BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long __RPC_FAR *, BSTR __RPC_FAR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
