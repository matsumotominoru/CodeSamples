// SetEvent.h : SETEVENT �A�v���P�[�V�����̃��C�� �w�b�_�[ �t�@�C���ł��B
//

#if !defined(AFX_SETEVENT_H__7C57C7DB_7780_11D2_AB98_0000B4725554__INCLUDED_)
#define AFX_SETEVENT_H__7C57C7DB_7780_11D2_AB98_0000B4725554__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// ���C�� �V���{��

/////////////////////////////////////////////////////////////////////////////
// CSetEventApp:
// ���̃N���X�̓���̒�`�Ɋւ��Ă� SetEvent.cpp �t�@�C�����Q�Ƃ��Ă��������B
//

class CSetEventApp : public CWinApp
{
public:
	CSetEventApp();

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CSetEventApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����

	//{{AFX_MSG(CSetEventApp)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ����o�֐���ǉ��܂��͍폜���܂��B
		//        ���̈ʒu�ɐ��������R�[�h��ҏW���Ȃ��ł��������B
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_SETEVENT_H__7C57C7DB_7780_11D2_AB98_0000B4725554__INCLUDED_)
