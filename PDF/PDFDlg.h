
// PDFDlg.h : 头文件
//

#pragma once
#include "PDFHandler.h"
#include "afxeditbrowsectrl.h"
#include "afxwin.h"


// CPDFDlg 对话框
class CPDFDlg : public CDialogEx
{
// 构造
public:
	CPDFDlg(CWnd* pParent = NULL);	// 标准构造函数
	~CPDFDlg();

// 对话框数据
	enum { IDD = IDD_PDF_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
