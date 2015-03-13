
// PDFDlg.h : ͷ�ļ�
//

#pragma once
#include "PDFHandler.h"
#include "afxeditbrowsectrl.h"
#include "afxwin.h"


// CPDFDlg �Ի���
class CPDFDlg : public CDialogEx
{
// ����
public:
	CPDFDlg(CWnd* pParent = NULL);	// ��׼���캯��
	~CPDFDlg();

// �Ի�������
	enum { IDD = IDD_PDF_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
	HANDLE m_hMain;
public:
	CString m_csPath;
	CString m_csOutPath;
	long m_lResult;
	CString m_csWaterMark;
	long m_lType;
	long m_lFlag;
	long m_lHasPag;
	long m_lUnicode;
	CButton m_btnstart;
public:
	afx_msg void OnBnClickedButtonTest();
	CMFCEditBrowseCtrl m_editpath;
	void Stop();
	virtual void OnCancel();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	void DeleteFile(const CString& csPath);
};
DWORD WINAPI _AfxMain(LPVOID lpParam);
