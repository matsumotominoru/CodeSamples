// ComDll.cpp

// The module's lock count
static long g_lLockCount = 0;


// Create class factory as global
#include "WroxClassFactory.h"
static CWroxClassFactory g_WroxClassFactory;

// 
#include "ComDll_IDL_i.c"


extern "C"
BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID /*lpReserved*/)
{
	// No implementation needed here
	return TRUE;
}

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID   riid, LPVOID*  ppv)
{
   if (rclsid == CLSID_WroxComponent)
      return g_WroxClassFactory.QueryInterface(riid, ppv);
   else
   {
      *ppv = NULL;
      return CLASS_E_CLASSNOTAVAILABLE;
   }
}

STDAPI DllCanUnloadNow(void)
{
	return (g_lLockCount == 0) ? S_OK : S_FALSE;
}


STDAPI DllRegisterServer(void)
{
	return S_OK;
}

STDAPI DllUnregisterServer(void)
{
	return S_OK;
}