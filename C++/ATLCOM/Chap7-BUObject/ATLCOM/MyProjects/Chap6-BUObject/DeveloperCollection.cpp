// DeveloperCollection.cpp : CDeveloperCollection のインプリメンテーション
#include "stdafx.h"
#include "BUObject.h"
#include "DeveloperCollection.h"

/////////////////////////////////////////////////////////////////////////////
// CDeveloperCollection


STDMETHODIMP CDeveloperCollection::Add(IEmployee *pEmployee)
{
	// TODO: この位置にインプリメント用のコードを追加してください
   CComBSTR bstrName;
   long ID;
   GetEmployee(pEmployee, bstrName, ID);

   if (bstrName.Length() == 0)
   {
      ATLTRACE(_T("Employee %ld must have ")
         _T("a name\n"), ID);
      return E_INVALIDARG;
   }

   ATLTRACE(_T("Adding Employee %ls (%ld)\n"), bstrName, ID);
   m_map[bstrName] = pEmployee;
   pEmployee->AddRef();

	return S_OK;
}

STDMETHODIMP CDeveloperCollection::get_Count(long *pVal)
{
	// TODO: この位置にインプリメント用のコードを追加してください
   *pVal = m_map.size();
	return S_OK;
}

STDMETHODIMP CDeveloperCollection::Item(VARIANT Index, LPVARIANT pItem)
{
	// TODO: この位置にインプリメント用のコードを追加してください
   VariantInit(pItem);

   // Check to see if a number has been passed
   if (Index.vt == VT_I4)
   {
      // 1 based index
      if (Index.lVal <= m_map.size() && Index.lVal > 0)
      {
         int i = 1;
         std::map<CComBSTR, IEmployee*, BSTRless>::iterator it;

         // Find the item by index
         for (it = m_map.begin(); it != m_map.end(); it++, i++)
         {
            if (i == Index.lVal)
            {
               // Found it! Copy the object into pItem
               pItem->vt = VT_DISPATCH;
               IEmployee* pEmp;

               // Get the item
               pEmp = (*it).second;

               // Put the IDispatch into pItem (also implicit AddRef())
               return pEmp->QueryInterface(IID_IDispatch,
                                           (void**) &(pItem->pdispVal));
            }
         }

         // Didn't find it; should never get here
         return E_INVALIDARG;
      }

      // Index out of range
      else
         return E_INVALIDARG;
   }

   // Check to see if a string has been passed
   else if (Index.vt == VT_BSTR)
   {
      // Indexed by name
      std::map<CComBSTR, IEmployee*, BSTRless>::iterator it;

      // Look for an item with this key
      it = m_map.find(Index.bstrVal);
      VariantClear(&Index);
      if (it == m_map.end())
      {
         // Can't find it
         return E_INVALIDARG;
      }
      pItem->vt = VT_DISPATCH;
      IEmployee* pEmp;
      pEmp = (*it).second;

      // Copy the item's IDispatch into pItem (also implicit AddRef())
      return pEmp->QueryInterface(IID_IDispatch,
                                  (void**) &(pItem->pdispVal));
   }

   // Unrecognised index type
   else
      return E_INVALIDARG;
	return S_OK;
}

STDMETHODIMP CDeveloperCollection::get__NewEnum(LPUNKNOWN *pVal)
{
	// TODO: この位置にインプリメント用のコードを追加してください
   long lCount = m_map.size();

   // Temporary array to hold the objects
   VARIANT* var = new VARIANT[lCount];
   std::map<CComBSTR, IEmployee*, BSTRless>::iterator it;
   int i = 0;

   // Fill the temporary array with the objects
   for (it = m_map.begin(); it != m_map.end(); it++, i++)
   {
      IEmployee* pEmp = (*it).second;
      VariantInit(&var[i]);
      var[i].vt = VT_DISPATCH;

      // VARIANT holds IDispatch pointers, also QI AddRef()s the objects
      pEmp->QueryInterface(IID_IDispatch, (void**)&(var[i].pdispVal));
   }

   // Do this typedef to make the following code readable!
   // We need a VARIANT enumerator
   typedef CComObject< CComEnum< IEnumVARIANT,
                                 &IID_IEnumVARIANT,
                                 VARIANT,
                                 _Copy<VARIANT> > > EnumVar;

   // Create a new instance of the object
   EnumVar* pVar = new EnumVar;

   // Initialize it with the objects, a copy will be made
   pVar->Init(&var[0], &var[i], NULL, AtlFlagCopy);

   // Now release the objects put in the temporary array
   lCount--;
   while(lCount >= 0)
   {
      VariantClear(&var[lCount]);
      lCount--;
   }
   delete [] var;

   // Return the IUnknown for the enumerator
   pVar->QueryInterface(IID_IUnknown, (void**)pVal);

   // We do not delete pVar, this is not a leak!
	return S_OK;
}

void CDeveloperCollection::FinalRelease()
{
	std::map<CComBSTR, IEmployee*, BSTRless>::iterator it;
   for (it = m_map.begin(); it != m_map.end(); it++)
   {
      IEmployee* pEmp = (*it).second;
      pEmp->Release();
   }
}

void CDeveloperCollection::GetEmployee( IEmployee* pEmployee,
                                        CComBSTR&  bstrName,
                                        long&      pEmployeeID )
{
#ifdef _DEBUG
   pEmployee->get_Name(&bstrName);
   pEmployee->get_EmployeeID(&pEmployeeID);
#endif
}

