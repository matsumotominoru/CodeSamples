// SetEventDlg.h : �w�b�_�[ �t�@�C��
//

#if !defined(AFX_SETEVENTDLG_H__7C57C7DD_7780_11D2_AB98_0000B4725554__INCLUDED_)
#define AFX_SETEVENTDLG_H__7C57C7DD_7780_11D2_AB98_0000B4725554__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSetEventDlg �_�C�A���O

class CSetEventDlg : public CDialog
{
// �\�z
public:
	CSetEventDlg(CWnd* pParent = NULL);	// �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CSetEventDlg)
	enum { IDD = IDD_SETEVENT_DIALOG };
		// ����: ���̈ʒu�� ClassWizard �ɂ���ăf�[�^ �����o���ǉ�����܂��B
	//}}AFX_DATA

	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CSetEventDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �̃T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
	HICON m_hIcon;

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CSetEventDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnChangeEventname();
	afx_msg void OnCreate();
	afx_msg void OnSelchangeEvents();
	afx_msg void OnGo();
	afx_msg void OnStop();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_SETEVENTDLG_H__7C57C7DD_7780_11D2_AB98_0000B4725554__INCLUDED_)
