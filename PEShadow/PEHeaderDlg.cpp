// PEHeaderDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "PEShadow.h"
#include "PEHeaderDlg.h"
#include "afxdialogex.h"


// CPEHeaderDlg 对话框

extern
	CHAR*  g_szFileData;

IMPLEMENT_DYNAMIC(CPEHeaderDlg, CDialog)

CPEHeaderDlg::CPEHeaderDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPEHeaderDlg::IDD, pParent)
	, m_EditNumberofSec(_T(""))
	, m_EditOpEntry(_T(""))
	, m_EditSizeOfOption(_T(""))
	, m_EditOpImageBase(_T(""))
	, m_EditOpBaseOfData(_T(""))
	, m_EditOpBaseOfCode(_T(""))
	, m_EditSectionAligment(_T(""))
	, m_EditFileAligment(_T(""))
	, m_EditOpNumOfDir(_T(""))
	, m_EditOptionMagic(_T(""))
	, m_EditFileSign(_T(""))
	, m_EditFileCharac(_T(""))
{
	m_FileData = g_szFileData;
}

CPEHeaderDlg::~CPEHeaderDlg()
{
}

void CPEHeaderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_PEHEADER_FILE_NUMBEROFSECTION, m_EditNumberofSec);
	DDX_Text(pDX, IDC_EDIT_PEHEADER_OPTION_ENTRY, m_EditOpEntry);
	DDX_Text(pDX, IDC_EDIT_PEHEADER_FILE_SIZEOFOPTIONHEAD, m_EditSizeOfOption);
	DDX_Text(pDX, IDC_EDIT_PEHEADER_OPTION_IMAGEBASE, m_EditOpImageBase);
	DDX_Text(pDX, IDC_EDIT_PEHEADER_OPTION_BASEOFDATA, m_EditOpBaseOfData);
	DDX_Text(pDX, IDC_EDIT_PEHEADER_OPTION_BASEOFCODE, m_EditOpBaseOfCode);
	DDX_Text(pDX, IDC_EDIT_PEHEADER_OPTION_SECTIONALIGMENT, m_EditSectionAligment);
	DDX_Text(pDX, IDC_EDIT_PEHEADER_OPTION_FILEALIGMENT, m_EditFileAligment);
	DDX_Text(pDX, IDC_EDIT_PEHEADER_OPTION_NUMBEROFDIR, m_EditOpNumOfDir);
	DDX_Text(pDX, IDC_EDIT_PEHEADER_OPTION_MAGIC, m_EditOptionMagic);
	DDX_Text(pDX, IDC_EDIT_PEHEASER_SIGN, m_EditFileSign);
	DDX_Text(pDX, IDC_EDIT_PEHEADER_FILE_CHAR, m_EditFileCharac);
}


BEGIN_MESSAGE_MAP(CPEHeaderDlg, CDialog)
END_MESSAGE_MAP()


// CPEHeaderDlg 消息处理程序

VOID CPEHeaderDlg::CheckPEHeader()
{
	UpdateData(TRUE);

	PIMAGE_DOS_HEADER			DosHead;  //ReadFile()返回的szFileData地址
	PIMAGE_NT_HEADERS		    NtHead = NULL;
	IMAGE_FILE_HEADER		    FileHead = {0};
	ULONG						FileKind = 0;
	PIMAGE_NT_HEADERS64			NtHeader64 = NULL;
	PIMAGE_NT_HEADERS32			NtHeader32 = NULL;
	IMAGE_OPTIONAL_HEADER32     OptionHead32;
	IMAGE_OPTIONAL_HEADER64     OptionHead64;

	m_FileData = g_szFileData;

	if (m_FileData==NULL)
	{
		return;
	}

	DosHead = (PIMAGE_DOS_HEADER)m_FileData;

	NtHead = (PIMAGE_NT_HEADERS)((ULONG)m_FileData+DosHead->e_lfanew);

	CHAR wzMagic[64] = {0};
	memcpy(wzMagic,(CHAR*)NtHead,4);

	m_EditFileSign = wzMagic;

	FileHead = NtHead->FileHeader;

	m_EditNumberofSec.Format(L"%d",FileHead.NumberOfSections);                //节数量
	m_EditSizeOfOption.Format(L"0x%x",FileHead.SizeOfOptionalHeader);		  //选项头大小

	switch(FileHead.Characteristics)
	{
	case 0x102:
		{
			m_EditFileCharac.Format(L"EXE文件");
			break;
		}
	case IMAGE_FILE_SYSTEM:
		{

		//	m_EditFileCharac.Format(L"系统文件");
		//	break;

		}

	case 0x210E:
		{
			m_EditFileCharac.Format(L"DLL文件");
			break;
		}

	default:
		break;

	}


	if (FileHead.Machine == IMAGE_FILE_MACHINE_IA64||FileHead.Machine == IMAGE_FILE_MACHINE_AMD64)
	{
		FileKind = 64;

	}
	else if (FileHead.Machine == IMAGE_FILE_MACHINE_I386)
	{
		FileKind = 32;
	}

	else
	{
		FileKind = -1;
	}

	switch(FileKind)
	{
	case 32:{

		NtHeader32 = (PIMAGE_NT_HEADERS32)NtHead;
		OptionHead32 = NtHeader32->OptionalHeader;

		if (OptionHead32.Magic==0x0107)
		{
			m_EditOptionMagic.Format(L"ROM映像");
		}
		else if (OptionHead32.Magic==0x010B)
		{
			m_EditOptionMagic.Format(L"可执行映像");
		}
		else
		{
			m_EditOptionMagic.Format(L"PE32+");
		}

		m_EditOpEntry.Format(L"0x%x",OptionHead32.AddressOfEntryPoint);
		m_EditOpBaseOfData.Format(L"0x%x",OptionHead32.BaseOfData);
		m_EditOpBaseOfCode.Format(L"0x%x",OptionHead32.BaseOfCode);
		m_EditSectionAligment.Format(L"0x%x",OptionHead32.SectionAlignment);
		m_EditFileAligment.Format(L"0x%x",OptionHead32.FileAlignment);
		m_EditOpNumOfDir.Format(L"%d",OptionHead32.NumberOfRvaAndSizes);
		m_EditOpImageBase.Format(L"0x%x",OptionHead32.ImageBase);

		break;
			}

	case 64:
		{
			NtHeader64 = (PIMAGE_NT_HEADERS64)NtHead;
			OptionHead64 = NtHeader64->OptionalHeader;

			if (OptionHead64.Magic==0x0107)
			{
				m_EditOptionMagic.Format(L"ROM映像");
			}
			else if (OptionHead64.Magic==0x010B)
			{
				m_EditOptionMagic.Format(L"可执行映像");
			}
			else
			{
				m_EditOptionMagic.Format(L"PE32+");
			}

			m_EditOpEntry.Format(L"0x%x",OptionHead64.AddressOfEntryPoint);
			m_EditOpBaseOfCode.Format(L"0x%x",OptionHead64.BaseOfCode);
			m_EditSectionAligment.Format(L"0x%x",OptionHead64.SectionAlignment);
			m_EditFileAligment.Format(L"0x%x",OptionHead64.FileAlignment);
			m_EditOpNumOfDir.Format(L"%d",OptionHead64.NumberOfRvaAndSizes);
			m_EditOpImageBase.Format(L"0x%p",OptionHead64.ImageBase);
			break;
		}

	default:
		break;

	}

	UpdateData(FALSE);

}


BOOL CPEHeaderDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化


	CheckPEHeader();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
