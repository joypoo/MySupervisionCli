#ifndef _colorstatic_h_
#define _colorstatic_h_
/////////////////////////////////////////////////////////////////////////////
// CColorStatic window

class CColorStatic : public CButton //CStatic //
{
// Construction
public:
	CColorStatic();
	virtual ~CColorStatic();
																															
	BOOL	Attach(CWnd* pParent, UINT nID, CFont* font = NULL, COLORREF textcolor = RGB(0, 0, 0), COLORREF backgroundcolor = GetSysColor(COLOR_3DFACE));

	void SetText(CString text = "");
	void SetBkColor(COLORREF color = ::GetSysColor(COLOR_3DFACE));
	void SetTextColor(COLORREF color = ::GetSysColor(COLOR_WINDOWTEXT));
	void SetImage(char* strPathImage);
	
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	void DrawButtonColor(CDC* pDC);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CColorStatic)
	//}}AFX_VIRTUAL

	// Generated message map functions
protected:
	//{{AFX_MSG(CColorStatic)
	//}}AFX_MSG

	HBRUSH CColorStatic::CtlColor(CDC* pDC, UINT nCtlColor);

	CFont*		m_Font;
	COLORREF	m_BackgroundColor;
	COLORREF	m_TextColor;
	CBrush		m_brBackgroundBrush;

	CRect       m_ButRect;          //°´Å¥³ß´ç
	CString     m_strText;          //°´Å¥ÎÄ×Ö
	char* image;
	HBITMAP m_hBitmap;

	DECLARE_MESSAGE_MAP()
private:

};

/////////////////////////////////////////////////////////////////////////////

#endif
