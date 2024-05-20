// GetDiskSpace.cpp : コンソール アプリケーション用のエントリ ポイントの定義
//

#include "stdafx.h"
#define _WIN32_DCOM
#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <atlbase.h>
#include <atlimpl.cpp>

#import "..\ServerInfo.tlb"
using namespace SERVERINFOLib;

int _tmain(int argc, _TCHAR** argv)
{
   CoInitialize(NULL);

   try
   {
      HRESULT hr = S_OK;
      IDiskInfoPtr pDiskInfo;
      if (argc == 3 && argv[1][0] == _T('R')) 
      {
         USES_CONVERSION;
         COSERVERINFO csi = {0, T2W(argv[2]), NULL, 0};
         MULTI_QI qi = {&__uuidof(IDiskInfo), NULL, S_OK};
         hr = CoCreateInstanceEx(__uuidof(DiskInfo), NULL,
                                 CLSCTX_REMOTE_SERVER, &csi, 1, &qi);
         if (FAILED(hr))
            _com_issue_error(hr);
         IDiskInfo* pInt = static_cast<IDiskInfo*>(qi.pItf);
         pDiskInfo.Attach(pInt);
      }
      else if (argc == 2 && argv[1][0] == _T('L')) 
         hr = pDiskInfo.CreateInstance(
            __uuidof(DiskInfo), NULL, CLSCTX_LOCAL_SERVER);
      else
         hr = pDiskInfo.CreateInstance(
            __uuidof(DiskInfo), NULL, CLSCTX_INPROC_SERVER);

      if (FAILED(hr))
         _com_issue_error(hr);

      hyper hypDiskSize;
      pDiskInfo->GetFreeDiskSpace(L"C:\\", &hypDiskSize);
      _tprintf(_T("There are %I64d free bytes\n"), hypDiskSize);
   }
   catch (const _com_error& e)
   {
      _tprintf(_T("There is an error (%08x): %s\n"), 
         e.Error(), e.ErrorMessage());
   }

   CoUninitialize();
   return 0;
}


