/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Wed Nov 04 23:38:13 1998
 */
/* Compiler settings for G:\Program Files\Microsoft Visual Studio\MyProjects\Automation\Automation.idl:
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

#ifndef __Automation_h__
#define __Automation_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IAuto_FWD_DEFINED__
#define __IAuto_FWD_DEFINED__
typedef interface IAuto IAuto;
#endif 	/* __IAuto_FWD_DEFINED__ */


#ifndef __IAuto2_FWD_DEFINED__
#define __IAuto2_FWD_DEFINED__
typedef interface IAuto2 IAuto2;
#endif 	/* __IAuto2_FWD_DEFINED__ */


#ifndef __Auto_FWD_DEFINED__
#define __Auto_FWD_DEFINED__

#ifdef __cplusplus
typedef class Auto Auto;
#else
typedef struct Auto Auto;
#endif /* __cplusplus */

#endif 	/* __Auto_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IAuto_INTERFACE_DEFINED__
#define __IAuto_INTERFACE_DEFINED__

/* interface IAuto */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IAuto;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("9542BEB1-6FB8-11D1-A607-00A0C94BC9C3")
    IAuto : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Greeting( 
            /* [in] */ BSTR bstrName,
            /* [retval][out] */ BSTR __RPC_FAR *bstrGreeting) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Value( 
            /* [in] */ LONG lVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAutoVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IAuto __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IAuto __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IAuto __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IAuto __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IAuto __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IAuto __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IAuto __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Greeting )( 
            IAuto __RPC_FAR * This,
            /* [in] */ BSTR bstrName,
            /* [retval][out] */ BSTR __RPC_FAR *bstrGreeting);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Value )( 
            IAuto __RPC_FAR * This,
            /* [in] */ LONG lVal);
        
        END_INTERFACE
    } IAutoVtbl;

    interface IAuto
    {
        CONST_VTBL struct IAutoVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAuto_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAuto_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAuto_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAuto_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IAuto_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IAuto_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IAuto_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IAuto_Greeting(This,bstrName,bstrGreeting)	\
    (This)->lpVtbl -> Greeting(This,bstrName,bstrGreeting)

#define IAuto_Value(This,lVal)	\
    (This)->lpVtbl -> Value(This,lVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAuto_Greeting_Proxy( 
    IAuto __RPC_FAR * This,
    /* [in] */ BSTR bstrName,
    /* [retval][out] */ BSTR __RPC_FAR *bstrGreeting);


void __RPC_STUB IAuto_Greeting_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAuto_Value_Proxy( 
    IAuto __RPC_FAR * This,
    /* [in] */ LONG lVal);


void __RPC_STUB IAuto_Value_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAuto_INTERFACE_DEFINED__ */


#ifndef __IAuto2_INTERFACE_DEFINED__
#define __IAuto2_INTERFACE_DEFINED__

/* interface IAuto2 */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IAuto2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("9542BEB3-6FB8-11D1-A607-00A0C94BC9C3")
    IAuto2 : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetGender( 
            /* [in] */ BSTR bstrName,
            /* [retval][out] */ BSTR __RPC_FAR *bstrGender) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Value2( 
            /* [in] */ LONG lVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAuto2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IAuto2 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IAuto2 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IAuto2 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IAuto2 __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IAuto2 __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IAuto2 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IAuto2 __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetGender )( 
            IAuto2 __RPC_FAR * This,
            /* [in] */ BSTR bstrName,
            /* [retval][out] */ BSTR __RPC_FAR *bstrGender);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Value2 )( 
            IAuto2 __RPC_FAR * This,
            /* [in] */ LONG lVal);
        
        END_INTERFACE
    } IAuto2Vtbl;

    interface IAuto2
    {
        CONST_VTBL struct IAuto2Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAuto2_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAuto2_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAuto2_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAuto2_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IAuto2_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IAuto2_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IAuto2_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IAuto2_GetGender(This,bstrName,bstrGender)	\
    (This)->lpVtbl -> GetGender(This,bstrName,bstrGender)

#define IAuto2_Value2(This,lVal)	\
    (This)->lpVtbl -> Value2(This,lVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAuto2_GetGender_Proxy( 
    IAuto2 __RPC_FAR * This,
    /* [in] */ BSTR bstrName,
    /* [retval][out] */ BSTR __RPC_FAR *bstrGender);


void __RPC_STUB IAuto2_GetGender_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAuto2_Value2_Proxy( 
    IAuto2 __RPC_FAR * This,
    /* [in] */ LONG lVal);


void __RPC_STUB IAuto2_Value2_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAuto2_INTERFACE_DEFINED__ */



#ifndef __AUTOMATIONLib_LIBRARY_DEFINED__
#define __AUTOMATIONLib_LIBRARY_DEFINED__

/* library AUTOMATIONLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_AUTOMATIONLib;

EXTERN_C const CLSID CLSID_Auto;

#ifdef __cplusplus

class DECLSPEC_UUID("9542BEB2-6FB8-11D1-A607-00A0C94BC9C3")
Auto;
#endif
#endif /* __AUTOMATIONLib_LIBRARY_DEFINED__ */

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
