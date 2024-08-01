
// MySupervisionCliView.cpp: CMySupervisionCliView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MySupervisionCli.h"
#endif

#include "MySupervisionCliDoc.h"
#include "MySupervisionCliView.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define PI 3.14150265
// CMySupervisionCliView

IMPLEMENT_DYNCREATE(CMySupervisionCliView, CView)

BEGIN_MESSAGE_MAP(CMySupervisionCliView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMySupervisionCliView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_BTN_ZOOMIN, &CMySupervisionCliView::OnBnClickedZoomIn)
	ON_BN_CLICKED(IDC_BTN_ZOOMOUT, &CMySupervisionCliView::OnBnClickedZoomOut)
	ON_BN_CLICKED(IDC_BTN_PANLEFT, &CMySupervisionCliView::OnBnClickedPanleft)
	ON_BN_CLICKED(IDC_BTN_PANRIGHT, &CMySupervisionCliView::OnBnClickedPanright)
	ON_BN_CLICKED(IDC_BTN_ZOOMALL, &CMySupervisionCliView::OnBnClickedZoomall)
END_MESSAGE_MAP()

// CMySupervisionCliView 构造/析构

CMySupervisionCliView::CMySupervisionCliView() noexcept
{
	// TODO: 在此处添加构造代码

}

CMySupervisionCliView::~CMySupervisionCliView()
{
}

BOOL CMySupervisionCliView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	float t;
	int i;

	int ptSize;
	const float step = 0.015f; // 步长
	//bool bPolyBezier;
	//float nSScale = 1.25f; //屏幕缩放 ♻️🔄
	Point p;

	int n = (int)theApp.points.size() - 1;
	theApp.points1.assign(theApp.points.begin() + n - theApp.nLenPointsShow, theApp.points.end());

	ptSize = (int)theApp.points1.size();
	theApp.ptSize = ptSize;
	theApp.ptNum = (int)(1 / step) + 1; // (float)ptSize / step + 0.5f; //2024-3-26,实际应该是步长的倒数

	for (i = 0; i < ptSize; i++) { //生成X轴时间点
		theApp.points1[i].x = 20 + (float)i * 80;// *m_x_scale;
	}

	//计算Bezier曲线控制点
	for (t = 0, i = 0; t <= 1; t += step, i++) {
		p = theApp.bezier_curve(theApp.points1, t);
		theApp.pArr[i].x = (LONG)p.x;
		theApp.pArr[i].y = (LONG)p.y;

		theApp.pArrNAV[i].x = (LONG)p.x;
		theApp.pArrNAV[i].y = (LONG)((p.z - 1) * 10000);
	}

	m_x_pos = (ptSize - 15) > 0 ? -(ptSize - 15) * 80 : 0; //2024-5-22,最新净值位置
	
	//theApp.m_wndSider.DoModal();
	return CView::PreCreateWindow(cs);
}

// CMySupervisionCliView 绘图

void CMySupervisionCliView::OnDraw(CDC* pDC)
{
	//CMySupervisionCliDoc* pDoc = GetDocument();
	//ASSERT_VALID(pDoc);

	//int j;

	//if (!pDoc)
	//	return;

	// TODO: 在此处为本机数据添加绘制代码
	HDC hDC = pDC->GetSafeHdc();

	//CPen pen;
	//pen.CreatePen(PS_SOLID, 18, RGB(255, 0, 0));
	//CPen* oldPen = this->GetDC()->SelectObject(&pen);

	//HPEN hpen;
#ifdef _UNICODE
	LPCWSTR str = _T("QWERTYUIOP ASDFGHJKL ZXCVBNM ~!@#$%^&*()_+{}|:\"<>?\
qwertyuiop asdfghjkl zxcvbnm `1234567890-=[]\\;\',./");
	LPCWSTR str2 = _T("QWERTYUIOP ASDFGHJKL ZXCVBNM 1234567890");
#else //MBCS
	char* str =  "QWERTYUIOP ASDFGHJKL ZXCVBNM ~!@#$%^&*()_+{}|:\"<>?\
qwertyuiop asdfghjkl zxcvbnm `1234567890-=[]\\;\',./";
	char* str2 = "QWERTYUIOP ASDFGHJKL ZXCVBNM 1234567890";
	char* str3 = "https://www.dayfund.cn/ajs/ajaxdata.shtml?showtype=getfundvalue&fundcode=100032&t=";
#endif
	int w_font = 32, h_font = 16;
	
	//pen.DeleteObject();
	MoveToEx(hDC, 8, 8 + h_font + 43, NULL);
	
#ifdef _UNICODE
	LineTo(hDC, 8 + (int)wcslen(str) * 18, 8 + h_font + 43); //分割线
	TextOut(hDC, 8, 8, str, (int)wcslen(str));
#else //MBCS
	LineTo(hDC, 8 + (int)strlen(str) / 2 * 18, 8 + h_font + 43); //分割线
	
	TextOut(hDC, 8, 8, str3, (int)strlen(str3));

	TextOut(hDC, 132, 32, "* - 当日涨幅    = - 单位净值", (int)strlen("* - 当日涨幅    = - 单位净值"));

	HPEN hpenh;
	hpenh = CreatePen(PS_DOT, 1, RGB(212, 85, 26));
	DeleteObject(SelectObject(hDC, hpenh));
	CRect rect;
	GetClientRect(rect);
	MoveToEx(hDC, 0, DRAW_LINE_BASE + 208, NULL); //0线
	LineTo(hDC, rect.Width(), DRAW_LINE_BASE + 208);
	
	if (hpenh != NULL) DeleteObject(hpenh);

#endif
	//this->GetDC()->SelectObject(&pen);
	//this->GetDC()->SelectObject(oldPen);

	//🎀
	DrawTie(hDC, 100, 100, RGB(255, 215, 0)); //RGB(242, 139, 146)
	//🌹
	//DrawRose(hDC);

	HFONT hFontOriginal, hFont1, hFont2;
	hFont1 = CreateFont(
		36,
		0,
		0,
		0,
		FW_DONTCARE,
		FALSE,
		TRUE, //bUnderline
		FALSE,
		DEFAULT_CHARSET,
		OUT_OUTLINE_PRECIS,
		CLIP_DEFAULT_PRECIS,
		CLEARTYPE_QUALITY,
		VARIABLE_PITCH | FF_SWISS,
		TEXT("Impact"));

	hFont2 = CreateFont(
		16,
		0,
		300,
		0,
		FW_DONTCARE,
		FALSE,
		FALSE, //bUnderline
		FALSE,
		DEFAULT_CHARSET,
		OUT_OUTLINE_PRECIS,
		CLIP_DEFAULT_PRECIS,
		CLEARTYPE_QUALITY,
		VARIABLE_PITCH | FF_SWISS,
#ifdef _UNICODE
		TEXT("HarmonyOS Sans SC")
		//TEXT("HarmonyOS Sans SC Medium")
		//TEXT("IntelOne Mono")
		//TEXT("IntelOne Mono Bold")
		//TEXT("Monaspace Argon")
#else //MBCS
		"HarmonyOS Sans SC"
		//TEXT("HarmonyOS Sans SC Medium")
		//TEXT("IntelOne Mono")
		//TEXT("IntelOne Mono Bold")
		//TEXT("Monaspace Argon")
#endif
	);
	//str
	hFontOriginal = (HFONT)SelectObject(hDC, hFont1);
#ifdef _UNICODE
	TextOut(hDC, 8, 8 + h_font + 2, L"100032", 6);
#else //MBCS
	TextOut(hDC, 8, 8 + h_font + 2, "100032", 6);
#endif
	SelectObject(hDC, hFontOriginal);
	DeleteObject(hFont1);

	////str2
	//hFontOriginal = (HFONT)SelectObject(hDC, hFont2);
	//TextOut(hDC, 8, 50 + h_font + 2, str2, wcslen(str2));
	//SelectObject(hDC, hFontOriginal);
	//DeleteObject(hFont2);
	int j;
	for (j = 0; j < theApp.ptNum; j++) { //Bezier点阵 DRAW_LINE_BASE
		TextOut(hDC, (int)(theApp.pArr[j].x * m_x_scale) + 2 + m_x_pos, theApp.pArr[j].y, _T("*"), 1);
		SetTextColor(hDC, RGB(255, 165, 0));
		TextOut(hDC, (int)(theApp.pArrNAV[j].x * m_x_scale) + 2 + m_x_pos, 
			DRAW_LINE_BASE + 298 - theApp.pArrNAV[j].y * m_y_scale * 1.77f, _T("="), 1);
		TextOut(hDC, (int)(theApp.pArrNAV[j].x * m_x_scale) + 2 + m_x_pos,
			DRAW_LINE_BASE + 298 - theApp.pArrNAV[j].y * m_y_scale * 1.77f + 1, _T("="), 1);
		SetTextColor(hDC, 0x000000);
	}

	//百分比和时间文本角度倾斜
	hFontOriginal = (HFONT)SelectObject(hDC, hFont2);

	for (j = 0; j < theApp.ptSize; j++) { //成交百分比*100
		// 获取待转换的数据的长度
		int len_in;
		wchar_t* resultDate, * resultData;
		size_t convertedDate = 0, convertedData = 0;
		int nData = 20;
		char chData[16];
		//涨幅(净值)
		sprintf_s(chData, 16, "%2.2f%%(%.4f)", (DRAW_LINE_BASE - theApp.points1[j].y) / 100.0, theApp.points1[j].z);
		len_in = MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)theApp.points1[j].strDate.c_str(), -1, NULL, 0);
		resultDate = (wchar_t*)malloc(len_in * sizeof(wchar_t));
		mbstowcs_s(&convertedDate, (wchar_t*)resultDate, len_in, theApp.points1[j].strDate.c_str(), _TRUNCATE);

		//成交时间点标记
		SetTextColor(hDC, 0x0000FF);
#ifdef _UNICODE
		TextOut(hDC, (int)theApp.points1[j].x * m_x_scale - 4 + m_x_pos, DRAW_DATE_BASE, _T("·"), 1);
#else //MBCS
		TextOut(hDC, (int)(theApp.points1[j].x * m_x_scale) - 4 + m_x_pos, DRAW_DATE_BASE, _T("·"), 2);
#endif
		//成交日期
		SetTextColor(hDC, 0xD30080);
		if (resultDate != 0) { 
#ifdef _UNICODE
			TextOut(hDC, (int)theApp.points1[j].x * m_x_scale + 11 + m_x_pos, DRAW_DATE_BASE, resultDate, (int)convertedDate - 1);
#else //MBCS
			TextOut(hDC, (int)(theApp.points1[j].x * m_x_scale) + 11 + m_x_pos, DRAW_DATE_BASE, theApp.points1[j].strDate.c_str(), (int)strlen(theApp.points1[j].strDate.c_str()));
#endif
		}
		//成交涨幅百分比
		len_in = MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)chData, -1, NULL, 0);
		resultData = (wchar_t*)malloc(len_in * sizeof(wchar_t));
		mbstowcs_s(&convertedData, (wchar_t*)resultData, len_in, chData, _TRUNCATE);
		if (resultData != 0) {
			char buffer[16] = { 0 };
			size_t i;
			char* pMBBuffer = (char*)malloc(100);

			// Conver Unicode to Multibyte
			wcstombs_s(&i, pMBBuffer, (size_t)100, resultData, (size_t)100 - 1); // -1 so the appended NULL doesn't fall outside the allocated buffer
			
			if (pMBBuffer != 0 && pMBBuffer[0] == '-') { //跌
				SetTextColor(hDC, 0x0000FF00);
			}
			else { //涨
				SetTextColor(hDC, 0x000000FF);
			}
#ifdef _UNICODE
			TextOut(hDC, (int)theApp.points1[j].x * m_x_scale + 2 + m_x_pos, DRAW_DATE_BASE - 16, resultData, (int)convertedData - 1);
#else //_MBCS
			TextOut(hDC, (int)(theApp.points1[j].x * m_x_scale) + 2 + m_x_pos, DRAW_DATE_BASE - 16, chData, (int)strlen(chData));
#endif
			// Free multibyte character buffer
			if (pMBBuffer)
			{
				free(pMBBuffer);
			}
		}
	}
	SelectObject(hDC, hFontOriginal);
	DeleteObject(hFont2);

	//画交易时间点指向射线
	HPEN hpen;
	hpen = CreatePen(PS_INSIDEFRAME, 2, RGB(rand() % 256, rand() % 256, rand() % 256)); //PS_INSIDEFRAME
	for (j = 0; j < theApp.ptSize; j++) {
		hpen = CreatePen(PS_DASH, 1, RGB(rand() % 256, rand() % 256, rand() % 256));
		DeleteObject(SelectObject(hDC, hpen));
		MoveToEx(hDC, (int)(theApp.points1[j].x * m_x_scale) + 4 + m_x_pos, DRAW_DATE_BASE - 8, (LPPOINT)NULL);
		LineTo(hDC, (int)(theApp.points1[j].x * m_x_scale) + 4 + m_x_pos, (int)theApp.points1[j].y + 15);
		//Pie(hDC, (int)theApp.points1[j].x - 3, (int)theApp.points1[j].y + 15 - 4, (int)theApp.points1[j].x + 8 + 3, (int)theApp.points1[j].y + 25, \
		//	(int)theApp.points1[j].x + 8 + 3, (int)theApp.points1[j].y + 15 - 2, (int)theApp.points1[j].x - 3, (int)theApp.points1[j].y + 15 - 2);
		
		hpen = CreatePen(PS_INSIDEFRAME, 2, RGB(0xFF, 0x0, 0x0));
		DeleteObject(SelectObject(hDC, hpen));
		theApp.Marker(hDC, (LONG)(theApp.points1[j].x * m_x_scale) + 4 + m_x_pos, (LONG)theApp.points1[j].y);
		//TextOut(hDC, theApp.points1[j].x, theApp.points1[j].y, _T("X"), 1);
	}

	ReleaseDC(pDC);
	if (hpen != NULL) DeleteObject(hpen);
	ValidateRect(NULL);
}


// CMySupervisionCliView 打印


void CMySupervisionCliView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMySupervisionCliView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMySupervisionCliView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CMySupervisionCliView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CMySupervisionCliView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	//ClientToScreen(&point); //相对坐标转成屏幕坐标
	//OnContextMenu(this, point);
	CString str;
	str.Format("坐标: %d, %d\n是:     ^_^\n否:     总览\n取消: 最新", point.x, point.y);
	
	if (point.x > 55 && point.x < 145 && point.y > 75 && point.y < 125) { //点击🦋图标
		int nRet = MessageBox(str, "当前相对坐标", MB_ICONWARNING | MB_YESNOCANCEL);
		if (IDCANCEL == nRet) {
			m_x_pos = -(theApp.ptSize - 15) * 80; //2024-5-22,最新净值位置
			m_x_scale = 1.0;
			m_y_scale = 1.0;
			Invalidate();
		}
		else if (IDNO == nRet) {
			m_x_pos = 40;
			m_x_scale = 0.45f;
			m_y_scale = 0.45f;
			Invalidate();
		}
	}

}

void CMySupervisionCliView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMySupervisionCliView 诊断

#ifdef _DEBUG
void CMySupervisionCliView::AssertValid() const
{
	CView::AssertValid();
}

void CMySupervisionCliView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

//CMySupervisionCliDoc* CMySupervisionCliView::GetDocument() const // 非调试版本是内联的
//{
//	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMySupervisionCliDoc)));
//	return (CMySupervisionCliDoc*)m_pDocument;
//}
#endif //_DEBUG


// CMySupervisionCliView 消息处理程序


void CMySupervisionCliView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	
	CString str;
	CRect rect;

	GetWindowRect(rect);
	str.Format("w=%d,h=%d,left=%d,top=%d,width=%d", cx, cy, rect.left, rect.top,rect.Width());
	theApp.nCxView = cx;

	//CMainFrame* pApp = (CMainFrame*) AfxGetApp();
	//pApp->m_wndSider->MoveWindow(200, 200, 800, 600, TRUE);

	//MessageBox(str);
}


int CMySupervisionCliView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	// 创建按钮
	CRect rectDummy;
	//rectDummy.SetRectEmpty();
	GetClientRect(rectDummy);
	//rectDummy.right -= 120;
	
#define BTN_POS_X 1100
	if (!m_btn_zoomin.Create(_T("|<>|"), WS_CHILD | WS_VISIBLE | BS_FLAT,
		CRect(BTN_POS_X + 50, 15, BTN_POS_X + 50 + 35, 40), this, (UINT)IDC_BTN_ZOOMIN))
	{
		TRACE0("Failed to create button ZoomIn\n");
		return -1;
	}

	if (!m_btn_zoomall.Create(_T("|...|"), WS_CHILD | WS_VISIBLE | BS_FLAT,
		CRect(BTN_POS_X + 54, 42, BTN_POS_X + 50 + 30, 68), this, (UINT)IDC_BTN_ZOOMALL))
	{
		TRACE0("Failed to create button Zoomall\n");
		return -1;
	}

	if (!m_btn_zoomout.Create(_T(">||<"), WS_CHILD | WS_VISIBLE | BS_FLAT,
		CRect(BTN_POS_X + 50, 70, BTN_POS_X + 50 + 35, 95), this, (UINT)IDC_BTN_ZOOMOUT))
	{
		TRACE0("Failed to create button ZoomOut\n");
		return -1;
	}
	if (!m_btn_panleft.Create(_T("<<"), WS_CHILD | WS_VISIBLE | BS_FLAT, //» ←
			CRect(BTN_POS_X - 0, 42, BTN_POS_X - 0 + 35, 68), this, (UINT)IDC_BTN_PANLEFT))
	{
		TRACE0("Failed to create button PanLeft\n");
		return -1;
	}
	
	if (!m_btn_panright.Create(_T(">>"), WS_CHILD | WS_VISIBLE | BS_FLAT, //→
		CRect(BTN_POS_X + 50 + 35 + 15, 42, BTN_POS_X + 50 + 35 + 15 + 35, 68), this, (UINT)IDC_BTN_PANRIGHT))
	{
		TRACE0("Failed to create button PanRight\n");
		return -1;
	}
	/*
	if (!m_progress_showpoint.Create(WS_CHILD | WS_VISIBLE | BS_FLAT,
		CRect(BTN_POS_X + 50 + 35 + 15 + 50, 40, BTN_POS_X + 50 + 35 + 15 + 35 + 150, 70), this, 
		(UINT)IDC_BTN_PANRIGHT + 10))
	{
		TRACE0("Failed to create progress showpoint\n");
		return -1;
	}
	else {
		m_progress_showpoint.SetRange32(10, 33); //范围
		m_progress_showpoint.SetStep(1); //步长
		m_progress_showpoint.SetPos(30); //位置
	}

	if (!m_slider_showpoint.Create(WS_CHILD | WS_VISIBLE | BS_FLAT | TBS_ENABLESELRANGE,
		CRect(BTN_POS_X + 50 + 35 + 15 + 50, 80, BTN_POS_X + 50 + 35 + 15 + 35 + 150, 110), this, 
		(UINT)IDC_BTN_PANRIGHT + 20))
	{
		TRACE0("Failed to create slider showpoint\n");
		return -1;
	}
	else {
		m_slider_showpoint.SetRange(10, 33);
	}
	*/
	return 0;
}


void CMySupervisionCliView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CView::OnLButtonUp(nFlags, point);
}

void CMySupervisionCliView::OnBnClickedZoomIn()
{
	m_x_scale = m_x_scale > 8 ? m_x_scale : m_x_scale + 0.1f;
	m_y_scale = m_y_scale > 8 ? m_y_scale : m_y_scale + 0.1f;

	Invalidate();

	//CString strScale;
	//strScale.Format("In当前比例系数:%f", m_x_scale);
	//MessageBox(strScale);
}

void CMySupervisionCliView::OnBnClickedZoomOut()
{
	m_x_scale = m_x_scale < 0.11f ? 0.09f : m_x_scale - 0.1f;
	m_y_scale = m_y_scale < 0.11f ? 0.09f : m_y_scale - 0.1f;
	Invalidate();

	//CString strScale;
	//strScale.Format("Out当前比例系数:%f", m_x_scale);
	//MessageBox(strScale);
}

void CMySupervisionCliView::OnBnClickedZoomall()
{
	m_x_pos = 40;
	m_x_scale = 0.45f;
	m_y_scale = 0.45f;
	Invalidate();
}


//画线
void CMySupervisionCliView::DrawLine(HDC hDC, int x1, int y1, int x2, int y2)
{
	MoveToEx(hDC, x1, y1, NULL);
	LineTo(hDC, x2, y2);
}

// 画蝴蝶结
struct vec
{
	double x;
	double y;
	double z;
};
vec operator*(vec v, double n)
{
	return { v.x * n , v.y * n , v.z * n };
}
vec operator+(vec& x, vec& y)
{
	return { x.x + y.x, x.y + y.y, x.z + y.z };
}
//参数
double a = 11;
double b = 27;
double c = 2;

vec velocity(vec & pos)
{
	vec velocity;
	velocity.x = a * (pos.y - pos.x);
	velocity.y = pos.x * (b - pos.z) - pos.y;
	velocity.z = pos.x * pos.y - c * pos.z;
		
	return velocity;
}
//时间微元
double dt = 0.001;
/////////////////
#define Y 1080
#define X 1920

// c is defined as the angle between each
// iterative lines, changing this would result
// in different and interesting patterns.
//#define cc 5 * M_PI / 7

// colorVal is used to provide different colors
// for each iterating point/line in the cycle.
int colorVal = 0;

// The core function in the program which is
// recursive in nature and terminates when the
// line size is less than 0.1 pixels.
/*int Pyt_Tree(float x, float y, float r, float ang)
{
	
	// Max iteration condition so as to increase
	// the accuracy of the fractal pattern.
	// The closer it is to zero the higher the
	// details but would cost more processing time.
	if (r < 0.1) {

		// combination of type casting and iteration
		// so as to provide a Greatest Integer Function
		// sort of manipulation for the color input.
		setcolor((colorVal++ % 15000) / 1000 + 1);

		// Conversion of the parametric coordinates
		// of the points to the Argand coordinates
		// while displaying them.
		line(x, y, x - r * sin(ang), y - r * cos(ang));

		return 0;
	}

	float r_n;

	if (c > M_PI / 4) {
		r_n = sin(c);
	}
	else {
		r_n = cos(c);
	}

	// Recursive calling of the Pyt_Tree() function
	// to get towards the end of the branch of the
	// fractal tree.
	Pyt_Tree(x - r * sin(ang), y - r * cos(ang),
		r / (2 * r_n), (ang + c));
	Pyt_Tree(x - r * sin(ang), y - r * cos(ang),
		r / (2 * r_n), (ang - c));
	
	return 0;
}*/
int CMySupervisionCliView::Pyt_Tree(HDC hDC, float x, float y, float r, float ang)
{
#define M_PI       3.14159265358979323846   // pi
#define cc 5 * M_PI / 7.0f
	// Max iteration condition so as to increase
	// the accuracy of the fractal pattern.
	// The closer it is to zero the higher the
	// details but would cost more processing time.
	if (r < 1) {
		HPEN h;
		BYTE rr, gg, bb;

		rr = (((colorVal++ % 15000) / 1000 + 1) & 0xFFFFFF) >> 16;
		gg = (((colorVal++ % 15000) / 1000 + 1) & 0x00FF00) >> 8;
		bb = ((colorVal++ % 15000) / 1000 + 1) & 0x0000FF;

		h = CreatePen(PS_SOLID, 2, RGB(rand() % 256, rand() % 256, rand() % 256));
		SelectObject(hDC, h);
		// combination of type casting and iteration
		// so as to provide a Greatest Integer Function
		// sort of manipulation for the color input.
		//setcolor((colorVal++ % 15000) / 1000 + 1);

		// Conversion of the parametric coordinates
		// of the points to the Argand coordinates
		// while displaying them.
		//line(x, y, x - r * sin(ang), y - r * cos(ang));
		//DrawLine(hDC, x, y, x - r * sin(ang), y - r * cos(ang));
		MoveToEx(hDC, (int)x, (int)y, NULL);
		LineTo(hDC, (int)(x - r * sin(ang)), (int)(y - r * cos(ang)));

		DeleteObject(h);
		return 0;
	}

	float r_n;

	//if (cc > M_PI / 4) {
		r_n = (float)sin((double)cc);
	//}
	//else {
	//	r_n = cos(cc);
	//}

	// Recursive calling of the Pyt_Tree() function
	// to get towards the end of the branch of the
	// fractal tree.
	Pyt_Tree(hDC, x - (float)(r * sin(ang)), y - (float)(r * cos(ang)),
		r / (2 * r_n), (float)(ang + cc));
	Pyt_Tree(hDC, x - (float)(r * sin(ang)), y - (float)(r * cos(ang)),
		r / (2 * r_n), (float)(ang - cc));

	return 0;
}

void CMySupervisionCliView::butterfly(HDC hDC, int x, int y, int r)
{
	if (r < 5)
		return;

	HPEN h;
	h = CreatePen(PS_SOLID, 2, RGB(rand() % 256, rand() % 256, rand() % 256));
	SelectObject(hDC, h);

	int x1 = x - (int)(r * cos(30 * 3.1415 / 180));
	int y1 = y + (int)(r * sin(30 * 3.1415 / 180));
	int x2 = x;
	int y2 = y - r;
	int x3 = x + (int)(r * cos(30 * 3.1415 / 180));
	int y3 = y + (int)(r * sin(30 * 3.1415 / 180));

	DrawLine(hDC, x1, y1, x2, y2);
	DrawLine(hDC, x2, y2, x3, y3);

	butterfly(hDC, x1, y1, (int)(r / 2));
	butterfly(hDC, x2 - (int)(r * cos(60 * 3.1415 / 180)), y2 - (int)(r * sin(60 * 3.1415 / 180)), (int)(r / 2));
	butterfly(hDC, x3, y3, (int)(r / 2));

	DeleteObject(h);
}
void CMySupervisionCliView::fractal(HDC hDC, float left, float top, float xside, float yside, COLORREF c) {
#define MAXCOUNT 30
	float xscale, yscale, zx, zy, cx, tempx, cy;
	int x, y;
	int maxx, maxy, count;

	// getting maximum value of x-axis of screen
	maxx = 200; // getmaxx();

	// getting maximum value of y-axis of screen
	maxy = 200; // getmaxy();

	// setting up the xscale and yscale
	xscale = xside / maxx;
	yscale = yside / maxy;

	// calling rectangle function
	// where required image will be seen
	//rectangle(0, 0, maxx, maxy);

	// scanning every point in that rectangular area.
	// Each point represents a Complex number (x + yi).
	// Iterate that complex number
	HPEN h;
	h = CreatePen(PS_SOLID, 2, c);
	SelectObject(hDC, h);

	for (y = 1; y <= maxy - 1; y++) {
		for (x = 1; x <= maxx - 1; x++)
		{
			// c_real
			cx = x * xscale + left;

			// c_imaginary
			cy = y * yscale + top;

			// z_real
			zx = 0;

			// z_imaginary
			zy = 0;
			count = 0;

			// Calculate whether c(c_real + c_imaginary) belongs
			// to the Mandelbrot set or not and draw a pixel
			// at coordinates (x, y) accordingly
			// If you reach the Maximum number of iterations
			// and If the distance from the origin is
			// greater than 2 exit the loop
			while ((zx * zx + zy * zy < 4) && (count < MAXCOUNT))
			{
				// Calculate Mandelbrot function
				// z = z*z + c where z is a complex number

				// tempx = z_real*_real - z_imaginary*z_imaginary + c_real
				tempx = zx * zx - zy * zy + cx;

				// 2*z_real*z_imaginary + c_imaginary
				zy = 2 * zx * zy + cy;

				// Updating z_real = tempx
				zx = tempx;

				// Increment count
				count = count + 1;
			}

			// To display the created fractal
			//putpixel(x, y, count);
			SetPixel(hDC, x + 50, y - 20, c);
		}
	}
	DeleteObject(h);
}
void CMySupervisionCliView::DrawTie(HDC hDC, int x, int y, COLORREF c)
{
	//Pyt_Tree(hDC, x, y, y, c);
	//butterfly(hDC, x, y, 50);
	//float left, top, xside, yside;
	//left = 10; // -1.75;
	//top = 10; // -0.25;
	//xside = 0.25;
	//yside = 0.45;

	//fractal(hDC, left, top, xside, yside, c);

	
	int x1, yl, x2, y2; 
	const int d = 25;// 50;
	double a, e;
	HPEN h;
	h = CreatePen(PS_SOLID, 2, c);
	SelectObject(hDC, h);
	for (a = 0; a < 2 * PI; a += PI / 360) {
		e = d * (1 + sin(a * 4));
		x1 = (int)(x + e * cos(a)); 
		yl = (int)(y + e * sin(a) / 2);
		x2 = (int)(x + e * cos(a + PI / 9));
		y2 = (int)(y + e * sin(a + PI / 9) / 4.5);
		DrawLine(hDC, x1, yl, x2, y2);
		//SetPixel(hDC, x1, yl, c);
		//SetPixel(hDC, x2, y2, c);
	}
	DeleteObject(h);
	
}

BOOL CMySupervisionCliView::DrawRoseCalc(double a, double b, double c, DOT& d)
{
	double j, n, o, w, z;

	if (c > 60)
	{
		// 花柄
		d.x = sin(a * 7) * (13 + 5 / (0.2 + pow(b * 4, 4))) - sin(b) * 50;
		d.y = b * rosesize + 50;
		d.z = 625 + cos(a * 7) * (13 + 5 / (0.2 + pow(b * 4, 4))) + b * 400;
		d.r = a * 1 - b / 2;
		d.g = a;
		return true;
	}
	double A = a * 2 - 1;
	double B = b * 2 - 1;
	if (A * A + B * B < 1)
	{
		//绿叶
		if (c > 37) {
			j = (int(c) & 1);
			n = j ? 6 : 4;
			o = 0.5 / (a + 0.01) + cos(b * 125) * 3 - a * 300;
			w = b * h;
			d.x = o * cos(n) + w * sin(n) + j * 610 - 390;
			d.y = o * sin(n) - w * cos(n) + 550 - j * 350;
			d.z = 1180 + cos(B + A) * 99 - j * 300;
			d.r = 0.4 - a * 0.1 + pow(1 - B * B, -h * 6) * 0.15 - a * b * 0.4 + cos(a + b) / 5 +
				pow(cos((o * (a + 1) + (B > 0 ? w : -w)) / 25), 30) * 0.1 * (1 - B * B);
			d.g = o / 1000 + 0.7 - o * w * 0.000003;
			return true;
		}

		if (c > 32)
		{
			// 花萼
			c = c * 1.16 - 0.15;
			o = a * 45 - 20;
			w = b * b * h;
			z = o * sin(c) + w * cos(c) + 620;
			d.x = o * cos(c) - w * sin(c);
			d.y = 28 + cos(B * 0.5) * 99 - b * b * b * 60 - z / 2 - h;
			d.z = z;
			d.r = (b * b * 0.3 + pow((1 - (A * A)), 7) * 0.15 + 0.3) * b;
			d.g = b * 0.7;
			return true;
		}
		// 花朵
		o = A * (2 - b) * (80 - c * 2);
		w = 99 - cos(A) * 120 - cos(b) * (-h - c * 4.9) + cos(pow(1 - b, 7)) * 50 + c * 2;
		z = o * sin(c) + w * cos(c) + 700;
		d.x = o * cos(c) - w * sin(c);
		d.y = B * 99 - cos(pow(b, 7)) * 50 - c / 3 - z / 1.35 + 450;
		d.z = z;
		d.r = (1 - b / 1.2) * 0.9 + a * 0.1;
		d.g = pow((1 - b), 20) / 4 + 0.05;
		return true;
	}

	return false;
}

void CMySupervisionCliView::DrawRose(HDC hDC)
{
	short* zBuffer;
	int x, y, z, zBufferIndex;
	DOT dot;

	zBuffer = new short[rosesize * rosesize];
	memset(zBuffer, 0, sizeof(short) * rosesize * rosesize);

	for (int j = 0; j < 2000; j++) //2000
	{
		for (int i = 0; i < 10000; i++) //10000
		{
			if (DrawRoseCalc(double(rand()) / RAND_MAX, double(rand()) / RAND_MAX, rand() % 46 / 0.74, dot))
			{
				z = int(dot.z + 0.5);
				x = int(dot.x * rosesize / z - h + 0.5);
				y = int(dot.y * rosesize / z - h + 0.5);
				if (y > rosesize) continue;
				zBufferIndex = y * rosesize + x;
				if (!zBuffer[zBufferIndex] || zBuffer[zBufferIndex] > z)
				{
					zBuffer[zBufferIndex] = z;
					// 画点
					int r = ~int((dot.r * h));

					if (r < 0) r = 0;

					if (r > 255) r = 255;

					int g = ~int((dot.g * h));
					if (g < 0) g = 0;
					if (g > 255) g = 255;

					int b = ~int((dot.r * dot.r * -80));
					if (b < 0) b = 0;

					if (b > 255) b = 255;

					SetPixel(hDC, x + 50, y - 20, RGB(r, g, b));
				}
			}
		}
		//Sleep(100);
	}
	delete[] zBuffer;
}

void CMySupervisionCliView::OnBnClickedPanleft()
{
	m_x_pos += 40;
	Invalidate();

	//CString strPos;
	//strPos.Format("Left当前位置:%f", m_x_scale);
	//MessageBox(strPos);
}


void CMySupervisionCliView::OnBnClickedPanright()
{
	m_x_pos -= 40;

	Invalidate();

	//CString strPos;
	//strPos.Format("Right当前位置:%f", m_x_scale);
	//MessageBox(strPos);
}
