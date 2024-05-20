// DiskInfo.h : CDiskInfo �̐錾

#ifndef __DISKINFO_H_
#define __DISKINFO_H_

#include "resource.h"       // ���C�� �V���{��

/////////////////////////////////////////////////////////////////////////////
// CDiskInfo
class ATL_NO_VTABLE CDiskInfo : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CDiskInfo, &CLSID_DiskInfo>,
	public IDiskInfo
{
public:
	CDiskInfo()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_DISKINFO)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CDiskInfo)
	COM_INTERFACE_ENTRY(IDiskInfo)
END_COM_MAP()

// IDiskInfo
public:
	STDMETHOD(GetFreeDiskSpace)(/*[in,string]*/ const wchar_t* wszDrive,/*[out]*/ hyper* hypFreeBytes);
};

#endif //__DISKINFO_H_
