
#pragma once

/////////////////////////////////////////////////////////////////////////////
// COutputList 窗口
//#include "SiderDlg.h"
class CDataList :public CListCtrl
{
public:
	CDataList() noexcept;
public:
	virtual ~CDataList();

	DECLARE_MESSAGE_MAP()
	afx_msg void OnNMClick(NMHDR* pNMHDR, LRESULT* pResult);
//	afx_msg void OnNMDblclk(NMHDR* pNMHDR, LRESULT* pResult);
};

class COutputList : public CListBox
{
// 构造
public:
	COutputList() noexcept;

// 实现
public:
	virtual ~COutputList();

protected:
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnEditCopy();
	afx_msg void OnEditClear();
	afx_msg void OnViewOutput();

	DECLARE_MESSAGE_MAP()
};

class COutputWnd : public CDockablePane
{
// 构造
public:
	COutputWnd() noexcept;

	void UpdateFonts();

// 特性
protected:
	CMFCTabCtrl	m_wndTabs;
	
	//COutputList m_wndOutputBuild;
	COutputList m_wndOutputDebug;
	COutputList m_wndOutputFind;
	CDataList m_wndDataList;
	CDialog m_DetailDlg;
protected:
	CButton m_btn_upd;
	void FillBuildWindow();
	void FillDebugWindow();
	void FillFindWindow();

	void AdjustHorzScroll(CListBox& wndListBox);

// 实现
public:
	virtual ~COutputWnd();

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBtnUpdate();
};

