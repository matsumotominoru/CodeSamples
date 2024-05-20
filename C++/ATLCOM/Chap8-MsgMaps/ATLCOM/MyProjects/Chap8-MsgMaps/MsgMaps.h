/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Fri Nov 27 20:12:39 1998
 */
/* Compiler settings for G:\Program Files\Microsoft Visual Studio\MyProjects\MsgMaps\MsgMaps.idl:
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

#ifndef __MsgMaps_h__
#define __MsgMaps_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IClick_FWD_DEFINED__
#define __IClick_FWD_DEFINED__
typedef interface IClick IClick;
#endif 	/* __IClick_FWD_DEFINED__ */


#ifndef __Click_FWD_DEFINED__
#define __Click_FWD_DEFINED__

#ifdef __cplusplus
typedef class Click Click;
#else
typedef struct Click Click;
#endif /* __cplusplus */

#endif 	/* __Click_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IClick_INTERFACE_DEFINED__
#define __IClick_INTERFACE_DEFINED__

/* interface IClick */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IClick;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("26A4A470-85A1-11D2-ABC6-0000B4725554")
    IClick : public IDispatch
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct IClickVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IClick __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IClick __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IClick __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IClick __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IClick __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IClick __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IClick __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } IClickVtbl;

    interface IClick
    {
        CONST_VTBL struct IClickVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IClick_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IClick_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IClick_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IClick_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IClick_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IClick_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IClick_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IClick_INTERFACE_DEFINED__ */



#ifndef __MSGMAPSLib_LIBRARY_DEFINED__
#define __MSGMAPSLib_LIBRARY_DEFINED__

/* library MSGMAPSLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_MSGMAPSLib;

EXTERN_C const CLSID CLSID_Click;

#ifdef __cplusplus

class DECLSPEC_UUID("26A4A471-85A1-11D2-ABC6-0000B4725554")
Click;
#endif
#endif /* __MSGMAPSLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
