
#include "pch.h"
#include "framework.h"
#include "ViewTree.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CViewTree

CViewTree::CViewTree() noexcept
{
}

CViewTree::~CViewTree()
{
}

BEGIN_MESSAGE_MAP(CViewTree, CTreeCtrl)
	ON_NOTIFY_REFLECT(NM_CLICK, &CViewTree::OnNMClick)
	ON_NOTIFY_REFLECT(NM_DBLCLK, &CViewTree::OnNMDblclk)
	ON_NOTIFY_REFLECT(NM_RCLICK, &CViewTree::OnNMRClick)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CViewTree 消息处理程序

BOOL CViewTree::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	BOOL bRes = CTreeCtrl::OnNotify(wParam, lParam, pResult);

	NMHDR* pNMHDR = (NMHDR*)lParam;
	ASSERT(pNMHDR != NULL);

	if (pNMHDR && pNMHDR->code == TTN_SHOW && GetToolTips() != NULL)
	{
		GetToolTips()->SetWindowPos(&wndTop, -1, -1, -1, -1, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOSIZE);
	}

	return bRes;

/*	BOOL bRes = CTreeCtrl::OnNotify(wParam, lParam, pResult);

	NMHDR* pNMHDR = (NMHDR*)lParam;
	ASSERT(pNMHDR != nullptr);

#pragma warning(suppress : 26454)
	if (pNMHDR && pNMHDR->code == TTN_SHOW && GetToolTips() != nullptr)
	{
		GetToolTips()->SetWindowPos(&wndTop, -1, -1, -1, -1, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOSIZE);
	}

	return bRes;
	*/
}

//单击Item
void CViewTree::OnNMClick(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	//HTREEITEM hTreeItem = GetSelectedItem();
	//CString str = GetItemText(hTreeItem);

	//MessageBox(str, "详细信息", MB_APPLMODAL | MB_ICONINFORMATION);

	*pResult = 0;
}


void CViewTree::OnNMDblclk(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	HTREEITEM hTreeItem = GetSelectedItem();
	CString str = GetItemText(hTreeItem);
	CString strParent = GetItemText(GetParentItem(hTreeItem));
	CString strParentParent = GetItemText(GetParentItem(GetParentItem(hTreeItem)));

	if (strParentParent.IsEmpty()) {
		//if (str.Compare("权限用户") == 0) {
		HTREEITEM scTreeItem = GetSelectedItem();
		HTREEITEM nodeOne = GetChildItem(scTreeItem);

		vector<HTREEITEM> result; //= GetSameLevelNode(this, scTreeItem);
		CString text;
		while (nodeOne != NULL)
		{
			result.push_back(nodeOne);
			nodeOne = GetNextSiblingItem(nodeOne);
		}
		for (size_t i = 0; i < result.size(); i++)
		{
			text += GetItemText(result[i]) + "\r\n";
			
		}
		AfxMessageBox(text);

		//MessageBox(str, "同级列表", MB_APPLMODAL | MB_ICONINFORMATION);
	}
	else {
		str = strParent + "->" + str;
		MessageBox(str, "详细信息", MB_APPLMODAL | MB_ICONINFORMATION);
	}


	*pResult = 0;
}


void CViewTree::OnNMRClick(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	int index = pNMItemActivate->iItem;
	if (index == -1)
		return;

	HMENU hMenu = ::CreatePopupMenu();
	AppendMenu(hMenu, MF_STRING, 10001, _T("升级"));
	AppendMenu(hMenu, MF_STRING, 10002, _T("定位信息"));

	CPoint pt;
	GetCursorPos(&pt); //获得当前鼠标位置
	UINT Cmd = (UINT)::TrackPopupMenu(hMenu, TPM_LEFTALIGN | TPM_RETURNCMD, pt.x, pt.y, 0, m_hWnd, NULL);//弹出菜单

	HTREEITEM hTreeItem = GetSelectedItem();
	CString str;

	switch (Cmd)//响应点击的菜单
	{
	case 10001:
		MessageBox("10001", "升级", MB_APPLMODAL | MB_ICONINFORMATION);
		break;
	case 10002:
		str.Format("%d,%s", pNMItemActivate->lParam, GetItemText(hTreeItem));
		MessageBox(str, "定位信息", MB_APPLMODAL | MB_ICONINFORMATION);
		break;
	}
	*pResult = 0;
}

vector<HTREEITEM> CViewTree::GetSameLevelNode(CTreeCtrl& m_treeCtrl, HTREEITEM hTreeItem)
{
	vector<HTREEITEM> result;
	HTREEITEM parentItem = m_treeCtrl.GetParentItem(hTreeItem);

	if (m_treeCtrl.ItemHasChildren(parentItem))
	{
		HTREEITEM nodeOne = m_treeCtrl.GetChildItem(parentItem);
		while (nodeOne != NULL)
		{
			result.push_back(nodeOne);
			nodeOne = m_treeCtrl.GetNextSiblingItem(nodeOne);
		}
	}
	return result;
}
