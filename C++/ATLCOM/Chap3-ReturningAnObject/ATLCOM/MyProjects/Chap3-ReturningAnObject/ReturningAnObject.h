/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Wed Oct 28 14:10:12 1998
 */
/* Compiler settings for G:\Program Files\Microsoft Visual Studio\MyProjects\ReturningAnObject\ReturningAnObject.idl:
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

#ifndef __ReturningAnObject_h__
#define __ReturningAnObject_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IMainObject_FWD_DEFINED__
#define __IMainObject_FWD_DEFINED__
typedef interface IMainObject IMainObject;
#endif 	/* __IMainObject_FWD_DEFINED__ */


#ifndef __ISeparateObject_FWD_DEFINED__
#define __ISeparateObject_FWD_DEFINED__
typedef interface ISeparateObject ISeparateObject;
#endif 	/* __ISeparateObject_FWD_DEFINED__ */


#ifndef __MainObject_FWD_DEFINED__
#define __MainObject_FWD_DEFINED__

#ifdef __cplusplus
typedef class MainObject MainObject;
#else
typedef struct MainObject MainObject;
#endif /* __cplusplus */

#endif 	/* __MainObject_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_ReturningAnObject_0000 */
/* [local] */ 





extern RPC_IF_HANDLE __MIDL_itf_ReturningAnObject_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_ReturningAnObject_0000_v0_0_s_ifspec;

#ifndef __IMainObject_INTERFACE_DEFINED__
#define __IMainObject_INTERFACE_DEFINED__

/* interface IMainObject */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IMainObject;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("35494FBF-6E15-11D2-AB83-0000B4725554")
    IMainObject : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Display( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CreateSeparateObject( 
            /* [retval][out] */ ISeparateObject __RPC_FAR *__RPC_FAR *ppSep) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CreateAndInitializeSeparateObject( 
            /* [retval][out] */ ISeparateObject __RPC_FAR *__RPC_FAR *ppSep) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMainObjectVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IMainObject __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IMainObject __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IMainObject __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IMainObject __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IMainObject __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IMainObject __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IMainObject __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Display )( 
            IMainObject __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateSeparateObject )( 
            IMainObject __RPC_FAR * This,
            /* [retval][out] */ ISeparateObject __RPC_FAR *__RPC_FAR *ppSep);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateAndInitializeSeparateObject )( 
            IMainObject __RPC_FAR * This,
            /* [retval][out] */ ISeparateObject __RPC_FAR *__RPC_FAR *ppSep);
        
        END_INTERFACE
    } IMainObjectVtbl;

    interface IMainObject
    {
        CONST_VTBL struct IMainObjectVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMainObject_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMainObject_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMainObject_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMainObject_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IMainObject_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IMainObject_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IMainObject_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IMainObject_Display(This)	\
    (This)->lpVtbl -> Display(This)

#define IMainObject_CreateSeparateObject(This,ppSep)	\
    (This)->lpVtbl -> CreateSeparateObject(This,ppSep)

#define IMainObject_CreateAndInitializeSeparateObject(This,ppSep)	\
    (This)->lpVtbl -> CreateAndInitializeSeparateObject(This,ppSep)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMainObject_Display_Proxy( 
    IMainObject __RPC_FAR * This);


void __RPC_STUB IMainObject_Display_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMainObject_CreateSeparateObject_Proxy( 
    IMainObject __RPC_FAR * This,
    /* [retval][out] */ ISeparateObject __RPC_FAR *__RPC_FAR *ppSep);


void __RPC_STUB IMainObject_CreateSeparateObject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMainObject_CreateAndInitializeSeparateObject_Proxy( 
    IMainObject __RPC_FAR * This,
    /* [retval][out] */ ISeparateObject __RPC_FAR *__RPC_FAR *ppSep);


void __RPC_STUB IMainObject_CreateAndInitializeSeparateObject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMainObject_INTERFACE_DEFINED__ */


#ifndef __ISeparateObject_INTERFACE_DEFINED__
#define __ISeparateObject_INTERFACE_DEFINED__

/* interface ISeparateObject */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ISeparateObject;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("35494FC3-6E15-11D2-AB83-0000B4725554")
    ISeparateObject : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Display( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISeparateObjectVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ISeparateObject __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ISeparateObject __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ISeparateObject __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ISeparateObject __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ISeparateObject __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ISeparateObject __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ISeparateObject __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Display )( 
            ISeparateObject __RPC_FAR * This);
        
        END_INTERFACE
    } ISeparateObjectVtbl;

    interface ISeparateObject
    {
        CONST_VTBL struct ISeparateObjectVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISeparateObject_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ISeparateObject_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ISeparateObject_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ISeparateObject_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ISeparateObject_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ISeparateObject_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ISeparateObject_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ISeparateObject_Display(This)	\
    (This)->lpVtbl -> Display(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISeparateObject_Display_Proxy( 
    ISeparateObject __RPC_FAR * This);


void __RPC_STUB ISeparateObject_Display_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ISeparateObject_INTERFACE_DEFINED__ */



#ifndef __RETURNINGANOBJECTLib_LIBRARY_DEFINED__
#define __RETURNINGANOBJECTLib_LIBRARY_DEFINED__

/* library RETURNINGANOBJECTLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_RETURNINGANOBJECTLib;

EXTERN_C const CLSID CLSID_MainObject;

#ifdef __cplusplus

class DECLSPEC_UUID("35494FC2-6E15-11D2-AB83-0000B4725554")
MainObject;
#endif
#endif /* __RETURNINGANOBJECTLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
