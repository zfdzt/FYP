// RoundButton.cpp : implementation file
//

#include "stdafx.h"
#include "test1.h"
#include "RoundButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// RoundButton dialog

void RoundButton::PreSubclassWindow()
{
	ModifyStyle(0, BS_OWNERDRAW);
	is_pressed = false;
	CButton::PreSubclassWindow();
}

void RoundButton::DrawItem(LPDRAWITEMSTRUCT lp)
{
	CRect rc = lp->rcItem;
	CDC dc;
	dc.Attach(lp->hDC);
	dc.SetBkMode(TRANSPARENT);
	CBrush br;
	br.CreateStockObject(NULL_BRUSH);
	dc.SelectObject(&br);
	if (is_pressed)
	{
		CPen pen(PS_SOLID, 2, RGB(112, 128, 105));
		dc.SelectObject(&pen);
		dc.Ellipse(0, 0, rc.Width(), rc.Height());
		dc.SetTextColor(RGB(255, 0, 0));
	}
	else
	{
		CPen pen(PS_SOLID, 2, RGB(112, 128, 105));
		dc.SelectObject(&pen);
		dc.Ellipse(0, 0, rc.Width(), rc.Height());
		dc.SetTextColor(RGB(0, 255, 0));
	}
	CString str;
	GetWindowText(str);
	dc.DrawText(str, CRect(0, 0, rc.right, rc.bottom), DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	dc.DeleteDC();
}

BEGIN_MESSAGE_MAP(RoundButton, CButton)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


void RoundButton::OnLButtonDown(UINT nFlags, CPoint point)
{
	is_pressed = true;
	CButton::OnLButtonDown(nFlags, point);
}

void RoundButton::OnLButtonUp(UINT nFlags, CPoint point)
{
	is_pressed = false;
	CButton::OnLButtonUp(nFlags, point);
}

BOOL RoundButton::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;  //����������  
}
