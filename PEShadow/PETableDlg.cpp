// PETableDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "PEShadow.h"
#include "PETableDlg.h"
//#include "afxdialogex.h"


// CPETableDlg 对话框

extern
	ULONG		g_SelectTab;
extern
	ULONG       g_dx;




UINT g_Column_Count_DirTable  = 5;	
UINT g_Column_Size_DirTable   = 705;
COLUMNSTRUCT g_Column_DirTableList[] =
{
	{ L"Name",		   	 180},	//ldr
	{ L"RVA",			 125},	//传递
	{ L"Size",			 125},	//
	{ L"RAW",		     125},
	{ L"所属区块",	     150}
};


UINT g_Column_Size_SectionTable   = 780;
UINT g_Column_Count_SectionTable  = 5;	
COLUMNSTRUCT g_Column_SectionTableList[] = 
{
	{ L"Name",					180 },	//ldr
	{ L"RVA",					150 },	//传递
	{ L"内存区块大小(未对齐)",	150 },	//
	{ L"文件偏移(offset)",		150 },
	{ L"文件大小",				150 }
};


UINT g_Column_Size_ImportTable   = 630;
UINT g_Column_Count_ImportTable  = 4;	
COLUMNSTRUCT g_Column_ImportTableList[] =
{
	{ L"函数序号",			150 },	//ldr
	{ L"函数名",			180 },	//传递
	{ L"函数地址",			150 },	//
	{ L"导入模块",          150 }
};


UINT g_Column_Size_ExportTable   = 780;	
UINT g_Column_Count_ExportTable  = 5;	
COLUMNSTRUCT g_Column_ExportTableList[] =
{
	{ L"函数序号",			150 },	//ldr
	{ L"函数名",			180 },	//传递
	{ L"函数地址",			150 },	//
	{ L"RVA",			    150 },
	{ L"Offset",			150 }
};

UINT g_Column_Size_RelocTable   = 980;
UINT g_Column_Count_RelocTable  = 7;	
COLUMNSTRUCT g_Column_RelocTableList[] =
{
	{ L"重定位表RVA",			150 },	//ldr
	{ L"重定位表Offset",		100 },
	{ L"重定位结构大小",		180 },	//传递
	{ L"TypeOffset",			150 },
	{ L"重定位项RVA",			150 },
	{ L"重定位项Offset",		100 },
	{ L"需要重定位的数据",		150 }
};


WCHAR wzDirTable[15][64] = {L"导出表地址",L"导入名称表",L"资源表",L"异常表",L"证书",L"重定向表",L"调试",L"版权",L"全局指针",L"LTS",L"加载配置",L"绑定导入表",L"导入地址表(IAT)",L"延迟加载导入表",L".NET 运行时"};


IMPLEMENT_DYNAMIC(CPETableDlg, CDialog)

CPETableDlg::CPETableDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPETableDlg::IDD, pParent)
	, m_GroupStatic(_T(""))
	, m_Table1(_T(""))
	, m_Table2(_T(""))
	, m_Table4(_T(""))
	, m_Table3(_T(""))
	, m_EditTable1(_T(""))
	, m_EditTable2(_T(""))
	, m_EditTable3(_T(""))
	, m_EditTable4(_T(""))
{

}

CPETableDlg::~CPETableDlg()
{
}

void CPETableDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_STATIC_TABLE, m_GroupStatic);
	DDX_Text(pDX, IDC_STATIC_TABLE1, m_Table1);
	DDX_Text(pDX, IDC_STATIC_TABLE2, m_Table2);
	DDX_Text(pDX, IDC_STATIC_TABLE4, m_Table4);
	DDX_Text(pDX, IDC_STATIC_TABLE3, m_Table3);
	DDX_Control(pDX, IDC_LIST_TABLE, m_ListTable);
	DDX_Text(pDX, IDC_EDIT_TABLE1, m_EditTable1);
	DDX_Text(pDX, IDC_EDIT_TABLE2, m_EditTable2);
	DDX_Text(pDX, IDC_EDIT_TABLE3, m_EditTable3);
	DDX_Text(pDX, IDC_EDIT_TABLE4, m_EditTable4);
}


BEGIN_MESSAGE_MAP(CPETableDlg, CDialog)
END_MESSAGE_MAP()


// CPETableDlg 消息处理程序


BOOL CPETableDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化



	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


VOID
	CPETableDlg::ShowPeTable(CHAR* FileData,PETYPE PeType)
{
	UpdateData(TRUE);

	switch(g_SelectTab)
	{
	case 1:
		{
			m_GroupStatic.Format(L"目录表详细信息");
			m_Table1.Format(L"");
			m_Table2.Format(L"");
			m_Table3.Format(L"");
			m_Table4.Format(L"");


			m_EditTable1.Format(L"");
			m_EditTable2.Format(L"");
			m_EditTable3.Format(L"");
			m_EditTable4.Format(L"");

			ShowDataDirTable(FileData,PeType);
			break;
		}

	case 2:
		{
			m_GroupStatic.Format(L"区块表详细信息");
			m_Table1.Format(L"");
			m_Table2.Format(L"");
			m_Table3.Format(L"");
			m_Table4.Format(L"");

			m_EditTable1.Format(L"");
			m_EditTable2.Format(L"");
			m_EditTable3.Format(L"");
			m_EditTable4.Format(L"");

			ShowSectionTable(FileData,PeType);
			break;
		}

	case 3:
		{
			m_GroupStatic.Format(L"导入表详细信息");

			m_Table1.Format(L"输入表RVA");
			m_Table2.Format(L"");
			m_Table3.Format(L"");
			m_Table4.Format(L"");

			m_EditTable1.Format(L"");
			m_EditTable2.Format(L"");
			m_EditTable3.Format(L"");
			m_EditTable4.Format(L"");

			ShowImportTable(FileData,PeType);
			break;
		}

	case 4:
		{
			m_GroupStatic.Format(L"导出表详细信息");

			m_Table1.Format(L"模块真实名称");
			m_Table2.Format(L"函数地址数组RVA");
			m_Table3.Format(L"函数名字指针RVA");
			m_Table4.Format(L"导出序号数组RVA");

			m_EditTable1.Format(L"");
			m_EditTable2.Format(L"");
			m_EditTable3.Format(L"");
			m_EditTable4.Format(L"");

			ShowExportTable(FileData,PeType);
			break;
		}

	case 5:
		{
			m_Table1.Format(L"");
			m_Table2.Format(L"");
			m_Table3.Format(L"");
			m_Table4.Format(L"");

			m_EditTable1.Format(L"");
			m_EditTable2.Format(L"");
			m_EditTable3.Format(L"");
			m_EditTable4.Format(L"");
			ShowRelocTable(FileData,PeType);

			break;
		}

	default:
		break;
	}

	UpdateData(FALSE);
}


VOID CPETableDlg::ShowDataDirTable(CHAR* szFileData,PETYPE PeType)
{
	PIMAGE_NT_HEADERS32						NtHead    = NULL;
	PIMAGE_NT_HEADERS64					NtHeader64    = NULL;
	PIMAGE_NT_HEADERS32					NtHeader32    = NULL;
	IMAGE_OPTIONAL_HEADER32		    	OptionHead32;
	IMAGE_OPTIONAL_HEADER64			    OptionHead64;
	PIMAGE_SECTION_HEADER				SectionHeader = NULL;

	ULONG							     DataDirTable = 0;
	ULONG									 DataSize = 0;
	ULONG_PTR								  DataRaw = 0;

	CString										   strRVA;
	CString										  strSize;
	CString									   strSection;
	CString										   strRaw;

	while(m_ListTable.DeleteColumn(0));
	m_ListTable.DeleteAllItems();

	m_ListTable.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_HEADERDRAGDROP);

	UINT	i = 0;
	for (i = 0;i<g_Column_Count_DirTable;i++)
	{
		ULONG ulLength = 0;

		ulLength = ((float)g_Column_DirTableList[i].nWidth/(float)g_Column_Size_DirTable)*(float)g_dx;

		m_ListTable.InsertColumn(i, g_Column_DirTableList[i].szTitle,LVCFMT_LEFT,ulLength);
	}

	if (szFileData==NULL)
	{
		return;
	}

	PIMAGE_DOS_HEADER DosHead = (PIMAGE_DOS_HEADER)szFileData;  //ReadFile()返回的szFileData地址

	switch(PeType)
	{
	case Bit32:
		{
			NtHeader32 = (PIMAGE_NT_HEADERS32)((ULONG)szFileData+DosHead->e_lfanew);
			OptionHead32 = NtHeader32->OptionalHeader;

			for (int i = 0;i<OptionHead32.NumberOfRvaAndSizes;i++)
			{
				DataDirTable = OptionHead32.DataDirectory[i].VirtualAddress;
				DataSize = OptionHead32.DataDirectory[i].Size;

				//得到数据块在文件中的偏移
				DataRaw = RVATwoOffset(NtHeader32,DataDirTable);

				//计算数据块属于哪个节中
				SectionHeader = GetSectionHeaderFromRva(DataDirTable,(PIMAGE_NT_HEADERS)NtHeader32);

				strRVA.Format(L"0x%X",DataDirTable);
				strSize.Format(L"0x%X",DataSize);
				strSection = SectionHeader->Name;
				strRaw.Format(L"0x%X",DataRaw);

				int n = m_ListTable.GetItemCount();
				int j = m_ListTable.InsertItem(n, wzDirTable[i]);
				m_ListTable.SetItemText(j, 1, strRVA);
				m_ListTable.SetItemText(j, 2, strSize);
				m_ListTable.SetItemText(j,3,strRaw);         //数据块在文件中偏移
				m_ListTable.SetItemText(j,4,strSection);

			}


			break;
		}

	case Bit64:
		{
			NtHeader64 = (PIMAGE_NT_HEADERS64)((ULONG)szFileData+DosHead->e_lfanew);

			OptionHead64 = NtHeader64->OptionalHeader;

			for (int i = 0;i<OptionHead64.NumberOfRvaAndSizes;i++)
			{
				DataDirTable = OptionHead64.DataDirectory[i].VirtualAddress;
				DataSize = OptionHead64.DataDirectory[i].Size;

				DataRaw = RVATwoOffset64(NtHeader64,DataDirTable);

				SectionHeader = GetSectionHeaderFromRva(DataDirTable,(PIMAGE_NT_HEADERS)NtHeader64);

				strRVA.Format(L"0x%X",DataDirTable);	//数据目录地址
				strSize.Format(L"0x%X",DataSize);		//数据目录大小
				strSection = SectionHeader->Name;		//所属节名字
				strRaw.Format(L"0x%X",DataRaw);          //数据目录文件偏移

				int n = m_ListTable.GetItemCount();
				int j = m_ListTable.InsertItem(n, wzDirTable[i]);
				m_ListTable.SetItemText(j, 1, strRVA);
				m_ListTable.SetItemText(j, 2, strSize);
				m_ListTable.SetItemText(j,3,strRaw);
				m_ListTable.SetItemText(j,4,strSection);

			}

			break;
		}
	default:
		break;

	}
}

PIMAGE_SECTION_HEADER
	CPETableDlg::GetSectionHeaderFromRva(ULONG RVA,PIMAGE_NT_HEADERS NtHeader)  //判断RVA是在那个节表当中
{
	ULONG   i = 0;


	//Nt头得到节表
	PIMAGE_SECTION_HEADER  SectionHeader = IMAGE_FIRST_SECTION(NtHeader);

	//Nt头中的File头中有区块表的个数  区块表是若干SECTION_HEADER个数据结构,个数是在文件头的NumberofSection中
	for (i=0;i<NtHeader->FileHeader.NumberOfSections;i++,SectionHeader++)
	{

		if ((RVA>=SectionHeader->VirtualAddress)&&
			(RVA<(SectionHeader->VirtualAddress + SectionHeader->Misc.VirtualSize)))      //Misc.VirtualSize   节的大小
		{
			return SectionHeader;
		}
	}

	return NULL;	
}


VOID  CPETableDlg::ShowSectionTable(CHAR* szFileData,PETYPE PeType)
{
	PIMAGE_NT_HEADERS						NtHead = NULL;
	PIMAGE_NT_HEADERS64					NtHeader64 = NULL;
	PIMAGE_NT_HEADERS32					NtHeader32 = NULL;

	IMAGE_FILE_HEADER				   	FileHeader;
	ULONG								  DataSize = 0;
	PIMAGE_SECTION_HEADER				SectionHeader;

	CString							      SectionName;
	CString									   strRVA;
	CString									 strRSize;
	CString									strOffset;
	CString									 strVsize;

	while(m_ListTable.DeleteColumn(0));       //清除    列表头    
	m_ListTable.DeleteAllItems();			//清空列表


	m_ListTable.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_HEADERDRAGDROP);

	UINT	i = 0;
	for (i = 0;i<g_Column_Count_SectionTable;i++)
	{
		ULONG ulLength = 0;

		ulLength = ((float)g_Column_SectionTableList[i].nWidth/(float)g_Column_Size_SectionTable)*(float)g_dx;

		m_ListTable.InsertColumn(i, g_Column_SectionTableList[i].szTitle,LVCFMT_LEFT,ulLength);
	}

	if (szFileData==NULL)
	{
		return;
	}

	PIMAGE_DOS_HEADER DosHead = (PIMAGE_DOS_HEADER)szFileData;

	//获得节表  
	if (PeType==Bit32)
	{
		NtHeader32 = (PIMAGE_NT_HEADERS32)((ULONG)szFileData+DosHead->e_lfanew);
		FileHeader = NtHeader32->FileHeader;
		SectionHeader =	(PIMAGE_SECTION_HEADER)((ULONG_PTR)NtHeader32 + sizeof(IMAGE_NT_HEADERS32));  
	}
	else 
	{
		NtHeader64 = (PIMAGE_NT_HEADERS64)((ULONG)szFileData+DosHead->e_lfanew);
		FileHeader =  NtHeader64->FileHeader;
		SectionHeader = (PIMAGE_SECTION_HEADER)((ULONG_PTR)NtHeader64 + sizeof(IMAGE_NT_HEADERS64));  
	}


	for (int i = 0;i<FileHeader.NumberOfSections;i++,SectionHeader++)    //节头的循环
	{
		SectionName = SectionHeader->Name;
		strRVA.Format(L"0x%x",SectionHeader->VirtualAddress);           //节RVA
		strRSize.Format(L"0x%x",SectionHeader->Misc.VirtualSize);		//节真实大小

		strOffset.Format(L"0x%x",SectionHeader->PointerToRawData);		//节的文件偏移
		strVsize.Format(L"0x%x",SectionHeader->SizeOfRawData);			//节的对齐大小    

		int n = m_ListTable.GetItemCount();
		int j = m_ListTable.InsertItem(n, SectionName);
		m_ListTable.SetItemText(j, 1, strRVA);
		m_ListTable.SetItemText(j, 2, strRSize);
		m_ListTable.SetItemText(j,3,strOffset);
		m_ListTable.SetItemText(j,4,strVsize);

	}


	UpdateData(FALSE);

}

VOID	CPETableDlg::ShowImportTable(CHAR*	szFileData,PETYPE PeType)
{
	PIMAGE_NT_HEADERS								NtHead                  = NULL;
	PIMAGE_THUNK_DATA32								ImportOriFirstThunk32   = NULL;
	PIMAGE_THUNK_DATA64                             ImportOriFirstThunk64   = NULL;
	PIMAGE_IMPORT_BY_NAME						    OrdinalName             = NULL;
	PIMAGE_NT_HEADERS64					            NtHeader64              = NULL;
	PIMAGE_NT_HEADERS32								NtHeader32              = NULL;

	IMAGE_OPTIONAL_HEADER32							OptionHead32;
	IMAGE_OPTIONAL_HEADER64							OptionHead64;
	IMAGE_DATA_DIRECTORY							ImportDirectory         = {0};
	PIMAGE_IMPORT_DESCRIPTOR						ImportTable             = NULL;
	ULONG_PTR										ImportSize			    = 0;
	ULONG_PTR										ImportDiff			    = 0;
	ULONG											ulIndex                 = 0;

	ULONG_PTR										ulFuncRVA               = 0;

	CString											strFuncName,strDllName;
	CString											strIndex                = 0;


	while(m_ListTable.DeleteColumn(0));
	m_ListTable.DeleteAllItems();

	m_ListTable.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_HEADERDRAGDROP);


	UINT	i = 0;
	for (i = 0;i<g_Column_Count_ImportTable;i++)
	{
		ULONG ulLength = 0;

		ulLength = ((float)g_Column_ImportTableList[i].nWidth/(float)g_Column_Size_ImportTable)*(float)g_dx;

		m_ListTable.InsertColumn(i, g_Column_ImportTableList[i].szTitle,LVCFMT_LEFT,ulLength);
	}

	if (szFileData==NULL)
	{
		return;
	}

	PIMAGE_DOS_HEADER DosHead = (PIMAGE_DOS_HEADER)szFileData;

	NtHead = (PIMAGE_NT_HEADERS)((ULONG)szFileData+DosHead->e_lfanew);

	switch(PeType)
	{
	case Bit32:
		{
			NtHeader32 = (PIMAGE_NT_HEADERS32)NtHead;
			OptionHead32 = NtHeader32->OptionalHeader;

			ImportDirectory = OptionHead32.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT];    //里面存放的导入表RVA

			m_EditTable1.Format(L"0x%p",ImportDirectory);

			if (ImportDirectory.Size==0)
			{
				return;
			}

			ImportTable = (PIMAGE_IMPORT_DESCRIPTOR)((ULONG_PTR)szFileData+ RVATwoOffset(NtHeader32,ImportDirectory.VirtualAddress));     //RVA   转换成    通过节表的文件偏移作为跳板  获得RVA RAW（文件偏移）

			while (ImportTable->Name)
			{
				char* DllName = (char*)((ULONG_PTR)szFileData+ RVATwoOffset(NtHeader32,ImportTable->Name));       //每个DLL     分配一个导入表     DLLName   RAV
				strDllName = DllName;

				ImportOriFirstThunk32 = (PIMAGE_THUNK_DATA32)((ULONG_PTR)szFileData + RVATwoOffset(NtHeader32,ImportTable->OriginalFirstThunk));

				while(ImportOriFirstThunk32->u1.Function)
				{

					int n = m_ListTable.GetItemCount();
					strIndex.Format(L"%d",ulIndex);
					int j = m_ListTable.InsertItem(n, strIndex);

					//判断是以序数导入还是以Name导入		
					//最高位为1说明以序数导入 序号值为低31位
					int Temp = ImportOriFirstThunk32->u1.Ordinal&0x80000000;

					if (Temp)
					{
						Temp =  ImportOriFirstThunk32->u1.Ordinal&0x7fffffff;
						strIndex.Format(L"%d",Temp);
						m_ListTable.SetItemText(j,1,strIndex);
					}
					else
					{
						OrdinalName = (PIMAGE_IMPORT_BY_NAME)((ULONG_PTR)szFileData + RVATwoOffset(NtHeader32,ImportOriFirstThunk32->u1.AddressOfData));
						char* FuncName = (char*)OrdinalName->Name;
						strFuncName = FuncName;						

						ulFuncRVA = (ULONG_PTR)((ULONG_PTR)szFileData + RVATwoOffset(NtHeader32,ImportOriFirstThunk32->u1.ForwarderString));

						m_ListTable.SetItemText(j,1,strFuncName);			

					}

					m_ListTable.SetItemText(j,3,strDllName);

					ulIndex++;
					ImportOriFirstThunk32++;

				}

				ImportTable++;
			}


			break;
		}
	case Bit64:
		{
			NtHeader64 = (PIMAGE_NT_HEADERS64)NtHead;
			OptionHead64 = NtHeader64->OptionalHeader;

			ImportDirectory = OptionHead64.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT];
			if (ImportDirectory.Size==0)
			{
				return;
			}

			ImportTable = (PIMAGE_IMPORT_DESCRIPTOR)((ULONG_PTR)szFileData+ RVATwoOffset64(NtHeader64,ImportDirectory.VirtualAddress));


			while (ImportTable->Name)
			{
				char* DllName = (char*)((ULONG_PTR)szFileData+ RVATwoOffset64(NtHeader64,ImportTable->Name));
				strDllName = DllName;

				ImportOriFirstThunk64 = (PIMAGE_THUNK_DATA64)((ULONG_PTR)szFileData + RVATwoOffset64(NtHeader64,ImportTable->OriginalFirstThunk));

				while(ImportOriFirstThunk64->u1.Function)
				{

					int n = m_ListTable.GetItemCount();
					strIndex.Format(L"%d",ulIndex);        //一开始为0   函数索引
					int j = m_ListTable.InsertItem(n, strIndex);

					INT64 Temp = ImportOriFirstThunk64->u1.Ordinal&0x8000000000000000;

					if (Temp)
					{
						Temp =  ImportOriFirstThunk64->u1.Ordinal&0x7fffffffffffffff;
						strIndex.Format(L"%d",Temp);
						m_ListTable.SetItemText(j,1,strIndex);
					}
					else
					{
						OrdinalName = (PIMAGE_IMPORT_BY_NAME)((ULONG_PTR)szFileData + RVATwoOffset64(NtHeader64,ImportOriFirstThunk64->u1.AddressOfData));
						char* FuncName = (char*)OrdinalName->Name;
						strFuncName = FuncName;						
						m_ListTable.SetItemText(j,1,strFuncName);						
					}

					m_ListTable.SetItemText(j,3,strDllName);

					ulIndex++;
					ImportOriFirstThunk64++;

				}

				ImportTable++;
			}


			break;
		}

	default:
		break;

	}
}


VOID	CPETableDlg::ShowExportTable(CHAR*	szFileData,PETYPE PeType)
{
	PIMAGE_NT_HEADERS									NtHead = NULL;
	PIMAGE_NT_HEADERS64								NtHeader64 = NULL;
	PIMAGE_NT_HEADERS32								NtHeader32 = NULL;
	IMAGE_OPTIONAL_HEADER32			              OptionHead32;
	IMAGE_OPTIONAL_HEADER64						  OptionHead64;
	IMAGE_DATA_DIRECTORY				       ExportDirectory = {0};
	PIMAGE_EXPORT_DIRECTORY			               ExportTable = NULL;



	ULONG_PTR									NameOfArrayRVA = NULL;
	ULONG*										   NameOfArray = NULL;
	ULONG_PTR								OrdinalsOfArrayRVA = NULL;
	WORD*								     OrdinalsOfArray   = NULL;
	ULONG_PTR							 FuncAddressOfArrayRVA = NULL;
	ULONG*								  FuncAddressOfArray   = NULL;
	ULONG_PTR										FuncAdress = NULL;

	CString		   strIndex, strFuncName,strFuncAddr,strRVA,strOffset;


	while(m_ListTable.DeleteColumn(0));
	m_ListTable.DeleteAllItems();
	m_ListTable.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_HEADERDRAGDROP);


	UINT	i = 0;
	for (i = 0;i<g_Column_Count_ExportTable;i++)
	{
		ULONG ulLength = 0;

		ulLength = ((float)g_Column_ExportTableList[i].nWidth/(float)g_Column_Size_ExportTable)*(float)g_dx;

		m_ListTable.InsertColumn(i, g_Column_ExportTableList[i].szTitle,LVCFMT_LEFT,ulLength);
	}

	if (szFileData==NULL)
	{
		return;
	}


	PIMAGE_DOS_HEADER DosHead = (PIMAGE_DOS_HEADER)szFileData;
	NtHead = (PIMAGE_NT_HEADERS)((ULONG)szFileData+DosHead->e_lfanew);

	switch(PeType)
	{
	case Bit32:
		{
			NtHeader32 = (PIMAGE_NT_HEADERS32)NtHead;
			OptionHead32 = NtHeader32->OptionalHeader;

			ExportDirectory = OptionHead32.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT]; 
			if (ExportDirectory.Size==0)
			{
				return;
			}

			DWORD	Temp = RVATwoOffset(NtHeader32,ExportDirectory.VirtualAddress);   //为了荡出没有导出表的模块

			if (Temp==0)
			{
				return;
			}


			ExportTable = (PIMAGE_EXPORT_DIRECTORY)((ULONG_PTR)szFileData+ Temp);

			CHAR*	DllName = (CHAR*)((ULONG_PTR)szFileData + RVATwoOffset(NtHeader32,ExportTable->Name));

			m_EditTable1.Format(L"%S",DllName);

			//
			NameOfArrayRVA = (ULONG_PTR)(ExportTable->AddressOfNames);
			m_EditTable3.Format(L"0x%p",NameOfArrayRVA);
			NameOfArrayRVA = RVATwoOffset(NtHeader32,NameOfArrayRVA);
			NameOfArray = (ULONG*)((ULONG_PTR)szFileData + NameOfArrayRVA);
			CHAR* wzFuncName = NULL;

			//
			OrdinalsOfArrayRVA = (ULONG_PTR)ExportTable->AddressOfNameOrdinals;
			m_EditTable4.Format(L"0x%p",OrdinalsOfArrayRVA);
			OrdinalsOfArrayRVA = RVATwoOffset(NtHeader32,OrdinalsOfArrayRVA);
			OrdinalsOfArray =  (WORD*)((ULONG_PTR)szFileData + OrdinalsOfArrayRVA);

			//
			FuncAddressOfArrayRVA = (ULONG_PTR)ExportTable->AddressOfFunctions;
			m_EditTable2.Format(L"0x%p",FuncAddressOfArrayRVA);
			FuncAddressOfArrayRVA = RVATwoOffset(NtHeader32,FuncAddressOfArrayRVA);
			FuncAddressOfArray = (ULONG*)((ULONG_PTR)szFileData + FuncAddressOfArrayRVA);


			for (int i=0;i<ExportTable->NumberOfNames;i++)
			{
				wzFuncName = (CHAR*)((ULONG_PTR)szFileData+RVATwoOffset(NtHeader32,NameOfArray[i]));
				FuncAdress  =(ULONG_PTR)szFileData + RVATwoOffset(NtHeader32,FuncAddressOfArray[OrdinalsOfArray[i]]);

				strIndex.Format(L"%d",OrdinalsOfArray[i]);
				strFuncName.Format(L"%S",wzFuncName);
				strFuncAddr.Format(L"0x%x",FuncAdress);
				strRVA.Format(L"0x%x",FuncAddressOfArray[OrdinalsOfArray[i]]);
				strOffset.Format(L"0x%x",RVATwoOffset(NtHeader32,FuncAddressOfArray[OrdinalsOfArray[i]]));


				int n = m_ListTable.GetItemCount();
				int j = m_ListTable.InsertItem(n, strIndex);
				m_ListTable.SetItemText(j, 1, strFuncName);
				m_ListTable.SetItemText(j, 2, strFuncAddr);
				m_ListTable.SetItemText(j,3,strRVA);
				m_ListTable.SetItemText(j,4,strOffset);

			}


			break;
		}

	case Bit64:
		{
			NtHeader64 = (PIMAGE_NT_HEADERS64)NtHead;
			OptionHead64 = NtHeader64->OptionalHeader;

			ExportDirectory = OptionHead64.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT]; 
			if (ExportDirectory.Size==0)
			{
				return;
			}

			DWORD		Temp = RVATwoOffset64(NtHeader64,ExportDirectory.VirtualAddress);

			if (Temp==0)
			{
				return;
			}

			ExportTable = (PIMAGE_EXPORT_DIRECTORY)((ULONG_PTR)szFileData+ Temp);

			CHAR*	DllName = (CHAR*)((ULONG_PTR)szFileData + RVATwoOffset64(NtHeader64,ExportTable->Name));

			m_EditTable1.Format(L"%S",DllName);


			NameOfArrayRVA = (ULONG_PTR)(ExportTable->AddressOfNames);
			m_EditTable3.Format(L"0x%p",NameOfArrayRVA);
			NameOfArrayRVA = RVATwoOffset64(NtHeader64,NameOfArrayRVA);
			NameOfArray = (ULONG*)((ULONG_PTR)szFileData + NameOfArrayRVA);
			CHAR* wzFuncName = NULL;


			OrdinalsOfArrayRVA = (ULONG_PTR)ExportTable->AddressOfNameOrdinals;
			m_EditTable4.Format(L"0x%p",OrdinalsOfArrayRVA);
			OrdinalsOfArrayRVA = RVATwoOffset64(NtHeader64,OrdinalsOfArrayRVA);
			OrdinalsOfArray =  (WORD*)((ULONG_PTR)szFileData + OrdinalsOfArrayRVA);


			FuncAddressOfArrayRVA = (ULONG_PTR)ExportTable->AddressOfFunctions;
			m_EditTable2.Format(L"0x%p",FuncAddressOfArrayRVA);
			FuncAddressOfArrayRVA = RVATwoOffset64(NtHeader64,FuncAddressOfArrayRVA);
			FuncAddressOfArray = (ULONG*)((ULONG_PTR)szFileData + FuncAddressOfArrayRVA);


			for (int i=0;i<ExportTable->NumberOfNames;i++)
			{
				wzFuncName = (CHAR*)((ULONG_PTR)szFileData+RVATwoOffset64(NtHeader64,NameOfArray[i]));
				FuncAdress  =(ULONG_PTR)szFileData + RVATwoOffset64(NtHeader64,FuncAddressOfArray[OrdinalsOfArray[i]]);

				strIndex.Format(L"%d",OrdinalsOfArray[i]);
				strFuncName.Format(L"%S",wzFuncName);
				strFuncAddr.Format(L"0x%x",FuncAdress);
				strRVA.Format(L"0x%x",FuncAddressOfArray[OrdinalsOfArray[i]]);
				strOffset.Format(L"0x%x",RVATwoOffset64(NtHeader64,FuncAddressOfArray[OrdinalsOfArray[i]]));


				int n = m_ListTable.GetItemCount();
				int j = m_ListTable.InsertItem(n, strIndex);
				m_ListTable.SetItemText(j, 1, strFuncName);
				m_ListTable.SetItemText(j, 2, strFuncAddr);
				m_ListTable.SetItemText(j,3,strRVA);
				m_ListTable.SetItemText(j,4,strOffset);

			}


			break;
		}
	default:
		break;

	}

	UpdateData(FALSE);
}

DWORD RVATwoOffset(PIMAGE_NT_HEADERS32 NTHeader, ULONG ulRVA)   
{
    PIMAGE_SECTION_HEADER SectionHeader =
		(PIMAGE_SECTION_HEADER)((ULONG)NTHeader + sizeof(IMAGE_NT_HEADERS32));  //获得节表  
	
    for(int i = 0; i < NTHeader->FileHeader.NumberOfSections; i++)
    {
        if(ulRVA >= SectionHeader[i].VirtualAddress && ulRVA < 
			(SectionHeader[i].VirtualAddress 
			+ SectionHeader[i].SizeOfRawData))
        {
			//文件偏移
            return SectionHeader[i].PointerToRawData + 
				(ulRVA - SectionHeader[i].VirtualAddress);            //节文件偏移     加上  目录RVA-节RVA  
        }
    }
	
    return 0;
}

ULONG_PTR RVATwoOffset64(PIMAGE_NT_HEADERS64 NTHeader, ULONG_PTR ulRVA)   
{
    PIMAGE_SECTION_HEADER SectionHeader =
		(PIMAGE_SECTION_HEADER)((ULONG_PTR)NTHeader + sizeof(IMAGE_NT_HEADERS64));  //获得节表  
	
    for(int i = 0; i < NTHeader->FileHeader.NumberOfSections; i++)
    {

        if(ulRVA >= SectionHeader[i].VirtualAddress && ulRVA < 
			(SectionHeader[i].VirtualAddress 
			+ SectionHeader[i].SizeOfRawData))
        {
			//文件偏移
            return SectionHeader[i].PointerToRawData + 
				(ulRVA - SectionHeader[i].VirtualAddress);
        }
    }
	
    return 0;
}




VOID
	CPETableDlg::ShowRelocTable(CHAR*	szFileData,PETYPE PeType)
{
	PIMAGE_NT_HEADERS						NtHead = NULL;
	PIMAGE_NT_HEADERS64					NtHeader64 = NULL;
	PIMAGE_NT_HEADERS32					NtHeader32 = NULL;
	IMAGE_OPTIONAL_HEADER32			OptionHead32;
	IMAGE_OPTIONAL_HEADER64			OptionHead64;
	IMAGE_DATA_DIRECTORY				RelocDirectory = {0};

	PIMAGE_BASE_RELOCATION		RelocTable = NULL;
	ULONG_PTR										RelocRVA = 0;
	ULONG_PTR										BlocSize = 0;
	ULONG_PTR										RelocDataOffset = 0;

	CString													strRelocRVA,strRelocOffset,strRelocDataRVA,strRelcoDataOffset,strRelocDataOffset,strRelocData,strRelocSize;
	CString													strTypeOffset,strSizeOfBlock;

	while(m_ListTable.DeleteColumn(0));
	m_ListTable.DeleteAllItems();

	m_ListTable.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_HEADERDRAGDROP);



	UINT	i = 0;
	for (i = 0;i<g_Column_Count_RelocTable;i++)
	{
		ULONG ulLength = 0;

		ulLength = ((float)g_Column_RelocTableList[i].nWidth/(float)g_Column_Size_RelocTable)*(float)g_dx;

		m_ListTable.InsertColumn(i, g_Column_RelocTableList[i].szTitle,LVCFMT_LEFT,ulLength);
	}



	if (szFileData==NULL)
	{
		return;
	}

	PIMAGE_DOS_HEADER DosHead = (PIMAGE_DOS_HEADER)szFileData;
	NtHead = (PIMAGE_NT_HEADERS)((ULONG)szFileData+DosHead->e_lfanew);

	switch (PeType)
	{
	case Bit32:
		{
			NtHeader32 = (PIMAGE_NT_HEADERS32)NtHead;
			OptionHead32 = NtHeader32->OptionalHeader;

			RelocDirectory = OptionHead32.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC]; 

			if (RelocDirectory.Size==0)
			{
				return;
			}

			DWORD		Temp = RVATwoOffset(NtHeader32,RelocDirectory.VirtualAddress);     //RVA转换文件相对偏移

			if (Temp==0)
			{
				return;
			}

			RelocTable = (PIMAGE_BASE_RELOCATION)((ULONG_PTR)szFileData+Temp);

			do 
			{
				ULONG_PTR		NumOfReloc=(RelocTable->SizeOfBlock-sizeof(IMAGE_BASE_RELOCATION))/2;        //???    为什么要除以2   

				SHORT			MiniOffset = 0;

				PSHORT 	RelocData =(PSHORT)((ULONG_PTR)RelocTable+sizeof(IMAGE_BASE_RELOCATION));

				for (i=0; i<NumOfReloc; i++) 
				{
					PULONG_PTR RelocAddress = 0;//需要重定位的地址

					if (((*RelocData)>>12)==IMAGE_REL_BASED_DIR64||((*RelocData)>>12)==IMAGE_REL_BASED_HIGHLOW)//判断重定位类型是否为IMAGE_REL_BASED_HIGHLOW[32]或IMAGE_REL_BASED_DIR64[64]
					{
						MiniOffset = (*RelocData)&0xfff;     //保留后12个字节的偏移    去除高4位的标志


						RelocDataOffset = (ULONG_PTR)RVATwoOffset(NtHeader32,MiniOffset+RelocTable->VirtualAddress);      //重定项在本页中的偏移

						strSizeOfBlock.Format(L"0x%x",RelocTable->SizeOfBlock);        //大小
						strTypeOffset.Format(L"0x%x",(*RelocData));					//重定项中数据

						strRelocRVA.Format(L"0x%x",RelocTable->VirtualAddress);		//本页的RVA
						strRelocOffset.Format(L"0x%x",RVATwoOffset(NtHeader32,RelocTable->VirtualAddress));    //本页相对文件偏移

						strRelocDataRVA.Format(L"0x%x",MiniOffset+RelocTable->VirtualAddress);				//重定项地址的RVA
						strRelocDataOffset.Format(L"0x%x",RelocDataOffset);									//重定项在本页中的偏移

						strRelocData.Format(L"0x%x",*(PULONG_PTR)((ULONG_PTR)szFileData+ RelocDataOffset));     //？？？

						int n = m_ListTable.GetItemCount();
						int j = m_ListTable.InsertItem(n, strRelocRVA);
						m_ListTable.SetItemText(j, 1, strRelocOffset);
						m_ListTable.SetItemText(j, 2, strSizeOfBlock);
						m_ListTable.SetItemText(j,3,strTypeOffset);
						m_ListTable.SetItemText(j,4,strRelocDataRVA);
						m_ListTable.SetItemText(j,5,strRelocDataOffset);
						m_ListTable.SetItemText(j,6,strRelocData);

					}

					RelocData++;
				}

				RelocTable=(PIMAGE_BASE_RELOCATION)((ULONG_PTR)RelocTable+RelocTable->SizeOfBlock);

			} while (RelocTable->VirtualAddress);


			break;
		}

	case Bit64:
		{
			NtHeader64 = (PIMAGE_NT_HEADERS64)NtHead;
			OptionHead64 = NtHeader64->OptionalHeader;

			RelocDirectory = OptionHead64.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC]; 

			if (RelocDirectory.Size==0)
			{
				return;
			}

			DWORD		Temp = RVATwoOffset64(NtHeader64,RelocDirectory.VirtualAddress);

			if (Temp==0)
			{
				return;
			}

			RelocTable = (PIMAGE_BASE_RELOCATION)((ULONG_PTR)szFileData+Temp);

			do 
			{
				ULONG_PTR		NumOfReloc=(RelocTable->SizeOfBlock-sizeof(IMAGE_BASE_RELOCATION))/2;

				SHORT				MiniOffset = 0;
				PUSHORT 			RelocData =(PUSHORT)((ULONG_PTR)RelocTable+sizeof(IMAGE_BASE_RELOCATION));

				for (i=0; i<NumOfReloc; i++) 
				{
					PULONG_PTR RelocAddress = 0;//需要重定位的地址

					if (((*RelocData)>>12)==IMAGE_REL_BASED_DIR64)//判断重定位类型是否为IMAGE_REL_BASED_HIGHLOW[32]或IMAGE_REL_BASED_DIR64[64]
					{
						MiniOffset = (*RelocData)&0xfff;


						RelocDataOffset = (ULONG_PTR)RVATwoOffset64(NtHeader64,MiniOffset+RelocTable->VirtualAddress);

						strSizeOfBlock.Format(L"0x%x",RelocTable->SizeOfBlock);
						strTypeOffset.Format(L"0x%x",(*RelocData));

						strRelocRVA.Format(L"0x%x",RelocTable->VirtualAddress);
						strRelocOffset.Format(L"0x%x",RVATwoOffset64(NtHeader64,RelocTable->VirtualAddress));

						strRelocDataRVA.Format(L"0x%x",MiniOffset+RelocTable->VirtualAddress);
						strRelocDataOffset.Format(L"0x%x",RVATwoOffset64(NtHeader64,MiniOffset+RelocTable->VirtualAddress));

						strRelocData.Format(L"0x%x",*(PULONG_PTR)((ULONG_PTR)szFileData+ RelocDataOffset));

						int n = m_ListTable.GetItemCount();
						int j = m_ListTable.InsertItem(n, strRelocRVA);
						m_ListTable.SetItemText(j, 1, strRelocOffset);
						m_ListTable.SetItemText(j, 2, strSizeOfBlock);
						m_ListTable.SetItemText(j,3,strTypeOffset);
						m_ListTable.SetItemText(j,4,strRelocDataRVA);
						m_ListTable.SetItemText(j,5,strRelocDataOffset);
						m_ListTable.SetItemText(j,6,strRelocData);


					}

					RelocData++;
				}

				RelocTable=(PIMAGE_BASE_RELOCATION)((ULONG_PTR)RelocTable+RelocTable->SizeOfBlock);

			} while (RelocTable->VirtualAddress);


			break;
		}

	default:
		break;
	}

}



