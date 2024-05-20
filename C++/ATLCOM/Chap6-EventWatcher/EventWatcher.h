/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Sun Jan 24 17:46:52 1999
 */
/* Compiler settings for I:\ATLCOM\MyProjects\EventWatcher\EventWatcher.idl:
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

#ifndef __EventWatcher_h__
#define __EventWatcher_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IEvents_FWD_DEFINED__
#define __IEvents_FWD_DEFINED__
typedef interface IEvents IEvents;
#endif 	/* __IEvents_FWD_DEFINED__ */


#ifndef ___IEventsEvents_FWD_DEFINED__
#define ___IEventsEvents_FWD_DEFINED__
typedef interface _IEventsEvents _IEventsEvents;
#endif 	/* ___IEventsEvents_FWD_DEFINED__ */


#ifndef __Events_FWD_DEFINED__
#define __Events_FWD_DEFINED__

#ifdef __cplusplus
typedef class Events Events;
#else
typedef struct Events Events;
#endif /* __cplusplus */

#endif 	/* __Events_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IEvents_INTERFACE_DEFINED__
#define __IEvents_INTERFACE_DEFINED__

/* interface IEvents */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C738A231-76D4-11D2-AB94-0000B4725554")
    IEvents : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE WatchEvent( 
            /* [string][in] */ wchar_t __RPC_FAR *strEventName) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetInterval( 
            /* [in] */ LONG lInterval) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEvents __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEvents __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *WatchEvent )( 
            IEvents __RPC_FAR * This,
            /* [string][in] */ wchar_t __RPC_FAR *strEventName);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetInterval )( 
            IEvents __RPC_FAR * This,
            /* [in] */ LONG lInterval);
        
        END_INTERFACE
    } IEventsVtbl;

    interface IEvents
    {
        CONST_VTBL struct IEventsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEvents_WatchEvent(This,strEventName)	\
    (This)->lpVtbl -> WatchEvent(This,strEventName)

#define IEvents_SetInterval(This,lInterval)	\
    (This)->lpVtbl -> SetInterval(This,lInterval)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IEvents_WatchEvent_Proxy( 
    IEvents __RPC_FAR * This,
    /* [string][in] */ wchar_t __RPC_FAR *strEventName);


void __RPC_STUB IEvents_WatchEvent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IEvents_SetInterval_Proxy( 
    IEvents __RPC_FAR * This,
    /* [in] */ LONG lInterval);


void __RPC_STUB IEvents_SetInterval_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEvents_INTERFACE_DEFINED__ */



#ifndef __EVENTWATCHERLib_LIBRARY_DEFINED__
#define __EVENTWATCHERLib_LIBRARY_DEFINED__

/* library EVENTWATCHERLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_EVENTWATCHERLib;

#ifndef ___IEventsEvents_DISPINTERFACE_DEFINED__
#define ___IEventsEvents_DISPINTERFACE_DEFINED__

/* dispinterface _IEventsEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__IEventsEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("C738A233-76D4-11D2-AB94-0000B4725554")
    _IEventsEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IEventsEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            _IEventsEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            _IEventsEvents __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            _IEventsEvents __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            _IEventsEvents __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            _IEventsEvents __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            _IEventsEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            _IEventsEvents __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } _IEventsEventsVtbl;

    interface _IEventsEvents
    {
        CONST_VTBL struct _IEventsEventsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IEventsEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _IEventsEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _IEventsEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _IEventsEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _IEventsEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _IEventsEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _IEventsEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IEventsEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_Events;

#ifdef __cplusplus

class DECLSPEC_UUID("C738A232-76D4-11D2-AB94-0000B4725554")
Events;
#endif
#endif /* __EVENTWATCHERLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
