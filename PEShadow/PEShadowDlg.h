
// PEShadowDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "PeCheckFunc.h"
#include "PEHeaderDlg.h"
#include "PETableDlg.h"


// CPEShadowDlg 对话框
class CPEShadowDlg : public CDialogEx
{
// 构造
public:
	CPEShadowDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_PESHADOW_DIALOG };

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
public:
	CTabCtrl    m_TabMain;
	CString     m_EditFilePath;
	CString     m_EditFileType;
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnTcnSelchangeTabMain(NMHDR *pNMHDR, LRESULT *pResult);
public:
	TCHAR		     m_FilePath[1024];
	CHAR*	         m_szFileData;
	ULONG		     m_ulLow;
	PETYPE		     PeType;
	CRect            m_TabRect;
	CPEHeaderDlg     m_PeHeaderDlg;
	CPETableDlg      m_PeTableDlg;
	VOID             OnInitTabConctrl();
		
	
};
