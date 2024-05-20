// ColorClient.cpp
#include <windows.h>
#include <stdio.h>
#include <tchar.h>

#import "..\Colors.tlb"

using namespace COLORSLib;

void _tmain()
{
   CoInitialize(NULL);

   try
   {
      IColorObjectPtr pSA(__uuidof(ColorObject));
      _variant_t var = pSA->Colors;
      SAFEARRAY* psa = var.parray;
      BSTR* bstrArray;
      SafeArrayAccessData(psa, (void**)&bstrArray);
      for (UINT i = 0; i < psa->rgsabound->cElements; i++)
         _tprintf(_T("%ls\n"), bstrArray[i]);
      SafeArrayUnaccessData(psa);
   }
   catch(_com_error e)
   {
      _tprintf(_T("Error: 0x%08x %ls\n"), e.Error(), e.ErrorMessage());
   }

   CoUninitialize();
}
