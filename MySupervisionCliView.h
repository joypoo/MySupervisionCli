
// MySupervisionCliView.h: CMySupervisionCliView 类的接口
//

#pragma once

//定义全局变量

//定义结构体
struct DOT {
	double x;
	double y;
	double z;
	double r;
	double g;
};

class CMySupervisionCliView : public CView
{
protected: // 仅从序列化创建
	CMySupervisionCliView() noexcept;
	DECLARE_DYNCREATE(CMySupervisionCliView)

// 特性
public:
	//CMySupervisionCliDoc* GetDocument() const;

// 操作
public:
	int rosesize = 500;
	int h = -250;
	BOOL DrawRoseCalc(double a, double b, double c, DOT& d);
	void DrawRose(HDC hDC);
	void DrawLine(HDC hDC, int x1, int y1, int x2, int y2);
	void DrawTie(HDC hDC, int x, int y, COLORREF c);
	int Pyt_Tree(HDC hDC, float x, float y, float r, float ang);
	void butterfly(HDC hDC, int x, int y, int r);
	// Function to draw mandelbrot set
	void fractal(HDC hDC, float left, float top, float xside, float yside, COLORREF c);

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CMySupervisionCliView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CButton m_btn_zoomin;
	CButton m_btn_zoomall;
	CButton m_btn_zoomout;
	CButton m_btn_panleft;
	CButton m_btn_panright;

	CProgressCtrl m_progress_showpoint; //展示的点的个数
	CSliderCtrl m_slider_showpoint; //修改展示点数滑块

	float m_x_scale = 1.0; //x轴比例
	float m_y_scale = 1.0; //y轴比例
	int m_x_pos = 0; //x轴滚动偏移量
	// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedZoomIn();
	afx_msg void OnBnClickedZoomOut();
	afx_msg void OnBnClickedPanleft();
	afx_msg void OnBnClickedPanright();
	afx_msg void OnBnClickedZoomall();
};

#ifndef _DEBUG  // MySupervisionCliView.cpp 中的调试版本
//inline CMySupervisionCliDoc* CMySupervisionCliView::GetDocument() const
//   { return reinterpret_cast<CMySupervisionCliDoc*>(m_pDocument); }
#endif

