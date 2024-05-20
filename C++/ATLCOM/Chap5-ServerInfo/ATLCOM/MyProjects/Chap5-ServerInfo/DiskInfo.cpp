// DiskInfo.cpp : CDiskInfo のインプリメンテーション
#include "stdafx.h"
#include "ServerInfo.h"
#include "DiskInfo.h"

/////////////////////////////////////////////////////////////////////////////
// CDiskInfo


STDMETHODIMP CDiskInfo::GetFreeDiskSpace(const wchar_t *wszDrive, hyper *hypFreeBytes)
{
	// TODO: この位置にインプリメント用のコードを追加してください

	USES_CONVERSION;

   DWORD dwSectorsPerCluster;
   DWORD dwBytesPerSector;
   DWORD dwNumberOfFreeClusters;
   DWORD dwTotalNumberOfClusters;

   // GetDiskFreeSpaceEx() is not available
   // before Win95 OSR2, so we'll use GetDiskFreeSpace()
   GetDiskFreeSpace(W2T(wszDrive), &dwSectorsPerCluster, &dwBytesPerSector, 
                    &dwNumberOfFreeClusters, &dwTotalNumberOfClusters);

   // The number of bytes per cluster should fit into a DWORD
   DWORD dwBytesPerCluster;
   dwBytesPerCluster = dwSectorsPerCluster * dwBytesPerSector;

   // But the number of bytes on the disk needs careful handling
   *hypFreeBytes =  UInt32x32To64(dwNumberOfFreeClusters, dwBytesPerCluster);

	return S_OK;
}
