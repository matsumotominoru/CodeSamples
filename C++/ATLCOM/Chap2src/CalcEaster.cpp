// CalcEaster.cpp : CCalcEaster のインプリメンテーション
#include "stdafx.h"
#include "Simple.h"
#include "CalcEaster.h"

/////////////////////////////////////////////////////////////////////////////
// CCalcEaster


STDMETHODIMP CCalcEaster::get_Year(short *pVal)
{
	// TODO: この位置にインプリメント用のコードを追加してください
	// 年の値を取得する
	*pVal = m_Year;
	return S_OK;
}

STDMETHODIMP CCalcEaster::put_Year(short newVal)
{
	// TODO: この位置にインプリメント用のコードを追加してください
	// 年の値を設定する
	m_Year = newVal;
	return S_OK;
}

STDMETHODIMP CCalcEaster::get_Month(short *pVal)
{
	// TODO: この位置にインプリメント用のコードを追加してください
	// 月の値を取得する
	*pVal = m_Month;
	return S_OK;
}

STDMETHODIMP CCalcEaster::get_Day(short *pVal)
{
	// TODO: この位置にインプリメント用のコードを追加してください
	// 日の値を取得する
	*pVal = m_Day;
	return S_OK;
}

STDMETHODIMP CCalcEaster::CalculateEaster()
{
	// TODO: この位置にインプリメント用のコードを追加してください
	// まず、年が設定されていること、およびそれが
	// 所定の範囲内にあることをチェックする。

   if (m_Year < 326 || m_Year > 4099)
      return E_FAIL;

   short first = m_Year / 100;   // 先頭の2桁
   short div19 = m_Year % 19;    // 19で割った場合の余り

   // PFM（復活祭の満月）の日付を求める
   short temp = (first - 15) / 2 + ((first > 26) ? -1 : 0) +
                ((first > 38) ? -1 : 0) + 202 - 11 * div19;

   if (first == 21 | first == 24 | first == 25 |
                     first == 33 | first == 36 | first == 37)
      temp += -1;

   temp %= 30;

   short ta = temp + ((temp == 29) ? -1 : 0) +
                     ((temp == 28 && div19 > 10) ? -1 : 0) + 21;

   // 最初の日曜日を求める
   short tb = (ta - 19) % 7;
   temp = (40 - first) % 4;
   short tc = temp - ((temp > 1) ? -1 : 0) - ((temp == 3) ? -1 : 0);

   temp = m_Year % 100;
   short td = (temp + temp / 4) % 7;
   short te = ((20 - tb - tc - td) % 7) + 1;

   m_Day = ta + te;

   // 月を求める
   if (m_Day > 61)
   {
      m_Day -= 61;
      m_Month = 5;
   }
   else if (m_Day > 31)
   {
      m_Day -= 31;
      m_Month = 4;
   }
   else
      m_Month = 3;
	return S_OK;
}
