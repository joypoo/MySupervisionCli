
// MySupervisionCli.h: MySupervisionCli 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含 'pch.h' 以生成 PCH"
#endif

#include "resource.h"       // 主符号

#include <string>
#include <vector>

using namespace std;
// CMySupervisionCliApp:
// 有关此类的实现，请参阅 MySupervisionCli.cpp
//

#define DRAW_LINE_BASE 280
#define DRAW_DATE_BASE 540

struct Point {
	float x, y, z;
	string strDate;
	Point(float x = 0, float y = 0, float z = 0, string strDate = "") :x(x), y(y), z(z), strDate(strDate) {}
};

class CMySupervisionCliApp : public CWinAppEx
{
public:
	CMySupervisionCliApp() noexcept;
private:
	int binomial(int n, int i); //计算组合数
public:
	vector<Point> points1;
	vector<Point> points = { //顺序号，涨幅，净值，时间
		{ 100, DRAW_LINE_BASE - (121),  1.0020f, "2024-02-29" }, //2.29 IN
		{ 100, DRAW_LINE_BASE - (10),   1.0030f, "2024-03-01" }, //3.1,-0.10%
		{ 200, DRAW_LINE_BASE - (50),   1.0080f, "2024-03-04" }, //3.4
		{ 200, DRAW_LINE_BASE - (40),   1.0f, "2024-03-05" }, //3.5
		{ 200, DRAW_LINE_BASE - (10),   1.0f, "2024-03-06" }, //3.6
		{ 200, DRAW_LINE_BASE - (40),   1.0f, "2024-03-07" }, //3.7
		{ 200, DRAW_LINE_BASE - (60),   1.0f, "2024-03-08" }, //3.8
		{ 200, DRAW_LINE_BASE - (-80),  1.0f, "2024-03-11" }, //3.11
		{ 200, DRAW_LINE_BASE - (-190), 1.0f, "2024-03-12" }, //3.12,
		{ 200, DRAW_LINE_BASE - (-20),  1.0f, "2024-03-13" }, //3.13
		{ 200, DRAW_LINE_BASE - (20),   1.0f, "2024-03-14" }, //3.14
		{ 200, DRAW_LINE_BASE - (22),   1.0f, "2024-03-15" },
		{ 200, DRAW_LINE_BASE - (-6),   1.0f, "2024-03-18" },
		{ 200, DRAW_LINE_BASE - (20),   1.0f, "2024-03-20" },
		{ 200, DRAW_LINE_BASE - (31),   1.0f, "2024-03-21" },
		{ 200, DRAW_LINE_BASE - (-30),  1.0f, "2024-03-22" },
		{ 200, DRAW_LINE_BASE - (34),   1.0f, "2024-03-25" },
		{ 200, DRAW_LINE_BASE - (2),	1.0f, "2024-03-26" },
		{ 200, DRAW_LINE_BASE - (-25),  1.0f, "2024-03-27" },
		{ 200, DRAW_LINE_BASE - (15),	1.0f, "2024-03-28" },
		{ 200, DRAW_LINE_BASE - (97),	1.0f, "03-29-2024" },
		{ 200, DRAW_LINE_BASE - (50),	1.0f, "04-01-2024" },
		{ 200, DRAW_LINE_BASE - (30),	1.0f, "04-02-2024" },
		{ 200, DRAW_LINE_BASE - (89),	1.0f, "04-03-2024" },
		{ 200, DRAW_LINE_BASE - (-10),	1.0f, "04-08-2024" },
		{ 200, DRAW_LINE_BASE - (-30),	1.0f, "04-09-2024" },
		{ 200, DRAW_LINE_BASE - (20),	1.0f, "04-10-2024" },
		{ 200, DRAW_LINE_BASE - (90),	1.0f, "04-11-2024" },
		{ 200, DRAW_LINE_BASE - (-20),	1.0f, "04-12-2024" },
		{ 200, DRAW_LINE_BASE - (185),	1.0400f, "04-15-2024" },
		{ 200, DRAW_LINE_BASE - (-42),	1.0361f, "04-16-2024" },
		{ 200, DRAW_LINE_BASE - (-154),	1.0361f, "04-17-2024" },
		{ 200, DRAW_LINE_BASE - (30),	1.0590f, "04-18-2024" },
		{ 200, DRAW_LINE_BASE - (16),	1.0560f, "04-19-2024" },
		{ 200, DRAW_LINE_BASE - (-144),	1.0446f, "04-22-2024" },
		{ 200, DRAW_LINE_BASE - (-146),	1.0254f, "04-23-2024" },
		{ 200, DRAW_LINE_BASE - (32),	1.0252f, "04-24-2024" },
		{ 200, DRAW_LINE_BASE - (30),	1.0280f, "04-25-2024" },
		{ 200, DRAW_LINE_BASE - (-24),	1.0256f, "04-26-2024" },
		{ 200, DRAW_LINE_BASE - (3),	1.0280f, "04-29-2024" },
		{ 200, DRAW_LINE_BASE - (-10),	1.0340f, "05-07-2024" },
		{ 200, DRAW_LINE_BASE - (-46),	1.0294f, "05-08-2024" },
		{ 200, DRAW_LINE_BASE - (57),	1.0397f, "05-09-2024" },
		{ 200, DRAW_LINE_BASE - (51),	1.0340f, "05-10-2024" },
		{ 200, DRAW_LINE_BASE - (20),	1.0490f, "05-13-2024" },
		{ 200, DRAW_LINE_BASE - (-20),	1.0470f, "05-14-2024" },
		{ 200, DRAW_LINE_BASE - (-40),	1.0430f, "05-15-2024" },
		{ 200, DRAW_LINE_BASE - (30),	1.0460f, "05-16-2024" },
		{ 200, DRAW_LINE_BASE - (80),	1.0510f, "05-17-2024" },
		{ 200, DRAW_LINE_BASE - (57),	1.0570f, "05-20-2024" },
		{ 200, DRAW_LINE_BASE - (28),	1.0600f, "05-21-2024" },
		{ 200, DRAW_LINE_BASE - (9),	1.0610f, "05-22-2024" },
		{ 200, DRAW_LINE_BASE - (-132),	1.0470f, "05-23-2024" },
		{ 200, DRAW_LINE_BASE - (-57),	1.0410f, "05-24-2024" },
		{ 200, DRAW_LINE_BASE - (134),	1.0610f, "05-27-2024" },
		{ 200, DRAW_LINE_BASE - (-60),	1.0550f, "05-28-2024" },
		{ 200, DRAW_LINE_BASE - (19),	1.0570f, "05-29-2024" },
		{ 200, DRAW_LINE_BASE - (-76),	1.0490f, "05-30-2024" },
		{ 200, DRAW_LINE_BASE - (7),	1.0498f, "05-31-2024" },
	}; // 贝塞尔曲线控制点，给定控制点的数量决定贝塞尔曲线的阶数

	int nLenPointsShow = 30; //要显示的最近的点个数(不能大于33，因为步长为0.015)

	Point bezier_curve(const vector<Point>& points, float t);// 计算n次贝塞尔曲线上的点
	POINT pArr[1024];	//去除有用的趋势图数据
	int ptSize, ptNum;			//n次贝塞尔曲线上的点的个数
	void CMySupervisionCliApp::Marker(HDC hDC, LONG x, LONG y);

	int nCxView, nCyView; //视图区的位置
	//CSiderDlg	*m_wndSider;
// 重写
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 实现
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMySupervisionCliApp theApp;
