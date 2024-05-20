// URLTreeView.h : Declaration of the CURLTreeView

#ifndef __URLTREEVIEW_H_
#define __URLTREEVIEW_H_

#include "resource.h"       // メイン シンボル
#include <vector>
#pragma warning(disable : 4530)


#include <atlctl.h>
#include <commctrl.h>


/////////////////////////////////////////////////////////////////////////////
// CURLTreeView
class ATL_NO_VTABLE CURLTreeView : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public IDispatchImpl<IURLTreeView, &IID_IURLTreeView, &LIBID_URLTREELib>,
	public CComControl<CURLTreeView>,
	public IPersistStreamInitImpl<CURLTreeView>,
	public IOleControlImpl<CURLTreeView>,
	public IOleObjectImpl<CURLTreeView>,
	public IOleInPlaceActiveObjectImpl<CURLTreeView>,
	public IViewObjectExImpl<CURLTreeView>,
	public IOleInPlaceObjectWindowlessImpl<CURLTreeView>,
	public IPersistStorageImpl<CURLTreeView>,
	public IObjectSafetyImpl<CURLTreeView, INTERFACESAFE_FOR_UNTRUSTED_DATA>,
   public IPersistPropertyBagImpl<CURLTreeView>,
	public ISpecifyPropertyPagesImpl<CURLTreeView>,
	public IQuickActivateImpl<CURLTreeView>,
	public IDataObjectImpl<CURLTreeView>,
	public IProvideClassInfo2Impl<&CLSID_URLTreeView, NULL, &LIBID_URLTREELib>,
	public CComCoClass<CURLTreeView, &CLSID_URLTreeView>
{
public:
	CContainedWindow m_ctlSysTreeView32;
	CContainedWindow m_ctlEdit;

CURLTreeView() :	
	m_ctlSysTreeView32(_T("SysTreeView32"), this, 1),
	m_ctlEdit(_T("EDIT"), this, 2)
{
   m_hImageList = NULL;
   m_iImage = -1;
   m_iSelect = -1;

	m_tmHeight = 0;
	m_bWindowOnly = TRUE;
   m_cbMaxSize = 256; // Default URL size
}
//	CURLViewTree();

   LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
   STDMETHOD(SetObjectRects)(LPCRECT prcPos, LPCRECT prcClip);
   LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
   LRESULT OnDeleteItem(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);
   LRESULT OnSelChanged(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);
   LRESULT OnLButtonDblClk(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
HRESULT OnDraw(ATL_DRAWINFO& di);

DECLARE_REGISTRY_RESOURCEID(IDR_URLTREEVIEW)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CURLTreeView)
	COM_INTERFACE_ENTRY(IURLTreeView)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IViewObjectEx)
	COM_INTERFACE_ENTRY(IViewObject2)
	COM_INTERFACE_ENTRY(IViewObject)
	COM_INTERFACE_ENTRY(IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY(IOleInPlaceObject)
	COM_INTERFACE_ENTRY2(IOleWindow, IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY(IOleInPlaceActiveObject)
	COM_INTERFACE_ENTRY(IOleControl)
	COM_INTERFACE_ENTRY(IOleObject)
	COM_INTERFACE_ENTRY(IPersistStreamInit)
	COM_INTERFACE_ENTRY2(IPersist, IPersistStreamInit)
	//COM_INTERFACE_ENTRY_IMPL(IObjectSafety)
	COM_INTERFACE_ENTRY(IObjectSafety)
   COM_INTERFACE_ENTRY_IMPL(IPersistPropertyBag)
	COM_INTERFACE_ENTRY(ISpecifyPropertyPages)
	COM_INTERFACE_ENTRY(IQuickActivate)
	COM_INTERFACE_ENTRY(IPersistStorage)
	COM_INTERFACE_ENTRY(IDataObject)
	COM_INTERFACE_ENTRY(IProvideClassInfo)
	COM_INTERFACE_ENTRY(IProvideClassInfo2)
END_COM_MAP()

BEGIN_PROP_MAP(CURLTreeView)
	PROP_DATA_ENTRY("_cx", m_sizeExtent.cx, VT_UI4)
	PROP_DATA_ENTRY("_cy", m_sizeExtent.cy, VT_UI4)
	PROP_PAGE(CLSID_URLPage)
	// Example entries
	// PROP_ENTRY("Property Description", dispid, clsid)
	// PROP_PAGE(CLSID_StockColorPage)
END_PROP_MAP()

BEGIN_MSG_MAP(CURLTreeView)
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
	MESSAGE_HANDLER(WM_SIZE, OnSize)
   NOTIFY_CODE_HANDLER(TVN_DELETEITEM, OnDeleteItem)
   NOTIFY_CODE_HANDLER(TVN_SELCHANGED, OnSelChanged)

	MESSAGE_HANDLER(WM_SETFOCUS, OnSetFocus)
	CHAIN_MSG_MAP(CComControl<CURLTreeView>)
ALT_MSG_MAP(1)
	// スーパークラス化された SysTreeView32 に対するメッセージ マップ エントリでここを置き換えます
   MESSAGE_HANDLER(WM_LBUTTONDBLCLK, OnLButtonDblClk)
ALT_MSG_MAP(2)
	// editボックスに対するメッセージマップ

END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	BOOL PreTranslateAccelerator(LPMSG pMsg, HRESULT& hRet)
	{
		if(pMsg->message == WM_KEYDOWN && 
			(pMsg->wParam == VK_LEFT || 
			pMsg->wParam == VK_RIGHT ||
			pMsg->wParam == VK_UP ||
			pMsg->wParam == VK_DOWN))
		{
			hRet = S_FALSE;
			return TRUE;
		}
		//TODO: この位置に固有のアクセラレータをハンドルするためのコードを追加してください
		return FALSE;
	}

	LRESULT OnSetFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LRESULT lRes = CComControl<CURLTreeView>::OnSetFocus(uMsg, wParam, lParam, bHandled);
		if (m_bInPlaceActive)
		{
			DoVerbUIActivate(&m_rcPos,  NULL);
			if(!IsChild(::GetFocus()))
				m_ctlSysTreeView32.SetFocus();
		}
		return lRes;
	}

// IViewObjectEx
	DECLARE_VIEW_STATUS(VIEWSTATUS_SOLIDBKGND | VIEWSTATUS_OPAQUE)

// IURLTreeView
public:
	STDMETHOD(get_URLs)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(put_URLs)(/*[in]*/ VARIANT newVal);
	// IPersistPropertyBag
   STDMETHOD(Load)(LPPROPERTYBAG pPropBag, LPERRORLOG pErrorLog);
   STDMETHOD(Save)(LPPROPERTYBAG pPropBag, BOOL fClearDirty,
                   BOOL fSaveAllProperties);
	//IPersistStreamInit
   STDMETHOD(Load)(LPSTREAM pStm);
   STDMETHOD(Save)(LPSTREAM pStm, BOOL fClearDirty);

	// IObjectSafety
   STDMETHOD(SetInterfaceSafetyOptions)(REFIID riid,
             DWORD dwSupportedOptions, DWORD dwEnabledOptions);

   void FinalRelease();
private:
   HTREEITEM TVAddItemCore(HTREEITEM hParent, LPWSTR strItem, LPWSTR strURL,
      int iImage = -1, int iSelect = -1);
   void TVAddItem(HTREEITEM hParent, LPWSTR strBranch, LPWSTR strURL,
      int iImage = -1, int iSelect = -1);
   void FillTree();
   HIMAGELIST m_hImageList;
   int m_iImage;
   int m_iSelect;

   int m_tmHeight;
   std::vector<CComBSTR> m_URLs;
   int m_cbMaxSize;
};

#endif //__URLTREEVIEW_H_
