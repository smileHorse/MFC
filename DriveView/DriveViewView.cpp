
// DriveViewView.cpp : CDriveViewView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "DriveView.h"
#endif

#include "DriveViewDoc.h"
#include "DriveViewView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// Image indexes
#define ILI_HARD_DISK		0
#define ILI_FLOPPY			1
#define ILI_CD_ROM			2
#define ILI_NET_DRIVE		3
#define ILI_CLOSED_FOLDER	4
#define ILI_OPEN_FOLDER		5

// CDriveViewView

IMPLEMENT_DYNCREATE(CDriveViewView, CTreeView)

BEGIN_MESSAGE_MAP(CDriveViewView, CTreeView)
	//{{AFX_MSG_MAP(CDriveView)
	ON_NOTIFY_REFLECT(TVN_ITEMEXPANDING, OnItemExpanding)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// CDriveViewView ����/����

CDriveViewView::CDriveViewView()
{
	// TODO: �ڴ˴���ӹ������

}

CDriveViewView::~CDriveViewView()
{
}

BOOL CDriveViewView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	if (!CTreeView::PreCreateWindow(cs))
	{
		return FALSE;
	}

	cs.style |= TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS | TVS_SHOWSELALWAYS;
	return TRUE;
}

void CDriveViewView::OnInitialUpdate()
{
	CTreeView::OnInitialUpdate();

	// Initialize the image list
	m_ilDrives.Create(IDB_DRIVEIMAGES, 16, 1, RGB(255, 0, 255));
	GetTreeCtrl().SetImageList(&m_ilDrives, TVSIL_NORMAL);

	// populate the tree view with drive items
	AddDrives();

	// show the folders of on the current drive

	TCHAR szPath[MAX_PATH];
	::GetCurrentDirectory(sizeof(szPath) / sizeof(TCHAR), szPath);
	CString strPath = szPath;
	strPath = strPath.Left(3);

	HTREEITEM hItem = GetTreeCtrl().GetNextItem(NULL, TVGN_ROOT);
	while (hItem != NULL)
	{
		if (GetTreeCtrl().GetItemText(hItem) == strPath)
		{
			break;
		}
		hItem = GetTreeCtrl().GetNextSiblingItem(hItem);
	}

	if (hItem != NULL)
	{
		GetTreeCtrl().Expand(hItem, TVE_EXPAND);
		GetTreeCtrl().Select(hItem, TVGN_CARET);
	}
}

// CDriveViewView ����

void CDriveViewView::OnDraw(CDC* /*pDC*/)
{
	CDriveViewDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CDriveViewView ���

#ifdef _DEBUG
void CDriveViewView::AssertValid() const
{
	CTreeView::AssertValid();
}

void CDriveViewView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}

BOOL CDriveViewView::AddDriveItem(LPCTSTR pszDrive)
{
	CString string;
	HTREEITEM hItem;

	UINT nType = ::GetDriveType(pszDrive);
	switch (nType)
	{
	case DRIVE_REMOVABLE:
		hItem = GetTreeCtrl().InsertItem(pszDrive, ILI_FLOPPY, ILI_FLOPPY);
		GetTreeCtrl().InsertItem(_T(""), ILI_CLOSED_FOLDER, ILI_CLOSED_FOLDER, hItem);
		break;
	case DRIVE_FIXED:
	case DRIVE_RAMDISK:
		hItem = GetTreeCtrl().InsertItem(pszDrive, ILI_HARD_DISK, ILI_HARD_DISK);
		SetButtonState(hItem, pszDrive);
		break;
	case DRIVE_REMOTE:
		hItem = GetTreeCtrl().InsertItem(pszDrive, ILI_NET_DRIVE, ILI_NET_DRIVE);
		SetButtonState(hItem, pszDrive);
		break;
	case DRIVE_CDROM:
		hItem = GetTreeCtrl().InsertItem(pszDrive, ILI_CD_ROM, ILI_CD_ROM);
		GetTreeCtrl().InsertItem(_T(""), ILI_CLOSED_FOLDER, ILI_CLOSED_FOLDER, hItem);
		break;
	default:
		return FALSE;
	}
	return TRUE;
}

int CDriveViewView::AddDirectories(HTREEITEM hItem, LPCTSTR pszPath)
{
	HANDLE hFind;
	WIN32_FIND_DATA fd;
	HTREEITEM hNewItem;

	int nCount = 0;

	CString strPath = pszPath;
	if (strPath.Right(1) != _T("\\"))
	{
		strPath += _T("\\");
	}
	strPath += _T("*.*");

	if ((hFind = ::FindFirstFile(strPath, &fd)) == INVALID_HANDLE_VALUE)
	{
		if (GetTreeCtrl().GetParentItem(hItem) == NULL)
		{
			GetTreeCtrl().InsertItem(_T(""), ILI_CLOSED_FOLDER, ILI_CLOSED_FOLDER, hItem);
			return 0;
		}
	}
	do 
	{
		if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			CString strComp = (LPCTSTR)&fd.cFileName;
			if ((strComp != _T(".") && strComp != _T("..")))
			{
				hNewItem = GetTreeCtrl().InsertItem((LPCTSTR)&fd.cFileName, ILI_CLOSED_FOLDER,
					ILI_CLOSED_FOLDER, hItem);
				CString strNewPath = pszPath;
				if (strNewPath.Right(1) != _T("\\"))
				{
					strNewPath += _T("\\");
				}

				strNewPath += (LPCTSTR)&fd.cFileName;
				SetButtonState(hNewItem, strNewPath);
				nCount++;
			}
		}
	} while (::FindNextFile(hFind, &fd));

	::FindClose(hFind);
	return nCount;
}

void CDriveViewView::DeleteAllChildren(HTREEITEM hItem)
{
	HTREEITEM hChildItem;
	if ((hChildItem = GetTreeCtrl().GetChildItem(hItem)) == NULL)
	{
		return;
	}

	do 
	{
		HTREEITEM hNextItem = GetTreeCtrl().GetNextSiblingItem(hChildItem);
		GetTreeCtrl().DeleteItem(hChildItem);
		hChildItem = hNextItem;
	} while (hChildItem != NULL);
}

void CDriveViewView::DeleteFirstChild(HTREEITEM hItem)
{
	HTREEITEM hChildItem;
	if ((hChildItem = GetTreeCtrl().GetChildItem(hItem)) != NULL)
	{
		GetTreeCtrl().DeleteItem(hChildItem);
	}
}

CString CDriveViewView::GetPathFromItem(HTREEITEM hItem)
{
	CString strResult = GetTreeCtrl().GetItemText(hItem);

	HTREEITEM hParent;
	while ((hParent = GetTreeCtrl().GetParentItem(hItem)) != NULL)
	{
		CString string = GetTreeCtrl().GetItemText(hParent);
		if (string.Right(1) != _T("\\"))
		{
			string += _T("\\");
		}
		strResult = string + strResult;
		hItem = hParent;
	}
	return strResult;
}

BOOL CDriveViewView::SetButtonState(HTREEITEM hItem, LPCTSTR pszPath)
{
	HANDLE hFind;
	WIN32_FIND_DATA fd;
	BOOL bResult = FALSE;

	CString strPath = pszPath;
	if (strPath.Right(1) != _T("\\"))
	{
		strPath += _T("\\");
	}
	strPath += _T("*.*");
	if ((hFind = ::FindFirstFile(strPath, &fd)) == INVALID_HANDLE_VALUE)
	{
		return bResult;
	}
	do 
	{
		if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			CString strComp = (LPCTSTR)&fd.cFileName;
			if ((strComp != _T(".")) && (strComp != _T("..")))
			{
				GetTreeCtrl().InsertItem(_T(""), ILI_CLOSED_FOLDER, ILI_CLOSED_FOLDER, hItem);
				bResult = TRUE;
				break;
			}
		}
	} while (::FindNextFile(hFind, &fd));

	::FindClose(hFind);
	return bResult;
}

int CDriveViewView::AddDrives()
{
	int nPos = 0;
	int nDrivesAdded = 0;
	CString string = _T("?:\\");

	DWORD dwDriveList = ::GetLogicalDrives();
	while (dwDriveList)
	{
		if (dwDriveList & 1)
		{
			string.SetAt(0, _T('A') + nPos);
			if (AddDriveItem(string))
			{
				nDrivesAdded++;
			}
		}
		dwDriveList >>= 1;
		nPos++;
	}
	return nDrivesAdded;
}

void CDriveViewView::OnItemExpanding(NMHDR* pNMHDR, LRESULT* pResult)
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	HTREEITEM hItem = pNMTreeView->itemNew.hItem;
	CString string = GetPathFromItem(hItem);

	*pResult = FALSE;

	if (pNMTreeView->action == TVE_EXPAND)
	{
		DeleteFirstChild(hItem);
		if (AddDirectories(hItem, string) == 0)
		{
			*pResult = TRUE;
		}
	}
	else
	{
		DeleteAllChildren(hItem);
		if (GetTreeCtrl().GetParentItem(hItem) == NULL)
		{
			GetTreeCtrl().InsertItem(_T(""), ILI_CLOSED_FOLDER, ILI_CLOSED_FOLDER, hItem);
		}
		else
		{
			SetButtonState(hItem, string);
		}
	}
}

CDriveViewDoc* CDriveViewView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDriveViewDoc)));
	return (CDriveViewDoc*)m_pDocument;
}
#endif //_DEBUG


// CDriveViewView ��Ϣ�������
