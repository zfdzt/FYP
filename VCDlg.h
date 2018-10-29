// VCDlg.h : header file
//
#if !defined(AFX_VCDLG_H__BA0735C3_526C_48DA_8E39_8F5312CA83A5__INCLUDED_)
#define AFX_VCDLG_H__BA0735C3_526C_48DA_8E39_8F5312CA83A5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "RoundBtn.h"
/////////////////////////////////////////////////////////////////////////////
// CVCDlg dialog
#include <Afxtempl.h>
#include <sstream>

class CVCDlg : public CDialog
{
// Construction
public:
	CVCDlg(CWnd* pParent = NULL);	// standard constructor
	void InitCbo();
	void InitHardware();
	void InitVariables();
	void ProcessData();
	void GetSamplingAndTime();
	double CalculatePower();
	double GetVoltageDiv(int sel);
	void CopyData();
// Dialog Data
	//{{AFX_DATA(CVCDlg)
	enum { IDD = IDD_VC_DIALOG };
	CListCtrl	m_power_list;
	CStatic	m_SubPanel2;
	CSliderCtrl m_ctrlSlider;
	RoundBtn m_btn1;
	RoundBtn m_btnCh2Postion;
	RoundBtn m_btnCh1Postion;
	RoundBtn m_apply;
	CComboBox	m_c_unit;
	CStatic	m_SubPanel;
	RoundBtn m_btnStop;
	RoundBtn m_btnStart;
	CEdit	m_editCh2Trigger;
	RoundBtn m_btnCh2Trigger;
	RoundBtn m_btnCh1Trigger;
	CEdit	m_editCh1Trigger;
	RoundBtn	m_btnAutoset;
	CStatic	m_MainPanel;
	CComboBox	m_cboTriggerSource;
	CComboBox	m_cboTriggerMode;
	CComboBox	m_cboTIMEBASE;
	CComboBox	m_cboCh2Voltage;
	CComboBox	m_cboCh1Voltage;
	int		m_txtCh1Position;
	int		m_txtCh1Trigger;
	int		m_txtCh2Position;
	int		m_txtCh2Trigger;
	float	m_power;
	float	m_voltage;
	double	m_capacitance;
	int		m_cycle_count;
	float	m_voltage2;
	float	m_xrange;
	float	m_yrange;
	float	m_frequency;
	int		m_span;
	float	m_voltage3;
	float	m_voltage4;
	float	m_voltage5;
	CEdit	m_power_edit;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVCDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
	CChart m_Chart2d;
	CChart m_Chart2d_voltage;
	int xx123;
	int TotalVoltage5s;
	int TotalTime;
	int Current_columns;
	CList<CRect,CRect&> m_listRect;

protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CVCDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnBtnCh1positionOk();
	afx_msg void OnBtnCh1triggerOk();
	afx_msg void OnBtnCh2positionOk();
	afx_msg void OnBtnCh2triggerOk();
	afx_msg void OnSelchangeCboCh1voltage();
	afx_msg void OnSelchangeCboCh2voltage();
	afx_msg void OnSelchangeCboTriggersource();
	afx_msg void OnSelchangeCboTriggermode();
	afx_msg void OnSelchangeCboTimebase();
	afx_msg void OnBtnAutoset();
	afx_msg void OnBtnStart();
	afx_msg void OnBtnStop();
	afx_msg void OnRadioOn();
	afx_msg void OnRadioOff();
	afx_msg void OnSelchangeComboCUnit();
	afx_msg void OnButtonApplyrange();
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	afx_msg void OnAbout();
	afx_msg void OnHelp();
	afx_msg void OnLoadData();
	afx_msg void OnSaveData();
	afx_msg void OnPlotLissajous();
	afx_msg void OnOutputLissajous();
	afx_msg void OnCustomdrawSlider5(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VCDLG_H__BA0735C3_526C_48DA_8E39_8F5312CA83A5__INCLUDED_)
