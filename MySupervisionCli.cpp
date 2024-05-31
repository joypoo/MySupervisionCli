
// MySupervisionCli.cpp: 定义应用程序的类行为。
// My C++ solution for Project Euler 363: Bezier Curves
// https://euler.stephan-brumme.com/363/

#include "pch.h"
#include "framework.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "MySupervisionCli.h"
#include "MainFrm.h"

#include "MySupervisionCliDoc.h"
#include "MySupervisionCliView.h"

//#include "SiderDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMySupervisionCliApp

BEGIN_MESSAGE_MAP(CMySupervisionCliApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CMySupervisionCliApp::OnAppAbout)
	// 基于文件的标准文档命令
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
	// 标准打印设置命令
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinAppEx::OnFilePrintSetup)
END_MESSAGE_MAP()


// CMySupervisionCliApp 构造

CMySupervisionCliApp::CMySupervisionCliApp() noexcept
{
	m_bHiColorIcons = TRUE;


	m_nAppLook = 0;
	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// 如果应用程序是利用公共语言运行时支持(/clr)构建的，则: 
	//     1) 必须有此附加设置，“重新启动管理器”支持才能正常工作。
	//     2) 在您的项目中，您必须按照生成顺序向 System.Windows.Forms 添加引用。
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: 将以下应用程序 ID 字符串替换为唯一的 ID 字符串；建议的字符串格式
	//为 CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("MySupervisionCli.AppID.NoVersion"));

	// TODO:  在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}

// 唯一的 CMySupervisionCliApp 对象

CMySupervisionCliApp theApp;


// CMySupervisionCliApp 初始化

BOOL CMySupervisionCliApp::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。  否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();


	// 初始化 OLE 库
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction(FALSE);

	// 使用 RichEdit 控件需要 AfxInitRichEdit2()
	// AfxInitRichEdit2();

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("ZXIApp"));
	LoadStdProfileSettings(4);  // 加载标准 INI 文件选项(包括 MRU)


	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// 注册应用程序的文档模板。  文档模板
	// 将用作文档、框架窗口和视图之间的连接
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CMySupervisionCliDoc),
		RUNTIME_CLASS(CMainFrame),       // 主 SDI 框架窗口
		RUNTIME_CLASS(CMySupervisionCliView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);


	// 分析标准 shell 命令、DDE、打开文件操作的命令行
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);



	// 调度在命令行中指定的命令。  如果
	// 用 /RegServer、/Register、/Unregserver 或 /Unregister 启动应用程序，则返回 FALSE。
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// 唯一的一个窗口已初始化，因此显示它并对其进行更新
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	

	//m_wndSider.DoModal();
	return TRUE;
}

int CMySupervisionCliApp::ExitInstance()
{
	//TODO: 处理可能已添加的附加资源
	AfxOleTerm(FALSE);

	return CWinAppEx::ExitInstance();
}

// CMySupervisionCliApp 消息处理程序


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg() noexcept;

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_ListCtrl2;
	virtual BOOL OnInitDialog();
};

CAboutDlg::CAboutDlg() noexcept : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, m_ListCtrl2);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// 用于运行对话框的应用程序命令
void CMySupervisionCliApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
	//CSiderDlg siderDlg;
	//siderDlg.DoModal();
}

// CMySupervisionCliApp 自定义加载/保存方法

void CMySupervisionCliApp::PreLoadState()
{
	BOOL bNameValid;
	CString strName;
	bNameValid = strName.LoadString(IDS_EDIT_MENU);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);
	bNameValid = strName.LoadString(IDS_EXPLORER);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EXPLORER);
}

void CMySupervisionCliApp::LoadCustomState()
{
}

void CMySupervisionCliApp::SaveCustomState()
{
}

// CMySupervisionCliApp 消息处理程序

//计算组合数
int CMySupervisionCliApp::binomial(int n, int i)
{
	double res = 1.0f;
	//int res = 1;
	for (int j = 1; j <= i; ++j) {
		res *= ((n - j + 1) / (double)j); //(double)十分关键，不然j=i=n时，j为分数=0；
	}
	return (int)res;
}

// 计算n次贝塞尔曲线上的点
Point CMySupervisionCliApp::bezier_curve(const vector<Point>& points, float t) 
{
	int n = (int)points.size() - 1;

	points1.assign(points.begin() + n - nLenPointsShow, points.end());
	//float ftmp;

	//for (int nTrs = 30; nTrs > 0; nTrs--, n--) { //只取最近30个
	//	points1[nTrs].x = points[n].x;
	//}
	n = (int)points1.size() - 1;

	Point res;
	//CString str;
	//str.Format("%d", n);
	//AfxMessageBox(str);
	
	//for (int i = 0; i <= n; ++i) {
	for (int i = n; i >  n - ptSize; --i) { //取最近的??个
		//std::cout << "p:" << points[i].x << "," << points[i].y << endl;
		float b = (float)(binomial(n, i) * pow(t, i) * pow(1 - t, n - i));
		//std::cout << "bino=" << binomial(n, i) << endl;
		res.x = res.x + points1[i].x * b;
		res.y = res.y + points1[i].y * b;
		res.z = res.z + points1[i].z * b;
	}
	return res;
}

void CMySupervisionCliApp::Marker(HDC hDC, LONG x, LONG y)
{
	//HDC hDC;

	//hDC = GetDC(hwnd);
	MoveToEx(hDC, (int)x - 10, (int)y, (LPPOINT)NULL);
	LineTo(hDC, (int)x + 10, (int)y);
	MoveToEx(hDC, (int)x, (int)y - 10, (LPPOINT)NULL);
	LineTo(hDC, (int)x, (int)y + 10);

	//ReleaseDC(hDC);
}

BOOL CAboutDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_ListCtrl2.InsertColumn(0, "Item", LVCFMT_LEFT, 100);
	m_ListCtrl2.InsertColumn(1, "ItemData1", LVCFMT_LEFT, 200);
	m_ListCtrl2.InsertColumn(2, "ItemData2", LVCFMT_LEFT, 200);

	for(int i = 0; i < 10; i++){
		m_ListCtrl2.InsertItem(i, "Item 1");
		m_ListCtrl2.SetItemText(i, 1, "Item 1 Data 1");
		m_ListCtrl2.SetItemText(i, 2, "Item 1 Data 2");
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
