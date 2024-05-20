// CalcEaster.cpp : CCalcEaster �̃C���v�������e�[�V����
#include "stdafx.h"
#include "Simple.h"
#include "CalcEaster.h"

/////////////////////////////////////////////////////////////////////////////
// CCalcEaster


STDMETHODIMP CCalcEaster::get_Year(short *pVal)
{
	// TODO: ���̈ʒu�ɃC���v�������g�p�̃R�[�h��ǉ����Ă�������
	// �N�̒l���擾����
	*pVal = m_Year;
	return S_OK;
}

STDMETHODIMP CCalcEaster::put_Year(short newVal)
{
	// TODO: ���̈ʒu�ɃC���v�������g�p�̃R�[�h��ǉ����Ă�������
	// �N�̒l��ݒ肷��
	m_Year = newVal;
	return S_OK;
}

STDMETHODIMP CCalcEaster::get_Month(short *pVal)
{
	// TODO: ���̈ʒu�ɃC���v�������g�p�̃R�[�h��ǉ����Ă�������
	// ���̒l���擾����
	*pVal = m_Month;
	return S_OK;
}

STDMETHODIMP CCalcEaster::get_Day(short *pVal)
{
	// TODO: ���̈ʒu�ɃC���v�������g�p�̃R�[�h��ǉ����Ă�������
	// ���̒l���擾����
	*pVal = m_Day;
	return S_OK;
}

STDMETHODIMP CCalcEaster::CalculateEaster()
{
	// TODO: ���̈ʒu�ɃC���v�������g�p�̃R�[�h��ǉ����Ă�������
	// �܂��A�N���ݒ肳��Ă��邱�ƁA����т��ꂪ
	// ����͈͓̔��ɂ��邱�Ƃ��`�F�b�N����B

   if (m_Year < 326 || m_Year > 4099)
      return E_FAIL;

   short first = m_Year / 100;   // �擪��2��
   short div19 = m_Year % 19;    // 19�Ŋ������ꍇ�̗]��

   // PFM�i�����Ղ̖����j�̓��t�����߂�
   short temp = (first - 15) / 2 + ((first > 26) ? -1 : 0) +
                ((first > 38) ? -1 : 0) + 202 - 11 * div19;

   if (first == 21 | first == 24 | first == 25 |
                     first == 33 | first == 36 | first == 37)
      temp += -1;

   temp %= 30;

   short ta = temp + ((temp == 29) ? -1 : 0) +
                     ((temp == 28 && div19 > 10) ? -1 : 0) + 21;

   // �ŏ��̓��j�������߂�
   short tb = (ta - 19) % 7;
   temp = (40 - first) % 4;
   short tc = temp - ((temp > 1) ? -1 : 0) - ((temp == 3) ? -1 : 0);

   temp = m_Year % 100;
   short td = (temp + temp / 4) % 7;
   short te = ((20 - tb - tc - td) % 7) + 1;

   m_Day = ta + te;

   // �������߂�
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
