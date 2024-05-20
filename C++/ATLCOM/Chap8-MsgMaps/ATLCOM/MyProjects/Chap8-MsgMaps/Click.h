// Click.h : Declaration of the CClick

#ifndef __CLICK_H_
#define __CLICK_H_

#include "resource.h"       // メイン シンボル
#include <atlctl.h>


/////////////////////////////////////////////////////////////////////////////
// CClick
class ATL_NO_VTABLE CClick : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public IDispatchImpl<IClick, &IID_IClick, &LIBID_MSGMAPSLib>,
	public CComControl<CClick>,
	public IPersistStreamInitImpl<CClick>,
	public IOleControlImpl<CClick>,
	public IOleObjectImpl<CClick>,
	public IOleInPlaceActiveObjectImpl<CClick>,
	public IViewObjectExImpl<CClick>,
	public IOleInPlaceObjectWindowlessImpl<CClick>,
	public IPersistStorageImpl<CClick>,
	public ISpecifyPropertyPagesImpl<CClick>,
	public IQuickActivateImpl<CClick>,
	public IDataObjectImpl<CClick>,
	public IProvideClassInfo2Impl<&CLSID_Click, NULL, &LIBID_MSGMAPSLib>,
	public CComCoClass<CClick, &CLSID_Click>
{
public:
	CContainedWindow m_ctlEdit;
   TCHAR m_str[80];	

	CClick() :	
		m_ctlEdit(_T("Edit"), this, 1)
	{
        m_str[0] = 0;
		m_bWindowOnly = TRUE;
	}

DECLARE_REGISTRY_RESOURCEID(IDR_CLICK)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CClick)
	COM_INTERFACE_ENTRY(IClick)
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
	COM_INTERFACE_ENTRY(ISpecifyPropertyPages)
	COM_INTERFACE_ENTRY(IQuickActivate)
	COM_INTERFACE_ENTRY(IPersistStorage)
	COM_INTERFACE_ENTRY(IDataObject)
	COM_INTERFACE_ENTRY(IProvideClassInfo)
	COM_INTERFACE_ENTRY(IProvideClassInfo2)
END_COM_MAP()

BEGIN_PROP_MAP(CClick)
	PROP_DATA_ENTRY("_cx", m_sizeExtent.cx, VT_UI4)
	PROP_DATA_ENTRY("_cy", m_sizeExtent.cy, VT_UI4)
	// Example entries
	// PROP_ENTRY("Property Description", dispid, clsid)
	// PROP_PAGE(CLSID_StockColorPage)

END_PROP_MAP()

BEGIN_MSG_MAP(CClick)
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
	MESSAGE_HANDLER(WM_SETFOCUS, OnSetFocus)
	CHAIN_MSG_MAP(CComControl<CClick>)
   MESSAGE_HANDLER(WM_LBUTTONDOWN, OnCtrlLButton)
ALT_MSG_MAP(1)
   MESSAGE_HANDLER(WM_LBUTTONDOWN, OnEditLButton)

	// スーパークラス化された Edit に対するメッセージ マップ エントリでここを置き換えます

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
		LRESULT lRes = CComControl<CClick>::OnSetFocus(uMsg, wParam, lParam, bHandled);
		if (m_bInPlaceActive)
		{
			DoVerbUIActivate(&m_rcPos,  NULL);
			if(!IsChild(::GetFocus()))
				m_ctlEdit.SetFocus();
		}
		return lRes;
	}

	LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		RECT rc;
		GetWindowRect(&rc);
		rc.right -= rc.left;
		rc.bottom -= rc.top;
		rc.top = rc.left = 0;
//		m_ctlEdit.Create(m_hWnd, rc);

      // Divide the height by 2
      rc.bottom /= 2;
      // Create the edit control in the top half of our
      // control and give it a border
      m_ctlEdit.Create(m_hWnd, rc, NULL,
         WS_CHILD | WS_VISIBLE | WS_BORDER);
	
		return 0;
	}

	STDMETHOD(SetObjectRects)(LPCRECT prcPos,LPCRECT prcClip)
	{
		IOleInPlaceObjectWindowlessImpl<CClick>::SetObjectRects(prcPos, prcClip);
		int cx, cy;
		cx = prcPos->right - prcPos->left;
		cy = prcPos->bottom - prcPos->top;
//		::SetWindowPos(m_ctlEdit.m_hWnd, NULL, 0,
//			0, cx, cy, SWP_NOZORDER | SWP_NOACTIVATE);
	      ::SetWindowPos(m_ctlEdit.m_hWnd, NULL, 0,
         0, cx, cy/2, SWP_NOZORDER | SWP_NOACTIVATE);

		return S_OK;
	}

	HRESULT CClick::OnDraw(ATL_DRAWINFO& di)
	{
		RECT& rc = *(RECT*)di.prcBounds;
		Rectangle(di.hdcDraw, rc.left, 
		rc.top + (rc.bottom - rc.top)/2,
		rc.right, rc.bottom);
		TextOut(di.hdcDraw, 0, 
		rc.top + (rc.bottom - rc.top)/2, 
		m_str, lstrlen(m_str));
		return S_OK;
	}
   LRESULT OnCtrlLButton(UINT uMsg, WPARAM wParam, LPARAM lParam,
                         BOOL& bHandled)
   {
      lstrcpy(m_str, _T("Clicked the control"));
      m_ctlEdit.SetWindowText(_T(""));
      FireViewChange();
      return 0;
   }

   LRESULT OnEditLButton(UINT uMsg, WPARAM wParam, LPARAM lParam,
                         BOOL& bHandled)
   {
      m_str[0] = 0;
      m_ctlEdit.SetWindowText(_T("Clicked the edit box"));
      FireViewChange();
      bHandled = FALSE;
      return 0;
   }

// IViewObjectEx
	DECLARE_VIEW_STATUS(VIEWSTATUS_SOLIDBKGND | VIEWSTATUS_OPAQUE)

// IClick
public:
};

#endif //__CLICK_H_
