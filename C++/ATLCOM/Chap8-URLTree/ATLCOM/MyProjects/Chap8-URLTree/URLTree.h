/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Fri Nov 27 23:29:18 1998
 */
/* Compiler settings for G:\Program Files\Microsoft Visual Studio\MyProjects\URLTree\URLTree.idl:
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

#ifndef __URLTree_h__
#define __URLTree_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IURLTreeView_FWD_DEFINED__
#define __IURLTreeView_FWD_DEFINED__
typedef interface IURLTreeView IURLTreeView;
#endif 	/* __IURLTreeView_FWD_DEFINED__ */


#ifndef __URLTreeView_FWD_DEFINED__
#define __URLTreeView_FWD_DEFINED__

#ifdef __cplusplus
typedef class URLTreeView URLTreeView;
#else
typedef struct URLTreeView URLTreeView;
#endif /* __cplusplus */

#endif 	/* __URLTreeView_FWD_DEFINED__ */


#ifndef __URLPage_FWD_DEFINED__
#define __URLPage_FWD_DEFINED__

#ifdef __cplusplus
typedef class URLPage URLPage;
#else
typedef struct URLPage URLPage;
#endif /* __cplusplus */

#endif 	/* __URLPage_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IURLTreeView_INTERFACE_DEFINED__
#define __IURLTreeView_INTERFACE_DEFINED__

/* interface IURLTreeView */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IURLTreeView;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("26A4A47E-85A1-11D2-ABC6-0000B4725554")
    IURLTreeView : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_URLs( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_URLs( 
            /* [in] */ VARIANT newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IURLTreeViewVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IURLTreeView __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IURLTreeView __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IURLTreeView __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IURLTreeView __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IURLTreeView __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IURLTreeView __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IURLTreeView __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_URLs )( 
            IURLTreeView __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_URLs )( 
            IURLTreeView __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        END_INTERFACE
    } IURLTreeViewVtbl;

    interface IURLTreeView
    {
        CONST_VTBL struct IURLTreeViewVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IURLTreeView_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IURLTreeView_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IURLTreeView_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IURLTreeView_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IURLTreeView_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IURLTreeView_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IURLTreeView_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IURLTreeView_get_URLs(This,pVal)	\
    (This)->lpVtbl -> get_URLs(This,pVal)

#define IURLTreeView_put_URLs(This,newVal)	\
    (This)->lpVtbl -> put_URLs(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IURLTreeView_get_URLs_Proxy( 
    IURLTreeView __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IURLTreeView_get_URLs_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IURLTreeView_put_URLs_Proxy( 
    IURLTreeView __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IURLTreeView_put_URLs_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IURLTreeView_INTERFACE_DEFINED__ */



#ifndef __URLTREELib_LIBRARY_DEFINED__
#define __URLTREELib_LIBRARY_DEFINED__

/* library URLTREELib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_URLTREELib;

EXTERN_C const CLSID CLSID_URLTreeView;

#ifdef __cplusplus

class DECLSPEC_UUID("26A4A47F-85A1-11D2-ABC6-0000B4725554")
URLTreeView;
#endif

EXTERN_C const CLSID CLSID_URLPage;

#ifdef __cplusplus

class DECLSPEC_UUID("7FD41ADD-85F8-11D2-ABC7-0000B4725554")
URLPage;
#endif
#endif /* __URLTREELib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  VARIANT_UserSize(     unsigned long __RPC_FAR *, unsigned long            , VARIANT __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  VARIANT_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, VARIANT __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  VARIANT_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, VARIANT __RPC_FAR * ); 
void                      __RPC_USER  VARIANT_UserFree(     unsigned long __RPC_FAR *, VARIANT __RPC_FAR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
