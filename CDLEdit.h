#if !defined(AFX_RoundBtn_H__4FC14028_77FA_4D14_B975_D1858BF5EFAA__INCLUDED_)
#define AFX_RoundBtn_H__4FC14028_77FA_4D14_B975_D1858BF5EFAA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RoundBtn.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// RoundBtn dialog
class RoundBtn : public CButton
{
private:
	bool is_pressed;  //����Ƿ���  
public:
	virtual void PreSubclassWindow();  //�޸��Ի�����  
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);  //���� Բ�ΰ�ť  
public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);  //��갴��  
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);  //����ɿ�  
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);  //����������  
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ROUNDBUTTON_H__4FC14028_77FA_4D14_B975_D1858BF5EFAA__INCLUDED_)
