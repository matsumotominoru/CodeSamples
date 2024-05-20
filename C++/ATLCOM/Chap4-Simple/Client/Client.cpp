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
   ICalcEaster* pCalc;
   HRESULT hr;
   hr = CoCreateInstance( CLSID_CalcEaster,
                          NULL,
                          CLSCTX_ALL,
                          IID_ICalcEaster,
                          (void**)&pCalc );
   if (SUCCEEDED(hr))
   {
      short sYear = 1998, sMonth, sDay;
      pCalc->put_Year(sYear);
      pCalc->CalculateEaster();
      pCalc->get_Month(&sMonth);
      pCalc->get_Day(&sDay);
      _tprintf(_T("Easter day in %d is %d/%d/%d\n"),
          sYear, sDay, sMonth, sYear);
      pCalc->Release();
   }

   CoUninitialize();
   return 0;
}

