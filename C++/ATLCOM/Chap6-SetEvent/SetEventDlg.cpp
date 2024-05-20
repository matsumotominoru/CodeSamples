// SetEventDlg.cpp : �C���v�������e�[�V���� �t�@�C��
//

#include "stdafx.h"
#include "SetEvent.h"
#include "SetEventDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetEventDlg �_�C�A���O

CSetEventDlg::CSetEventDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSetEventDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSetEventDlg)
		// ����: ���̈ʒu�� ClassWizard �ɂ���ă����o�̏��������ǉ�����܂��B
	//}}AFX_DATA_INIT
	// ����: LoadIcon �� Win32 �� DestroyIcon �̃T�u�V�[�P���X��v�����܂���B
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSetEventDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetEventDlg)
		// ����: ���̏ꏊ�ɂ� ClassWizard �ɂ���� DDX �� DDV �̌Ăяo�����ǉ�����܂��B
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSetEventDlg, CDialog)
	//{{AFX_MSG_MAP(CSetEventDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_EVENTNAME, OnChangeEventname)
	ON_BN_CLICKED(IDC_CREATE, OnCreate)
	ON_LBN_SELCHANGE(IDC_EVENTS, OnSelchangeEvents)
	ON_BN_CLICKED(IDC_GO, OnGo)
	ON_BN_CLICKED(IDC_STOP, OnStop)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSetEventDlg ���b�Z�[�W �n���h��

BOOL CSetEventDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���̃_�C�A���O�p�̃A�C�R����ݒ肵�܂��B�t���[�����[�N�̓A�v���P�[�V�����̃��C��
	// �E�B���h�E���_�C�A���O�łȂ����͎����I�ɐݒ肵�܂���B
	SetIcon(m_hIcon, TRUE);			// �傫���A�C�R����ݒ�
	SetIcon(m_hIcon, FALSE);		// �������A�C�R����ݒ�
	
	// TODO: ���ʂȏ��������s�����͂��̏ꏊ�ɒǉ����Ă��������B
	
	return TRUE;  // TRUE ��Ԃ��ƃR���g���[���ɐݒ肵���t�H�[�J�X�͎����܂���B
}

// �����_�C�A���O�{�b�N�X�ɍŏ����{�^����ǉ�����Ȃ�΁A�A�C�R����`�悷��
// �R�[�h���ȉ��ɋL�q����K�v������܂��BMFC �A�v���P�[�V������ document/view
// ���f�����g���Ă���̂ŁA���̏����̓t���[�����[�N�ɂ�莩���I�ɏ�������܂��B

void CSetEventDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �`��p�̃f�o�C�X �R���e�L�X�g

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// �N���C�A���g�̋�`�̈���̒���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �A�C�R����`�悵�܂��B
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// �V�X�e���́A���[�U�[���ŏ����E�B���h�E���h���b�O���Ă���ԁA
// �J�[�\����\�����邽�߂ɂ������Ăяo���܂��B
HCURSOR CSetEventDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CSetEventDlg::OnChangeEventname() 
{
	// TODO: ���ꂪ RICHEDIT �R���g���[���̏ꍇ�A�R���g���[���́A lParam �}�X�N
	// ���ł̘_���a�� ENM_CHANGE �t���O�t���� CRichEditCrtl().SetEventMask()
	// ���b�Z�[�W���R���g���[���֑��邽�߂� CDialog::OnInitDialog() �֐����I�[�o�[
	// ���C�h���Ȃ����肱�̒ʒm�𑗂�܂���B
	
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
   CButton* pButton = (CButton*)GetDlgItem(IDC_CREATE);
   ASSERT(pButton);
   CWnd* pEdit = GetDlgItem(IDC_EVENTNAME);
   ASSERT(pEdit);
   CString strEvent;
   pEdit->GetWindowText(strEvent);
   pButton->EnableWindow(!strEvent.IsEmpty());
	
}

void CSetEventDlg::OnCreate() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
   CListBox* pList = (CListBox*)GetDlgItem(IDC_EVENTS);
   ASSERT(pList);
   CWnd* pEdit = GetDlgItem(IDC_EVENTNAME);
   ASSERT(pEdit);

   CString strEvent;
   pEdit->GetWindowText(strEvent);

   if (LB_ERR == pList->FindString(0, strEvent))
   {
      // Does not exist so we can add it
      HANDLE hEvent = CreateEvent(NULL, true, false, strEvent);

      if (hEvent)
      {
         int pos = pList->AddString(strEvent);
         pList->SetItemData(pos, (DWORD)hEvent);
         pList->SetCurSel(pos);
         OnSelchangeEvents();
      }
   }
	
}

void CSetEventDlg::OnSelchangeEvents() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
   CListBox* pList = (CListBox*)GetDlgItem(IDC_EVENTS);
   ASSERT(pList);

   CStatic* pIcon = (CStatic*)GetDlgItem(IDC_STATUS);
   ASSERT(pIcon);

   HANDLE hEvent = (HANDLE)pList->GetItemData(pList->GetCurSel());
   HICON hIcon;

   // Get the status of the event
   if (WAIT_OBJECT_0 == WaitForSingleObject(hEvent,0))
   {
      // Event is set
      hIcon = AfxGetApp()->LoadIcon(IDI_GO);
      CButton* pButton = (CButton*)GetDlgItem(IDC_GO);
      ASSERT(pButton);
      pButton->SetCheck(1);
      pButton = (CButton*)GetDlgItem(IDC_STOP);
      ASSERT(pButton);
      pButton->SetCheck(0);
   }
   else
   {
      // Event is not set
      hIcon = AfxGetApp()->LoadIcon(IDI_STOP);
      CButton* pButton = (CButton*)GetDlgItem(IDC_STOP);
      ASSERT(pButton);
      pButton->SetCheck(1);
      pButton = (CButton*)GetDlgItem(IDC_GO);
      ASSERT(pButton);
      pButton->SetCheck(0);
   }

   pIcon->SetIcon(hIcon);
	
}

void CSetEventDlg::OnGo() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
   CListBox* pList = (CListBox*)GetDlgItem(IDC_EVENTS);
   ASSERT(pList);

   CStatic* pIcon = (CStatic*)GetDlgItem(IDC_STATUS);
   ASSERT(pIcon);

   HANDLE hEvent = (HANDLE)pList->GetItemData(pList->GetCurSel());
   SetEvent(hEvent);

   HICON hIcon = AfxGetApp()->LoadIcon(IDI_GO);
   pIcon->SetIcon(hIcon);

}

void CSetEventDlg::OnStop() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
   CListBox* pList = (CListBox*)GetDlgItem(IDC_EVENTS);
   ASSERT(pList);

   CStatic* pIcon = (CStatic*)GetDlgItem(IDC_STATUS);
   ASSERT(pIcon);

   HANDLE hEvent = (HANDLE)pList->GetItemData(pList->GetCurSel());
   ResetEvent(hEvent);

   HICON hIcon = AfxGetApp()->LoadIcon(IDI_STOP);
   pIcon->SetIcon(hIcon);
	
}

void CSetEventDlg::OnClose() 
{
	// TODO: ���̈ʒu�Ƀ��b�Z�[�W �n���h���p�̃R�[�h��ǉ����邩�܂��̓f�t�H���g�̏������Ăяo���Ă�������
   // Release all the event objects
   CListBox* pList = (CListBox*)GetDlgItem(IDC_EVENTS);
   ASSERT(pList);

   int count = pList->GetCount();
   count--;

   while (count>=0)
   {
      HANDLE hEvent = (HANDLE)pList->GetItemData(count--);
      CloseHandle(hEvent);
   }
   CDialog::OnClose();
	
	CDialog::OnClose();
}
