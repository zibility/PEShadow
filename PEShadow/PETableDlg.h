#pragma once
//#include "afxwin.h"
#include "Common.h"
//#include "afxcmn.h"


// CPETableDlg 对话框




class CPETableDlg : public CDialog
{
	DECLARE_DYNAMIC(CPETableDlg)

public:
	CPETableDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPETableDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_TABLE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CString m_GroupStatic;
	CString m_Table1;
	CString m_Table2;
	CString m_Table3;
	CString m_Table4;

	VOID	                    ShowPeTable(CHAR* FileData,PETYPE PeType);
	VOID	                    ShowDataDirTable(CHAR* szFileData,PETYPE PeType);
	VOID                        ShowSectionTable(CHAR* szFileData,PETYPE PeType);
	VOID                        ShowImportTable(CHAR*  szFileData,PETYPE PeType);
	VOID						ShowExportTable(CHAR*  szFileData,PETYPE PeType);
	VOID						ShowRelocTable(CHAR*   szFileData,PETYPE PeType);
	PIMAGE_SECTION_HEADER		GetSectionHeaderFromRva(ULONG RVA,PIMAGE_NT_HEADERS NtHeader);  //判断RVA是在那个节表当中;

	CListCtrl m_ListTable;
	CString m_EditTable1;
	CString m_EditTable2;
	CString m_EditTable3;
	CString m_EditTable4;
};

DWORD RVATwoOffset(PIMAGE_NT_HEADERS32 NTHeader, ULONG ulRVA)   ;
ULONG_PTR RVATwoOffset64(PIMAGE_NT_HEADERS64 NTHeader, ULONG_PTR ulRVA)   ;