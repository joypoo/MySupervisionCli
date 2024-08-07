//---------------------------------------------------------------------------------------
//		ColorStatic.cpp
//
//		Contents:
//			A costum made control to display colorred text
//
//		Environment:
//			Microsoft Windows NT 4.0, Visual C++ 5.0
//
//		Revision 
//#include "stdafx.h"
#include "pch.h"
#include "ColorStatic.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//
// default contructor
//
CColorStatic::CColorStatic()
{
	m_Font = NULL;
	m_BackgroundColor = RGB(255, 255, 255);	// white color
	m_TextColor = RGB(0, 0, 0);				// black text
	m_brBackgroundBrush.CreateSolidBrush(m_BackgroundColor);
	image = NULL;
}

//
// contructor for dialog based static controls
//
BOOL CColorStatic::Attach(CWnd* pParent, UINT nID, CFont* font, COLORREF textcolor, COLORREF backgroundcolor)
{
	if (!SubclassDlgItem(nID, pParent))
		return FALSE;

	m_Font = font;
	m_BackgroundColor = backgroundcolor;	
	m_TextColor = textcolor;

	m_brBackgroundBrush.DeleteObject();
	m_brBackgroundBrush.CreateSolidBrush(m_BackgroundColor);

	if (m_Font)
		SetFont(m_Font);

	return TRUE;
}

//
// Destructor
//
CColorStatic::~CColorStatic()
{
	m_brBackgroundBrush.DeleteObject();
	delete [] image;
}


BEGIN_MESSAGE_MAP(CColorStatic, CStatic)
	//{{AFX_MSG_MAP(CColorStatic)
	ON_WM_CTLCOLOR_REFLECT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//
// Change the text
//
void CColorStatic::SetText(CString text)
{
	SetWindowText(text);
}

//
// Set the background color of the static control
//
void CColorStatic::SetBkColor(COLORREF color)
{
	m_brBackgroundBrush.DeleteObject();
	m_brBackgroundBrush.CreateSolidBrush(color);
	m_BackgroundColor = color;
	Invalidate();
}

//
// Set the color of the text
//
void CColorStatic::SetTextColor(COLORREF color)
{
	m_TextColor = color;
	Invalidate();
}
   
//
// Respond to the WM_CTLCOLOR message which is called when the control need
// to be painted
//
HBRUSH CColorStatic::CtlColor(CDC* pDC, UINT nCtlColor) 
{
	pDC->SetTextColor(m_TextColor);
	pDC->SetBkColor(m_BackgroundColor);
	return (HBRUSH) m_brBackgroundBrush;
}

void CColorStatic::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// TODO: Add your code to draw the specified item
	UINT uStyle = DFCS_BUTTONPUSH;

	// This code only works with buttons.
	ASSERT(lpDrawItemStruct->CtlType == ODT_BUTTON);

	// If drawing selected, add the pushed style to DrawFrameControl.
	if (lpDrawItemStruct->itemState & ODS_SELECTED)
		uStyle |= DFCS_PUSHED;

	// Draw the button frame.
	::DrawFrameControl(lpDrawItemStruct->hDC, &lpDrawItemStruct->rcItem,
		DFC_BUTTON, uStyle);
	// Get the button's text.
	CString strText;
	GetWindowText(strText);

	// Draw the button text using the text color red.
	COLORREF crOldColor = ::SetTextColor(lpDrawItemStruct->hDC, m_TextColor);
	::DrawText(lpDrawItemStruct->hDC, strText, strText.GetLength(),
		&lpDrawItemStruct->rcItem, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
	::SetTextColor(lpDrawItemStruct->hDC, crOldColor);

	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	m_ButRect = lpDrawItemStruct->rcItem;    //获取按钮尺寸
	ASSERT_VALID(pDC);
	if (m_strText.IsEmpty())
	{
		GetWindowText(m_strText);          //获取按钮文本
	}

	int nSavedDC = pDC->SaveDC();
	VERIFY(pDC);
	DrawButtonColor(pDC);
	pDC->RestoreDC(nSavedDC);
}

void CColorStatic::DrawButtonColor(CDC* pDC)
{
	CPen Pen;
	//COLORREF bColor;
	//bColor = RGB(255, 0, 0);

	//绘制按钮背景
	CBrush Brush;
	Brush.CreateSolidBrush(m_BackgroundColor);    //背景刷
	pDC->SelectObject(&Brush);

	Pen.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));	//外框颜色
	pDC->SelectObject(&Pen);
	pDC->RoundRect(&m_ButRect, CPoint(0, 0));    //画外框矩形圆角

	//绘制按钮文字
	pDC->SetTextColor(m_TextColor);         //画文字
	pDC->SetBkMode(TRANSPARENT);
	pDC->DrawText(m_strText, &m_ButRect, DT_SINGLELINE | DT_CENTER | DT_VCENTER | DT_END_ELLIPSIS);

	if (GetFocus() == this)
	{
		CRect Rect;
		Rect.SetRect(m_ButRect.left + 3, m_ButRect.top + 2, m_ButRect.right - 3, m_ButRect.bottom - 2);
		pDC->DrawFocusRect(&Rect);     //画拥有焦点的虚线框
	}
}

void CColorStatic::SetImage(char* strPathImage)
{
	delete[] image;
	image = new char[strlen(strPathImage) + 1];
	::strcpy_s(image, sizeof(strPathImage)*16, strPathImage);
	m_hBitmap = (HBITMAP)::LoadImage(NULL, _T(image), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	this->Invalidate();
}