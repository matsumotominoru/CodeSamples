// ComDialog.cpp : CComDialog のインプリメンテーション
#include "stdafx.h"
#include "ComDialog.h"

/////////////////////////////////////////////////////////////////////////////
// CComDialog

STDMETHODIMP CComDialog::get_Visible(VARIANT_BOOL* pbVisible)
{
	*pbVisible = IsVisible();
	return S_OK;
}

STDMETHODIMP CComDialog::put_Visible(VARIANT_BOOL bVisible)
{
	// Do nothing if the visible state doesn't change
	// This ensures that we always have matched AddRef()s and Release()s
	if (bVisible == IsVisible())
		return S_OK;

	// Show or hide the window
	ShowWindow( bVisible ? SW_SHOW : SW_HIDE );

	// Now AddRef() or Release() the object.
	// This is the reference count for the interactive user
	bVisible ? GetUnknown()->AddRef() : GetUnknown()->Release();

	// Don't use any methods or members in this class from this point on,
	// because we may have called Release() in the previous statement.
	// The final call to Release() results in the object deleting itself, and we
	// don't want to access any members of a deleted object!
	return S_OK;
}