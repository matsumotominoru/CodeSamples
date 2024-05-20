// Client.cpp : コンソール アプリケーション用のエントリ ポイントの定義
//

#include "stdafx.h"
#include <stdio.h>
#include <tchar.h>

// Bring in the interface and GUID definitions
#include "..\simple.h"
#include "..\simple_i.c"

int main()
{
   CoInitialize(NULL);
   IDispatch* pObj;
   HRESULT hr = CoCreateInstance( CLSID_CalcEaster,
                                  NULL,
                                  CLSCTX_ALL,
                                  IID_IDispatch,
                                  (void**)&pObj );
   short sYear = 1998;

   VARIANTARG* pvars = new VARIANTARG[1];
   VariantInit(&pvars[0]);
   pvars[0].vt = VT_I2;
   pvars[0].iVal = sYear;
   DISPID dispid = DISPID_PROPERTYPUT;
   DISPPARAMS disp = { pvars, &dispid, 1, 1 };

   VARIANT varResult;
   VariantInit(&varResult);
   pObj->Invoke( 0x1,
                 IID_NULL,
                 LOCALE_USER_DEFAULT,
                 DISPATCH_PROPERTYPUT,
                 &disp,
                 &varResult, NULL, NULL );

   delete[] pvars;

   // Do other things with the object
   LPOLESTR pszName = L"CalculateEaster";
   pObj->GetIDsOfNames( IID_NULL,
                        &pszName,
                        1,
                        LOCALE_USER_DEFAULT,
                        &dispid );

   ITypeInfo* pType;
   pObj->GetTypeInfo(0, LOCALE_USER_DEFAULT, &pType);

   TYPEATTR* pTypeAttr;
   hr = pType->GetTypeAttr(&pTypeAttr);

   if (SUCCEEDED(hr))
   {
      for (short i = 0; i < pTypeAttr->cFuncs; i++)
      {
         FUNCDESC* pFuncDesc;
         hr = pType->GetFuncDesc(i, &pFuncDesc);
         if (SUCCEEDED(hr))
         {
            if (pFuncDesc->memid == dispid)
            {
               _tprintf(_T("returns %ld\n"),
                  pFuncDesc->elemdescFunc.tdesc.vt);
               for (short n = 0; n<pFuncDesc->cParams; n++)
               {
                  _tprintf(_T("param %ld is type %ld\n"), n,
                     pFuncDesc->lprgelemdescParam[n].tdesc.vt);
               }
            }
            pType->ReleaseFuncDesc(pFuncDesc);
         }
      }
      pType->ReleaseTypeAttr(pTypeAttr);
   }

   pType->Release();
   pObj->Release();
   CoUninitialize();
   return 0;
}

