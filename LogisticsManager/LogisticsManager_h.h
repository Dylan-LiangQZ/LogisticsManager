

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Sun Apr 21 15:51:55 2019
 */
/* Compiler settings for LogisticsManager.idl:
    Oicf, W1, Zp8, env=Win64 (32b run), target_arch=AMD64 8.00.0603 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__


#ifndef __LogisticsManager_h_h__
#define __LogisticsManager_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __ILogisticsManager_FWD_DEFINED__
#define __ILogisticsManager_FWD_DEFINED__
typedef interface ILogisticsManager ILogisticsManager;

#endif 	/* __ILogisticsManager_FWD_DEFINED__ */


#ifndef __LogisticsManager_FWD_DEFINED__
#define __LogisticsManager_FWD_DEFINED__

#ifdef __cplusplus
typedef class LogisticsManager LogisticsManager;
#else
typedef struct LogisticsManager LogisticsManager;
#endif /* __cplusplus */

#endif 	/* __LogisticsManager_FWD_DEFINED__ */


#ifndef __IUserLoginPage_FWD_DEFINED__
#define __IUserLoginPage_FWD_DEFINED__
typedef interface IUserLoginPage IUserLoginPage;

#endif 	/* __IUserLoginPage_FWD_DEFINED__ */


#ifndef __UserLoginPage_FWD_DEFINED__
#define __UserLoginPage_FWD_DEFINED__

#ifdef __cplusplus
typedef class UserLoginPage UserLoginPage;
#else
typedef struct UserLoginPage UserLoginPage;
#endif /* __cplusplus */

#endif 	/* __UserLoginPage_FWD_DEFINED__ */


#ifndef __IAddOrderPage_FWD_DEFINED__
#define __IAddOrderPage_FWD_DEFINED__
typedef interface IAddOrderPage IAddOrderPage;

#endif 	/* __IAddOrderPage_FWD_DEFINED__ */


#ifndef __CAddOrderPage_FWD_DEFINED__
#define __CAddOrderPage_FWD_DEFINED__

#ifdef __cplusplus
typedef class CAddOrderPage CAddOrderPage;
#else
typedef struct CAddOrderPage CAddOrderPage;
#endif /* __cplusplus */

#endif 	/* __CAddOrderPage_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __LogisticsManager_LIBRARY_DEFINED__
#define __LogisticsManager_LIBRARY_DEFINED__

/* library LogisticsManager */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_LogisticsManager;

#ifndef __ILogisticsManager_DISPINTERFACE_DEFINED__
#define __ILogisticsManager_DISPINTERFACE_DEFINED__

/* dispinterface ILogisticsManager */
/* [uuid] */ 


EXTERN_C const IID DIID_ILogisticsManager;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("32B476DB-609D-41C0-AE45-83BBCCADC14D")
    ILogisticsManager : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct ILogisticsManagerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ILogisticsManager * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ILogisticsManager * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ILogisticsManager * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ILogisticsManager * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ILogisticsManager * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ILogisticsManager * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ILogisticsManager * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } ILogisticsManagerVtbl;

    interface ILogisticsManager
    {
        CONST_VTBL struct ILogisticsManagerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILogisticsManager_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ILogisticsManager_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ILogisticsManager_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ILogisticsManager_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define ILogisticsManager_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define ILogisticsManager_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define ILogisticsManager_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __ILogisticsManager_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_LogisticsManager;

#ifdef __cplusplus

class DECLSPEC_UUID("7FF20474-B532-4E97-B339-4A7B356D1336")
LogisticsManager;
#endif

#ifndef __IUserLoginPage_DISPINTERFACE_DEFINED__
#define __IUserLoginPage_DISPINTERFACE_DEFINED__

/* dispinterface IUserLoginPage */
/* [uuid] */ 


EXTERN_C const IID DIID_IUserLoginPage;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("571160B3-5F1E-437E-AB49-259A8F4E7AC9")
    IUserLoginPage : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IUserLoginPageVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IUserLoginPage * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IUserLoginPage * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IUserLoginPage * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IUserLoginPage * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IUserLoginPage * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IUserLoginPage * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IUserLoginPage * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } IUserLoginPageVtbl;

    interface IUserLoginPage
    {
        CONST_VTBL struct IUserLoginPageVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IUserLoginPage_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IUserLoginPage_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IUserLoginPage_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IUserLoginPage_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IUserLoginPage_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IUserLoginPage_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IUserLoginPage_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IUserLoginPage_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_UserLoginPage;

#ifdef __cplusplus

class DECLSPEC_UUID("25ADB8AF-6A60-4A45-8D8A-5E56A2F1A660")
UserLoginPage;
#endif

#ifndef __IAddOrderPage_DISPINTERFACE_DEFINED__
#define __IAddOrderPage_DISPINTERFACE_DEFINED__

/* dispinterface IAddOrderPage */
/* [uuid] */ 


EXTERN_C const IID DIID_IAddOrderPage;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("4852161E-BE95-4EEE-B991-5ED0BFDD926F")
    IAddOrderPage : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IAddOrderPageVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAddOrderPage * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAddOrderPage * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAddOrderPage * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IAddOrderPage * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IAddOrderPage * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IAddOrderPage * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IAddOrderPage * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } IAddOrderPageVtbl;

    interface IAddOrderPage
    {
        CONST_VTBL struct IAddOrderPageVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAddOrderPage_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IAddOrderPage_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IAddOrderPage_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IAddOrderPage_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IAddOrderPage_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IAddOrderPage_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IAddOrderPage_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IAddOrderPage_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_CAddOrderPage;

#ifdef __cplusplus

class DECLSPEC_UUID("73E5533B-E650-4B2C-B47B-6A519418A3D5")
CAddOrderPage;
#endif
#endif /* __LogisticsManager_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


