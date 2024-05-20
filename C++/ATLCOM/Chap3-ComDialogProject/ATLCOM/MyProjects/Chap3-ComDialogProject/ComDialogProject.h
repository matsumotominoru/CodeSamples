/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Tue Oct 27 00:10:37 1998
 */
/* Compiler settings for G:\Program Files\Microsoft Visual Studio\MyProjects\ComDialogProject\ComDialogProject.idl:
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

#ifndef __ComDialogProject_h__
#define __ComDialogProject_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IComDialog_FWD_DEFINED__
#define __IComDialog_FWD_DEFINED__
typedef interface IComDialog IComDialog;
#endif 	/* __IComDialog_FWD_DEFINED__ */


#ifndef __ComDialog_FWD_DEFINED__
#define __ComDialog_FWD_DEFINED__

#ifdef __cplusplus
typedef class ComDialog ComDialog;
#else
typedef struct ComDialog ComDialog;
#endif /* __cplusplus */

#endif 	/* __ComDialog_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IComDialog_INTERFACE_DEFINED__
#define __IComDialog_INTERFACE_DEFINED__

/* interface IComDialog */
/* [object][helpstring][unique][oleautomation][uuid] */ 


EXTERN_C const IID IID_IComDialog;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("624235B3-64CB-11D1-A159-64D6F8C00000")
    IComDialog : public IUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Visible( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbVisible) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Visible( 
            /* [in] */ VARIANT_BOOL bVisible) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IComDialogVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IComDialog __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IComDialog __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IComDialog __RPC_FAR * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Visible )( 
            IComDialog __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbVisible);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Visible )( 
            IComDialog __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL bVisible);
        
        END_INTERFACE
    } IComDialogVtbl;

    interface IComDialog
    {
        CONST_VTBL struct IComDialogVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IComDialog_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IComDialog_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IComDialog_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IComDialog_get_Visible(This,pbVisible)	\
    (This)->lpVtbl -> get_Visible(This,pbVisible)

#define IComDialog_put_Visible(This,bVisible)	\
    (This)->lpVtbl -> put_Visible(This,bVisible)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IComDialog_get_Visible_Proxy( 
    IComDialog __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbVisible);


void __RPC_STUB IComDialog_get_Visible_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IComDialog_put_Visible_Proxy( 
    IComDialog __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL bVisible);


void __RPC_STUB IComDialog_put_Visible_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IComDialog_INTERFACE_DEFINED__ */



#ifndef __COMDIALOGPROJECTLib_LIBRARY_DEFINED__
#define __COMDIALOGPROJECTLib_LIBRARY_DEFINED__

/* library COMDIALOGPROJECTLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_COMDIALOGPROJECTLib;

EXTERN_C const CLSID CLSID_ComDialog;

#ifdef __cplusplus

class DECLSPEC_UUID("D55039F0-61B3-11D1-B28D-00A0C94515AD")
ComDialog;
#endif
#endif /* __COMDIALOGPROJECTLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
