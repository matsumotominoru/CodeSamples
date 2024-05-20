#import "..\ReturningAnObject.tlb"
using namespace RETURNINGANOBJECTLib;
#include <iostream>
using namespace std;

int main()
{
	CoInitialize(NULL);
	try
	{
		IMainObjectPtr pMain(__uuidof(MainObject));
		pMain->Display();

		// Uncomment the following line to trigger a compile-time error
		// We removed the SeparateObject coclass from the server's IDL file
		// ISeparateObjectPtr pCantCreateSep(__uuidof(SeparateObject));
		ISeparateObjectPtr pSep = pMain->CreateSeparateObject();
		pSep->Display();

		ISeparateObjectPtr pSepInit = pMain->CreateAndInitializeSeparateObject();
		pSepInit->Display();
	}
	catch (const _com_error& Err)
	{
		cout << Err.ErrorMessage()
			<< hex << "0x" << Err.Error() << '\n'; 
	}
	CoUninitialize();
	return 0;
}
