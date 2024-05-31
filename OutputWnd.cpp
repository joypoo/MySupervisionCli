
#include "pch.h"
#include "framework.h"

#include "OutputWnd.h"
#include "Resource.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COutputBar

COutputWnd::COutputWnd() noexcept
{
}

COutputWnd::~COutputWnd()
{
}

BEGIN_MESSAGE_MAP(COutputWnd, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BTN_UPDATE, &COutputWnd::OnBtnUpdate)
END_MESSAGE_MAP()

int COutputWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	CRect rect;
	rect.SetRect(rectDummy.left + 20, rectDummy.top + 5, rectDummy.left + 20 + 80, rectDummy.top + 5 + 35);

	//m_btn_upd.Create("升级", WS_CHILD | WS_VISIBLE | BS_FLAT, rect, this, IDC_BTN_UPDATE);

	//rectDummy.top = rectDummy.top + 45;
	//rectDummy.bottom = rectDummy.bottom - 90;
	// 创建选项卡窗口: 
	if (!m_wndTabs.Create(CMFCTabCtrl::STYLE_FLAT, rectDummy, this, 1))
	{
		TRACE0("未能创建输出选项卡窗口\n");
		return -1;      // 未能创建
	}
	TRACE0("创建输出选项卡窗口成功\n");

	// 创建输出窗格: 
	const DWORD dwStyle = LBS_NOINTEGRALHEIGHT | WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL;

	if (!m_wndOutputDebug.Create(dwStyle, rectDummy, &m_wndTabs, 3) ||
		!m_wndOutputFind.Create(dwStyle, rectDummy, &m_wndTabs, 4))
	{
		TRACE0("未能创建输出窗口\n");
		return -1;      // 未能创建
	}
	TRACE0("创建输出窗口成功\n");

	if (!m_wndDataList.Create(LVS_REPORT,
		rectDummy, &m_wndTabs, 2)) {
		TRACE0("未能创建输出窗口\n");
		return -1;      // 未能创建
	}
	m_wndDataList.SetExtendedStyle(LVS_EX_CHECKBOXES | LVS_EX_FULLROWSELECT);//设定列表一行全部选中的特性

	m_wndDataList.InsertColumn(0, "车牌号码", LVCFMT_LEFT, 100);
	m_wndDataList.InsertColumn(1, "ISU ID", LVCFMT_LEFT, 200);
	m_wndDataList.InsertColumn(2, "当前版本", LVCFMT_LEFT, 200);
	for (int i = 0; i < 50; i++) {
		m_wndDataList.InsertItem(i, "浙A9TT00");
		m_wndDataList.SetItemText(i, 1, "10991234560");
		m_wndDataList.SetItemText(i, 2, "1.3.2");

		m_wndDataList.InsertItem(i + 1, "浙A9TT01");
		m_wndDataList.SetItemText(i + 1, 1, "10991234561");
		m_wndDataList.SetItemText(i + 1, 2, "1.3.2");
	}


	//if (!m_wndOutputBuild.Create(dwStyle, rectDummy, &m_wndTabs, 2))

	//CSiderDlg* m_lstInfo = (CSiderDlg*)GetDlgItem(IDD_DIALOG_SIDER);
	//if (!m_DetailDlg.Create(IDD_DIALOG_SIDER, GetDlgItem(1))) //this->GetParent()
	//{
	//	TRACE0("未能创建输出窗口OutputBuild\n");
	//	return -1;      // 未能创建
	//}

	//UpdateFonts();

	CString strTabName = "数据列表";
	BOOL bNameValid;

	// 将列表窗口附加到选项卡: 
	//bNameValid = strTabName.LoadString(IDS_MDT_LIST_TAB);
	//ASSERT(bNameValid);
	m_wndTabs.AddTab(&m_wndDataList, strTabName, (UINT)0);
	//m_wndTabs.AddTab(&m_DetailDlg, strTabName, (UINT)0);

	//bNameValid = strTabName.LoadString(IDS_BUILD_TAB);
	//ASSERT(bNameValid);
	//m_wndTabs.AddTab(&m_wndOutputBuild, strTabName, (UINT)0);

	bNameValid = strTabName.LoadString(IDS_DEBUG_TAB);
	ASSERT(bNameValid);
	m_wndTabs.AddTab(&m_wndOutputDebug, strTabName, (UINT)1);

	bNameValid = strTabName.LoadString(IDS_FIND_TAB);
	ASSERT(bNameValid);
	m_wndTabs.AddTab(&m_wndOutputFind, strTabName, (UINT)2); 

	// 使用一些虚拟文本填写输出选项卡(无需复杂数据)
	//FillBuildWindow();
	FillDebugWindow();
	FillFindWindow();

	return 0;
}

void COutputWnd::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);

	// 选项卡控件应覆盖整个工作区: 
	m_wndTabs.SetWindowPos (nullptr, -1, -1, cx, cy, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
}

void COutputWnd::AdjustHorzScroll(CListBox& wndListBox)
{
	CClientDC dc(this);
	CFont* pOldFont = dc.SelectObject(&afxGlobalData.fontRegular);

	int cxExtentMax = 0;

	for (int i = 0; i < wndListBox.GetCount(); i ++)
	{
		CString strItem;
		wndListBox.GetText(i, strItem);

		cxExtentMax = max(cxExtentMax, (int)dc.GetTextExtent(strItem).cx);
	}

	wndListBox.SetHorizontalExtent(cxExtentMax);
	dc.SelectObject(pOldFont);
}

void COutputWnd::FillBuildWindow()
{
	//m_wndOutputBuild.AddString(_T("日志："));
	//for (int i = 0; i < 10; i++) {
	//	m_wndOutputBuild.AddString(_T("生成输出正显示在此处。"));
	//	m_wndOutputBuild.AddString(_T("输出正显示在列表视图的行中"));
	//	m_wndOutputBuild.AddString(_T("但您可以根据需要更改其显示方式..."));
	//}
}

void COutputWnd::FillDebugWindow()
{
	m_wndOutputDebug.AddString(_T("警告输出正显示在此处。"));
	m_wndOutputDebug.AddString(_T("输出正显示在列表视图的行中"));
	m_wndOutputDebug.AddString(_T("但您可以根据需要更改其显示方式..."));
}

void COutputWnd::FillFindWindow()
{
	m_wndOutputFind.AddString(_T("错误输出正显示在此处。"));
	m_wndOutputFind.AddString(_T("输出正显示在列表视图的行中"));
	m_wndOutputFind.AddString(_T("但您可以根据需要更改其显示方式..."));
}

void COutputWnd::UpdateFonts()
{
	//m_wndOutputBuild.SetFont(&afxGlobalData.fontRegular);
	m_wndOutputDebug.SetFont(&afxGlobalData.fontRegular);
	m_wndOutputFind.SetFont(&afxGlobalData.fontRegular);
}

CDataList::CDataList() noexcept
{

}
CDataList::~CDataList()
{

}


/////////////////////////////////////////////////////////////////////////////
// COutputList1

COutputList::COutputList() noexcept
{
}

COutputList::~COutputList()
{
}

BEGIN_MESSAGE_MAP(COutputList, CListBox)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_CLEAR, OnEditClear)
	ON_COMMAND(ID_VIEW_OUTPUTWND, OnViewOutput)
	ON_WM_WINDOWPOSCHANGING()
END_MESSAGE_MAP()
/////////////////////////////////////////////////////////////////////////////
// COutputList 消息处理程序

void COutputList::OnContextMenu(CWnd* /*pWnd*/, CPoint point)
{
	CMenu menu;
	menu.LoadMenu(IDR_OUTPUT_POPUP);

	CMenu* pSumMenu = menu.GetSubMenu(0);

	if (AfxGetMainWnd()->IsKindOf(RUNTIME_CLASS(CMDIFrameWndEx)))
	{
		CMFCPopupMenu* pPopupMenu = new CMFCPopupMenu;

		if (!pPopupMenu->Create(this, point.x, point.y, (HMENU)pSumMenu->m_hMenu, FALSE, TRUE))
			return;

		((CMDIFrameWndEx*)AfxGetMainWnd())->OnShowPopupMenu(pPopupMenu);
		UpdateDialogControls(this, FALSE);
	}

	SetFocus();
}

void COutputList::OnEditCopy()
{
	MessageBox(_T("复制输出"));
}

void COutputList::OnEditClear()
{
	MessageBox(_T("清除输出"));
}

void COutputList::OnViewOutput()
{
	CDockablePane* pParentBar = DYNAMIC_DOWNCAST(CDockablePane, GetOwner());
	CMDIFrameWndEx* pMainFrame = DYNAMIC_DOWNCAST(CMDIFrameWndEx, GetTopLevelFrame());

	if (pMainFrame != nullptr && pParentBar != nullptr)
	{
		pMainFrame->SetFocus();
		pMainFrame->ShowPane(pParentBar, FALSE, FALSE, FALSE);
		pMainFrame->RecalcLayout();

	}
}
BEGIN_MESSAGE_MAP(CDataList, CListCtrl)
	ON_NOTIFY_REFLECT(NM_CLICK, &CDataList::OnNMClick)
END_MESSAGE_MAP()


void CDataList::OnNMClick(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	CString str;
	int nRow = pNMItemActivate->iItem; //获取单击的行号
	//int nRow;
	//CListCtrl* pListCtrl = (CListCtrl*)GetDlgItem(IDC_LIST2); //窗口句柄转换成类指针
	//CPoint ptClicked = pNMItemActivate->ptAction; // 获取鼠标单击位置
	//nRow = HitTest(ptClicked); // 获取鼠标位置所在的行

	int nColumn = pNMItemActivate->iSubItem;

	str.Format("ROW=%d, COL=%d\r\n", nRow, nColumn);
	str += "车牌号码:\t";
	str += GetItemText(nRow, 0);
	str += "\r\nISU ID:\t";
	str += GetItemText(nRow, 1);
	str += "\r\nVer:\t";
	str += GetItemText(nRow, 2);

	if (nRow != -1) MessageBox(str, "详细信息", MB_APPLMODAL | MB_ICONINFORMATION);

	*pResult = 0;
}


void COutputWnd::OnBtnUpdate()
{
	// TODO: 在此添加命令处理程序代码
	Invalidate();
}
