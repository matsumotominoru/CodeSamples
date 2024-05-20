/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Sun Jan 24 22:07:08 1999
 */
/* Compiler settings for I:\ATLCOM\MyProjects\Chap1-ComDll\ComDll_IDL.idl:
    Os (OptLev=s), W1, Zp8, env=Win32, ms_ext, c_ext
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

#ifndef __ComDll_IDL_h__
#define __ComDll_IDL_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IWroxInterface_FWD_DEFINED__
#define __IWroxInterface_FWD_DEFINED__
typedef interface IWroxInterface IWroxInterface;
#endif 	/* __IWroxInterface_FWD_DEFINED__ */


#ifndef __IWroxSimple_FWD_DEFINED__
#define __IWroxSimple_FWD_DEFINED__
typedef interface IWroxSimple IWroxSimple;
#endif 	/* __IWroxSimple_FWD_DEFINED__ */


#ifndef __WroxComponent_FWD_DEFINED__
#define __WroxComponent_FWD_DEFINED__

#ifdef __cplusplus
typedef class WroxComponent WroxComponent;
#else
typedef struct WroxComponent WroxComponent;
#endif /* __cplusplus */

#endif 	/* __WroxComponent_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IWroxInterface_INTERFACE_DEFINED__
#define __IWroxInterface_INTERFACE_DEFINED__

/* interface IWroxInterface */
/* [uuid][object] */ 


EXTERN_C const IID IID_IWroxInterface;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("FEB89321-6D77-11d1-B28D-00A0C94515AD")
    IWroxInterface : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Alert( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWroxInterfaceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IWroxInterface __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IWroxInterface __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IWroxInterface __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Alert )( 
            IWroxInterface __RPC_FAR * This);
        
        END_INTERFACE
    } IWroxInterfaceVtbl;

    interface IWroxInterface
    {
        CONST_VTBL struct IWroxInterfaceVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWroxInterface_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IWroxInterface_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IWroxInterface_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IWroxInterface_Alert(This)	\
    (This)->lpVtbl -> Alert(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IWroxInterface_Alert_Proxy( 
    IWroxInterface __RPC_FAR * This);


void __RPC_STUB IWroxInterface_Alert_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWroxInterface_INTERFACE_DEFINED__ */


#ifndef __IWroxSimple_INTERFACE_DEFINED__
#define __IWroxSimple_INTERFACE_DEFINED__

/* interface IWroxSimple */
/* [uuid][object] */ 


EXTERN_C const IID IID_IWroxSimple;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("FEB89322-6D77-11d1-B28D-00A0C94515AD")
    IWroxSimple : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Display( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWroxSimpleVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IWroxSimple __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IWroxSimple __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IWroxSimple __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Display )( 
            IWroxSimple __RPC_FAR * This);
        
        END_INTERFACE
    } IWroxSimpleVtbl;

    interface IWroxSimple
    {
        CONST_VTBL struct IWroxSimpleVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWroxSimple_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IWroxSimple_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IWroxSimple_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IWroxSimple_Display(This)	\
    (This)->lpVtbl -> Display(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IWroxSimple_Display_Proxy( 
    IWroxSimple __RPC_FAR * This);


void __RPC_STUB IWroxSimple_Display_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWroxSimple_INTERFACE_DEFINED__ */



#ifndef __WroxComponentLib_LIBRARY_DEFINED__
#define __WroxComponentLib_LIBRARY_DEFINED__

/* library WroxComponentLib */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_WroxComponentLib;

EXTERN_C const CLSID CLSID_WroxComponent;

#ifdef __cplusplus

class DECLSPEC_UUID("FEB89324-6D77-11d1-B28D-00A0C94515AD")
WroxComponent;
#endif
#endif /* __WroxComponentLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
