// Main.cpp
#import "..\ComDialogProject.tlb"
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
	}
	catch (const _com_error& Err)
	{
		std::cout << Err.ErrorMessage() << "0x" << std::hex << Err.Error() << '\n';
		hr = Err.Error();
	}

	CoUninitialize();
	return hr;
}