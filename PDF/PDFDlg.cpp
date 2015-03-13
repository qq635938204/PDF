
// PDFDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PDF.h"
#include "PDFDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

const UINT _MESSAGE_COMPLETE_(WM_USER + 0x1001);
const UINT _MESSAGE_UNCOMPLETE_(WM_USER + 0x1002);

HANDLE __HEVENT_EXIT__ = NULL;
// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CPDFDlg �Ի���



CPDFDlg::CPDFDlg(CWnd* pParent /*=NULL*/)
: CDialogEx(CPDFDlg::IDD, pParent), m_hMain(NULL), m_lResult(-1)
, m_csWaterMark(_T(""))
, m_lType(0)
, m_lFlag(0)
, m_lHasPag(0)
, m_lUnicode(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CPDFDlg::~CPDFDlg()
{
	if (__HEVENT_EXIT__)
	{
		CloseHandle(__HEVENT_EXIT__);
		__HEVENT_EXIT__ = NULL;
	}
}

void CPDFDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MFCEDITBROWSE_PATH, m_editpath);
	DDX_Text(pDX, IDC_EDIT_WATERMARK, m_csWaterMark);
	DDX_Text(pDX, IDC_EDIT_TYPE, m_lType);
	DDX_Text(pDX, IDC_EDIT_FLAG, m_lFlag);
	DDX_Text(pDX, IDC_EDIT_PAGE, m_lHasPag);
	DDX_Text(pDX, IDC_EDIT_UNICODE, m_lUnicode);
	DDX_Control(pDX, IDC_BUTTON_TEST, m_btnstart);
}

BEGIN_MESSAGE_MAP(CPDFDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_TEST, &CPDFDlg::OnBnClickedButtonTest)
END_MESSAGE_MAP()


// CPDFDlg ��Ϣ�������

BOOL CPDFDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	__HEVENT_EXIT__ = CreateEvent(NULL, TRUE, FALSE, NULL);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CPDFDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CPDFDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CPDFDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


DWORD WINAPI _AfxMain(LPVOID lpParam)
{
	BOOL bValue(FALSE);
	CPDFDlg*pDlg = (CPDFDlg*)lpParam;
	CFile file;
	TCHAR szLog[256] = { 0 };
	CString csText(pDlg->m_csPath), csTemp, csOutFile, csTempFile, csName, csPath;
	long lCount(0);
	lCount = GetPageCount(csText);
	csTemp.Format(_T("PageCount = %d"), lCount);
	auto pos = csText.ReverseFind(_T('\\'));
	if (pos>0)
	{
		csPath = csText.Left(pos + 1);
		csName = csText.Mid(pos + 1);
		csOutFile.Format(_T("%sOUT_%s"), csPath, csName);
		pDlg->m_csOutPath = csOutFile;
		csTempFile.Format(_T("%sTMP_%s"), csPath, csName);
		PST_WATERMARK parWaterMark = new ST_WATERMARK[1];
		swprintf_s(parWaterMark->cszMark, 512, pDlg->m_csWaterMark);
		parWaterMark->lType = 0;
		parWaterMark->lFlag = 3;
		parWaterMark->lHasPage = 0;
		parWaterMark->lUnicode = 0;
		parWaterMark->lSize = _tcslen(parWaterMark->cszMark)*2;
		BOOL bRet = ReplacePDFText(csText, csOutFile, csTempFile, parWaterMark, 1, 0, szLog);
		csTemp = szLog;
		if (bRet == TRUE&&csTemp.Find(_T("�ɹ�")) >= 0)
		{
				bValue = TRUE;
		}
	}
	if (bValue)
		pDlg->PostMessage(_MESSAGE_COMPLETE_);
	else
		pDlg->PostMessage(_MESSAGE_UNCOMPLETE_);
	return 0;
}


void CPDFDlg::OnBnClickedButtonTest()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	DWORD id(0);
	CString csTemp;
	m_editpath.GetWindowText(m_csPath);
	if (m_csPath.IsEmpty())
	{
		AfxMessageBox(_T("�������ļ�·����"));
		return;
	}
	csTemp = m_csPath;
	csTemp.MakeLower();
	if (csTemp.Find(_T(".pdf")) < 0)
		return;
	UpdateData();
	//m_csWaterMark = _T("barbarayy_tong@citickawahbank.com Barbara Tong * AM CITIC Bank International")
	if (m_csWaterMark.IsEmpty())
	{
		AfxMessageBox(_T("������ˮӡ���ݣ�"));
		return;
	}
	if (m_csWaterMark.GetLength()>512)
		m_csWaterMark = m_csWaterMark.Left(511);
	m_btnstart.SetWindowText(_T("������..."));
	m_hMain = CreateThread(NULL, 0, _AfxMain, reinterpret_cast<void*>(this), 0, &id);
}

void CPDFDlg::Stop()
{
	if (__HEVENT_EXIT__)
		SetEvent(__HEVENT_EXIT__);
	if (m_hMain)
	{
		if (WaitForSingleObject(m_hMain, INFINITE) != WAIT_OBJECT_0)
		{
			OutputDebugString(_T("------------------------------------------\r\n"));
			TerminateThread(m_hMain, 0);
		}
		CloseHandle(m_hMain);
		m_hMain = NULL;
	}
}


void CPDFDlg::OnCancel()
{
	// TODO:  �ڴ����ר�ô����/����û���
	Stop();
	CDialogEx::OnCancel();
}



BOOL CPDFDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO:  �ڴ����ר�ô����/����û���
	if (pMsg->message == _MESSAGE_COMPLETE_)
	{
		m_btnstart.SetWindowText(_T("GO!"));
		if (IDYES == MessageBox(_T("����ɹ����Ƿ���ļ���"), _T(""), MB_YESNO))
			::ShellExecute(0, NULL, m_csOutPath, NULL, NULL, SW_NORMAL);
		return TRUE;
	}
	if (pMsg->message == _MESSAGE_UNCOMPLETE_)
	{
		DeleteFile(m_csOutPath);
		m_btnstart.SetWindowText(_T("GO!"));
		AfxMessageBox(_T("����ʧ�ܣ�"));
		return TRUE;
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}

void CPDFDlg::DeleteFile(const CString& csPath)
{
	if (csPath.IsEmpty())
		return;
	CFile file;
	if (file.Open(csPath, CFile::readOnly))
	{
		file.Close();
		CFile::Remove(csPath);
	}
}
