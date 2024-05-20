// AutoClient.cpp : コンソール アプリケーション用のエントリ ポイントの定義
//

#include "stdafx.h"

#include <windows.h>
#include <stdio.h>
#include <tchar.h>

#import "..\automation.tlb"

using namespace AUTOMATIONLib;

int _tmain(int argc, _TCHAR** argv)
{
   CoInitialize(NULL);

   try
   {
      IAutoPtr pAuto(__uuidof(Auto));
      IAuto2Ptr pAuto2 = pAuto;
	  IDispatchPtr pDisp = pAuto;
	  IDispatchPtr pDisp2 = pAuto2;

      // Get the user to pass values to the object
      TCHAR str[256];
      LONG lVal;
      while (true)
      {
         _tprintf(_T("(enter 0 to stop)> "));
         _tscanf(_T("%s"), str);
         lVal = _ttol(str);
         if (lVal == 0)
            break;
         try
         {
            pAuto->Value(lVal);
            pAuto2->Value2(lVal);
         }
         catch(_com_error e)
         {
            _tprintf(_T("There is an error")
             _T(" (%08x) in %s: \n\t\"%s\"\n"),
             e.Error(), (LPCSTR)e.Source(),
             (LPCSTR)e.Description());
         }
		          HRESULT hr;
         VARIANT varResult;
         VariantInit(&varResult);

         VARIANTARG vars;
         VariantInit(&vars);
         vars.vt = VT_I4;
         vars.lVal = lVal;

         DISPPARAMS disp = {&vars, NULL, 1, 0};
         EXCEPINFO excepInfo;
         hr = pDisp->Invoke(0x2, IID_NULL,
                            LOCALE_USER_DEFAULT,
                            DISPATCH_METHOD, &disp,
                            &varResult, &excepInfo,
                            NULL);

         if (hr == DISP_E_EXCEPTION)
         {
            _tprintf(_T("There is an error in Invoke()")
               _T(" (%08x) in %ls: \n\t\"%ls\"\n"),
               excepInfo.scode, excepInfo.bstrSource,
               excepInfo.bstrDescription);
            SysFreeString(excepInfo.bstrSource);
            SysFreeString(excepInfo.bstrDescription);
            SysFreeString(excepInfo.bstrHelpFile);
         }
         hr = pDisp2->Invoke(0x2, IID_NULL,
                             LOCALE_USER_DEFAULT,
                             DISPATCH_METHOD, &disp,
                             &varResult, &excepInfo,
                             NULL);

         if (hr == DISP_E_EXCEPTION)
         {
            _tprintf(_T("There is an error in Invoke()")
               _T(" (%08x) in %ls: \n\t\"%ls\"\n"),
               excepInfo.scode, excepInfo.bstrSource,
               excepInfo.bstrDescription);
            SysFreeString(excepInfo.bstrSource);
            SysFreeString(excepInfo.bstrDescription);
            SysFreeString(excepInfo.bstrHelpFile);
         }

      }
   }
   catch(_com_error e)
   {
      _tprintf(_T("There is an error (%08x):")
         _T(" %s\n"), e.Error(),
         e.ErrorMessage());
   }

   CoUninitialize();
   return 0;
}


