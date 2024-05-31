
#pragma once

/////////////////////////////////////////////////////////////////////////////
// CViewTree 窗口
#include <vector>
using namespace std;

class CViewTree : public CTreeCtrl
{
public:
	//获取同级节点
	vector<HTREEITEM> GetSameLevelNode(CTreeCtrl& m_treeCtrl, HTREEITEM hTreeItem);
// 构造
public:
	CViewTree() noexcept;

// 重写
protected:
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);

// 实现
public:
	virtual ~CViewTree();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnNMClick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnNMDblclk(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnNMRClick(NMHDR* pNMHDR, LRESULT* pResult);
};
