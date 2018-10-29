// DLEdit.cpp : 实现文件
//

// RoundBtn.cpp : implementation file
//

#include "stdafx.h"
#include "RoundBtn.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// RoundBtn dialog

void RoundBtn::PreSubclassWindow()
{
	ModifyStyle(0, BS_OWNERDRAW);
	is_pressed = false;
	CButton::PreSubclassWindow();
}

void RoundBtn::DrawItem(LPDRAWITEMSTRUCT lp)
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
		CPen pen(PS_SOLID, 2, RGB(0,0,0));
		dc.SelectObject(&pen);
		CBrush *pBrush=new CBrush(RGB(255,255,255));
		dc.SelectObject(pBrush);
		dc.RoundRect(0, 0, rc.Width(), rc.Height(), rc.Height()/2, rc.Height()/2);
		dc.SetTextColor(RGB(0, 0, 0));
	}
	else
	{
		CPen pen(PS_SOLID, 2, RGB(0,0,0));
		dc.SelectObject(&pen);
		CBrush *pBrush=new CBrush(RGB(0,191,255));
		dc.SelectObject(pBrush);
		dc.RoundRect(0, 0, rc.Width(), rc.Height(), rc.Height()/2, rc.Height()/2);
		dc.SetTextColor(RGB(0, 0, 0));
		CWnd * parent = this->GetParent();
		if(parent)
		{
			rc.InflateRect(4,4);
			rc.OffsetRect(2,2);
			parent->ScreenToClient(&rc);
			parent->InvalidateRect(&rc);
			InvalidateRect(&rc);
		}
	}
	CString str;
	GetWindowText(str);
	dc.DrawText(str, CRect(0, 0, rc.right, rc.bottom), DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	dc.DeleteDC();
}

BEGIN_MESSAGE_MAP(RoundBtn, CButton)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


void RoundBtn::OnLButtonDown(UINT nFlags, CPoint point)
{
	is_pressed = true;
	CButton::OnLButtonDown(nFlags, point);
}

void RoundBtn::OnLButtonUp(UINT nFlags, CPoint point)
{
	is_pressed = false;
	CButton::OnLButtonUp(nFlags, point);
}

BOOL RoundBtn::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;  //不擦除背景  
}
