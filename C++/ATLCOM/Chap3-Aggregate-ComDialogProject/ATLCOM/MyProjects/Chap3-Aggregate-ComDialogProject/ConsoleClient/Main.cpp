// Main.cpp
#include "Tchar.h"						// ..ADD
#import "..\ComDialogProject.tlb"
#import "..\..\Simple\Simple.tlb"		// ..ADD
#include <iostream>

int main(int argc, char* argv[], char* envp[ ])
{
	HRESULT hr = CoInitialize(NULL);
	if (FAILED(hr))
		return hr;

	try
	{
		COMDIALOGPROJECTLib::IComDialogPtr p(__uuidof(COMDIALOGPROJECTLib::ComDialog));
		p->Visible = VARIANT_TRUE;
		SIMPLELib::ICalcEasterPtr pCalcEaster( p );		// ..ADD
        pCalcEaster->Year = 1984;						// ..ADD
        pCalcEaster->CalculateEaster();					// ..ADD

        TCHAR buff[255] = {0};							// ..ADD
        wsprintf(buff, _T("Easter was %d/%d in %d"), pCalcEaster->Day, pCalcEaster->Month, pCalcEaster->Year);
        MessageBox(NULL, buff, _T("Calculation"), MB_OK);	// ..ADD
	}
	catch (const _com_error& Err)
	{
		std::cout << Err.ErrorMessage() << "0x" << std::hex << Err.Error() << '\n';
		hr = Err.Error();
	}

	CoUninitialize();
	return hr;
}