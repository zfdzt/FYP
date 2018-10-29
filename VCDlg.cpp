// VCDlg.cpp : implementation file
//

#include "stdafx.h"
#include <iomanip>
#include "VC.h"
#include "VCDlg.h"
#include "SDKDLL.h"
#include "MemDC.h"
#include "Channel.h"
#include "GlobalsVariables.h"

#include <fstream>
#include <iostream>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

struct PictureRange View;
struct PictureRange View2;
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVCDlg dialog

CVCDlg::CVCDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CVCDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CVCDlg)
	m_txtCh1Position = 0;
	m_txtCh1Trigger = 0;
	m_txtCh2Position = 0;
	m_txtCh2Trigger = 0;
	m_power = 0.0f;
	m_voltage = 0.0f;
	m_capacitance = 0.47;
	m_cycle_count = 0;
	m_voltage2 = 0.0f;
	m_xrange = 10;
	m_yrange = 2;
	m_frequency = 0.0f;
	m_span = 500;
	m_voltage3 = 0.0f;
	m_voltage4 = 0.0f;
	m_voltage5 = 0.0f;
	Current_columns =0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CVCDlg::DoDataExchange(CDataExchange* pDX)  //添加消息相应函数，固件和变量关联
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CVCDlg)
	DDX_Control(pDX, Power_list, m_power_list);
	DDX_Control(pDX, IDC_SUBPANEL2, m_SubPanel2);
	DDX_Control(pDX, IDC_SLIDER5, m_ctrlSlider);
	DDX_Control(pDX, IDC_BUTTON1, m_btn1);
	DDX_Control(pDX, IDC_BTN_CH2POSITION_OK, m_btnCh2Postion);
	DDX_Control(pDX, IDC_BTN_CH1POSITION_OK, m_btnCh1Postion);
	DDX_Control(pDX, IDC_BUTTON_APPLYRANGE, m_apply);
	DDX_Control(pDX, IDC_COMBO_C_UNIT, m_c_unit);
	DDX_Control(pDX, IDC_SUBPANEL, m_SubPanel);
	DDX_Control(pDX, IDC_BTN_STOP, m_btnStop);
	DDX_Control(pDX, IDC_BTN_START, m_btnStart);
	DDX_Control(pDX, IDC_EDIT_CH2TRIGGER, m_editCh2Trigger);
	DDX_Control(pDX, IDC_BTN_CH2TRIGGER_OK, m_btnCh2Trigger);
	DDX_Control(pDX, IDC_BTN_CH1TRIGGER_OK, m_btnCh1Trigger);
	DDX_Control(pDX, IDC_EDIT_CH1TRIGGER, m_editCh1Trigger);
	DDX_Control(pDX, IDC_BTN_AUTOSET, m_btnAutoset);
	DDX_Control(pDX, IDC_MAINPANEL, m_MainPanel);
	DDX_Control(pDX, IDC_CBO_TRIGGERSOURCE, m_cboTriggerSource);
	DDX_Control(pDX, IDC_CBO_TRIGGERMODE, m_cboTriggerMode);
	DDX_Control(pDX, IDC_CBO_TIMEBASE, m_cboTIMEBASE);
	DDX_Control(pDX, IDC_CBO_CH2VOLTAGE, m_cboCh2Voltage);
	DDX_Control(pDX, IDC_CBO_CH1VOLTAGE, m_cboCh1Voltage);
	DDX_Text(pDX, IDC_EDIT_CH1POSITION, m_txtCh1Position);
	DDX_Text(pDX, IDC_EDIT_CH1TRIGGER, m_txtCh1Trigger);
	DDX_Text(pDX, IDC_EDIT_CH2POSITION, m_txtCh2Position);
	DDX_Text(pDX, IDC_EDIT_CH2TRIGGER, m_txtCh2Trigger);
	DDX_Text(pDX, IDC_EDIT_POWER, m_power);
	DDX_Text(pDX, IDC_EDIT_VOLTAGE, m_voltage);
	DDX_Text(pDX, IDC_EDIT_C, m_capacitance);
	DDX_Text(pDX, IDC_EDIT_CYCLE, m_cycle_count);
	DDX_Text(pDX, IDC_EDIT_VOLTAGE2, m_voltage2);
	DDX_Text(pDX, IDC_EDIT_XRANGE, m_xrange);
	DDX_Text(pDX, IDC_EDIT_YRANGE, m_yrange);
	DDX_Text(pDX, IDC_EDIT_FREQUENCY, m_frequency);
	DDX_Text(pDX, IDC_EDIT_SPAN, m_span);
	DDX_Text(pDX, IDC_EDIT_VOLTAGE3, m_voltage3);
	DDX_Text(pDX, IDC_EDIT_VOLTAGE4, m_voltage4);
	DDX_Text(pDX, IDC_EDIT_VOLTAGE5, m_voltage5);
	DDX_Control(pDX, Power_hz, m_power_edit);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CVCDlg, CDialog)  //宏定义，之间添加消息相应函数，固件和变量关联
	//{{AFX_MSG_MAP(CVCDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_CH1POSITION_OK, OnBtnCh1positionOk)
	ON_BN_CLICKED(IDC_BTN_CH1TRIGGER_OK, OnBtnCh1triggerOk)
	ON_BN_CLICKED(IDC_BTN_CH2POSITION_OK, OnBtnCh2positionOk)
	ON_BN_CLICKED(IDC_BTN_CH2TRIGGER_OK, OnBtnCh2triggerOk)
	ON_CBN_SELCHANGE(IDC_CBO_CH1VOLTAGE, OnSelchangeCboCh1voltage)
	ON_CBN_SELCHANGE(IDC_CBO_CH2VOLTAGE, OnSelchangeCboCh2voltage)
	ON_CBN_SELCHANGE(IDC_CBO_TRIGGERSOURCE, OnSelchangeCboTriggersource)
	ON_CBN_SELCHANGE(IDC_CBO_TRIGGERMODE, OnSelchangeCboTriggermode)
	ON_CBN_SELCHANGE(IDC_CBO_TIMEBASE, OnSelchangeCboTimebase)
	ON_BN_CLICKED(IDC_BTN_AUTOSET, OnBtnAutoset)
	ON_BN_CLICKED(IDC_BTN_START, OnBtnStart)
	ON_BN_CLICKED(IDC_BTN_STOP, OnBtnStop)
	ON_BN_CLICKED(IDC_RADIO_ON, OnRadioOn)
	ON_BN_CLICKED(IDC_RADIO_OFF, OnRadioOff)
	ON_CBN_SELCHANGE(IDC_COMBO_C_UNIT, OnSelchangeComboCUnit)
	ON_BN_CLICKED(IDC_BUTTON_APPLYRANGE, OnButtonApplyrange)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_COMMAND(IDM_ABOUT, OnAbout)
	ON_COMMAND(IDM_HELP, OnHelp)
	ON_COMMAND(IDM_LOAD_DATA, OnLoadData)
	ON_COMMAND(IDM_SAVE_DATA, OnSaveData)
	ON_COMMAND(IDM_PLOT_LISSAJOUS, OnPlotLissajous)
	ON_COMMAND(IDM_OUTPUT_LISSAJOUS, OnOutputLissajous)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER5, OnCustomdrawSlider5)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVCDlg message handlers

BOOL CVCDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	CRect rect;
	GetWindowRect(&rect);
	m_listRect.AddTail(rect);//对话框的区域
	CWnd* pWnd = GetWindow(GW_CHILD);//获取子窗体
	while(pWnd)
	{
		pWnd->GetWindowRect(rect);//子窗体的区域
		m_listRect.AddTail(rect);           //CList<CRect,CRect> m_listRect成员变量
		pWnd = pWnd->GetNextWindow();//取下一个子窗体
	}

	m_ctrlSlider.SetRange(1,20);//设置滑动范围为1到20
    m_ctrlSlider.SetTicFreq(1);//每1个单位画一刻度
    m_ctrlSlider.SetPos(10);//设置滑块初始位置为1

	// TODO: Add extra initialization here
	// Set radio default
	CButton* pButton;
	pButton = (CButton*)this->GetDlgItem(IDC_RADIO_OFF);
	pButton->SetFocus();
	pButton->SetCheck(true);

	m_power_list.SetExtendedStyle(m_power_list.GetExtendedStyle() 
	| LVS_EX_GRIDLINES 
	| LVS_EX_FULLROWSELECT);  
	
	m_power_list.InsertColumn(0,"",LVCFMT_CENTER,60,0);
	m_power_list.InsertItem(0, "Time");
	m_power_list.InsertItem(1, "Power");
	Current_columns = 1;



	WORD Result;
	InitCbo();
	InitVariables();
	Result = sdSearchDevice(DeviceIndex);  //寻找连接语句 This function is used for finding device. If successful return 1, else return 0.
	if(Result == 0) 
	{
		MessageBox("Error:No Device Found!");
		return FALSE;
	}
	InitHardware();
	this->SetTimer (0,10,NULL);

	return TRUE;  // return TRUE  unless you set the focus to a control

	
	
}

void CVCDlg::OnSysCommand(UINT nID, LPARAM lParam)   //截获控制命令
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)  //nid 最后4位置0，判断得到的数据是否和IDM_ABOUTBOX相等
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}
//nID最低四位是被系统使用的
// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CVCDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);  //SM_CXICON = 11 'Width of standard icon  GetSystemMetrics用来获取icon的宽
		int cyIcon = GetSystemMetrics(SM_CYICON);  //SM_CYICON = 12 'Height of standard icon
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}

}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CVCDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
void  CVCDlg::InitCbo()   //初始载入的数据
{
	//Init Ch1 Voltage Combox
	m_cboCh1Voltage.AddString("10mV");
	m_cboCh1Voltage.AddString("20mV");
	m_cboCh1Voltage.AddString("50mV");
	m_cboCh1Voltage.AddString("100mV");
	m_cboCh1Voltage.AddString("200mV");
	m_cboCh1Voltage.AddString("500mV");
	m_cboCh1Voltage.AddString("1V");
	m_cboCh1Voltage.AddString("2V");
	m_cboCh1Voltage.AddString("5V");
	m_cboCh1Voltage.SetCurSel(8);
	
	//Init Ch2 Voltage Combox
	m_cboCh2Voltage.AddString("10V");
	m_cboCh2Voltage.AddString("20V");
	m_cboCh2Voltage.AddString("50V");
	m_cboCh2Voltage.AddString("100V");
	m_cboCh2Voltage.AddString("200V");
	m_cboCh2Voltage.AddString("500V");
	m_cboCh2Voltage.AddString("1000V");
	m_cboCh2Voltage.AddString("2000V");
	m_cboCh2Voltage.AddString("5000V");
	m_cboCh2Voltage.SetCurSel(8);

	//Init Trigger Source Combox
	m_cboTriggerSource.AddString ("CH1");
	m_cboTriggerSource.AddString ("CH2");
	m_cboTriggerSource.AddString ("ALT");
	m_cboTriggerSource.AddString ("EXT");
	m_cboTriggerSource.SetCurSel (0);

	//Init Trigger Mode Combox
	m_cboTriggerMode.AddString ("AUTO");
	m_cboTriggerMode.AddString ("NORMAL");
	m_cboTriggerMode.AddString ("SINGLE");
	m_cboTriggerMode.SetCurSel (0);

	//Init TIMEBASE Combox
	m_cboTIMEBASE.AddString ("4ns");
	m_cboTIMEBASE.AddString ("10ns");
	m_cboTIMEBASE.AddString ("20ns");
	m_cboTIMEBASE.AddString ("40ns");
	m_cboTIMEBASE.AddString ("0.1us");
	m_cboTIMEBASE.AddString ("0.2us");
	m_cboTIMEBASE.AddString ("0.4us");
	m_cboTIMEBASE.AddString ("1us");
	m_cboTIMEBASE.AddString ("2us");
	m_cboTIMEBASE.AddString ("4us");
	m_cboTIMEBASE.AddString ("10us");
	m_cboTIMEBASE.AddString ("20us");
	m_cboTIMEBASE.AddString ("40us");
	m_cboTIMEBASE.AddString ("0.1ms");
	m_cboTIMEBASE.AddString ("0.2ms");
	m_cboTIMEBASE.AddString ("0.4ms");
	m_cboTIMEBASE.AddString ("1ms");
	m_cboTIMEBASE.AddString ("2ms");
	m_cboTIMEBASE.AddString ("4ms");
	m_cboTIMEBASE.AddString ("10ms");
	m_cboTIMEBASE.AddString ("20ms");
	m_cboTIMEBASE.AddString ("40ms");
	m_cboTIMEBASE.AddString ("0.1s");
	m_cboTIMEBASE.AddString ("0.2s");
	m_cboTIMEBASE.AddString ("0.4s");
	m_cboTIMEBASE.AddString ("1s");
	m_cboTIMEBASE.AddString ("2s");
	m_cboTIMEBASE.AddString ("4s");
	m_cboTIMEBASE.AddString ("10s");
	m_cboTIMEBASE.AddString ("20s");
	m_cboTIMEBASE.AddString ("40s");
	m_cboTIMEBASE.AddString ("1min");
	m_cboTIMEBASE.AddString ("2min");
	m_cboTIMEBASE.AddString ("4min");
	m_cboTIMEBASE.AddString ("10min");
	m_cboTIMEBASE.AddString ("20min");
	m_cboTIMEBASE.AddString ("40min");
	m_cboTIMEBASE.AddString ("1hour");
	m_cboTIMEBASE.SetCurSel (12);

	// Capacitance
	m_c_unit.AddString ("n");
	m_c_unit.AddString ("u");
	m_c_unit.AddString ("m");
	m_c_unit.SetCurSel (1);

	
	SetTimer(0,10,NULL); //set a counter with period 10s


	// Plot
	CRect Rect ;
	Rect.left = 615;
	Rect.right = Rect.left + 580;
	Rect.top = 10;
	Rect.bottom = 367;

	//if ( !m_Chart2d.AllocSerie(1000) ) {
	//	AfxMessageBox("Error allocating chart serie") ;
    //    return ;  //载入1000组数据
	//}
	// Customize chart 

	m_Chart2d.SetChartTitle("Q-U Lissajous Plot");
	m_Chart2d.SetChartLabel("Uapp/kV","Q/uC");
	m_Chart2d.m_GridColor = RGB(0,255,255); //网格的颜色
	m_Chart2d.SetRange(-10,10,-2,2); //横纵坐标的尺寸
	m_Chart2d.SetAxisStyle(0); //设置坐标种类，0：single quadrant, 1:double quadrant, 2: 4 quadrant
	m_Chart2d.mpSerie[0].m_plotColor = RGB(0,0,0); //划线颜色  
	m_Chart2d.m_BGColor = RGB(255,255,255); //背景颜色
	m_Chart2d.SetGridXYNumber(10,10);
    m_Chart2d.AllocSerie(100000); //载入100000组数据
	
		//m_Chart2d.bLogScale = TRUE ;

	// Create chart .
	m_Chart2d.Create(WS_CHILD|WS_VISIBLE,Rect,this,IDC_SUBPANEL);

	//电压坐标
	Rect.left = 615;
	Rect.right = Rect.left + 580;
	Rect.top = 380;
	Rect.bottom = 547;

	m_Chart2d_voltage.SetChartTitle("Power Log-log plot");
	m_Chart2d_voltage.SetChartLabel("Periods", "Power");
	m_Chart2d_voltage.m_GridColor = RGB(0,255,255); //grid colour 
	m_Chart2d_voltage.SetRange(0, 20, 0, 70); //range of horizontal axis
	m_Chart2d_voltage.SetIntorFloat(1);
	m_Chart2d_voltage.SetAxisStyle(0); //set coordinate type，0：single quadrant, 1:double quadrant, 2: 4 quadrant
	m_Chart2d_voltage.mpSerie[0].m_plotColor = RGB(0,0,0); //plot colour  
	m_Chart2d_voltage.m_BGColor = RGB(255,255,255); //background colour
	m_Chart2d_voltage.SetGridXYNumber(20,7);
    m_Chart2d_voltage.AllocSerie(100000); //reload 100,000 data

	m_Chart2d_voltage.Create(WS_CHILD|WS_VISIBLE, Rect, this, IDC_SUBPANEL2);
	xx123 = 0;
	TotalVoltage5s = 0;
	TotalTime = 0;
	SetTimer(1,1000,NULL); //start a counter with period 1s 
	m_power_edit.SetWindowText("5");
}

//DEL void CAboutDlg::OnTimer(UINT nIDEvent) 
//DEL {
//DEL 	// TODO: Add your message handler code here and/or call default
//DEL 	
//DEL 	CDialog::OnTimer(nIDEvent);
//DEL }

void CVCDlg::OnTimer(UINT nIDEvent) // realize the online control function
{
	//////// PLOT

	
	if(nIDEvent == 0){

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/////////////////////////////// Code for power monitoring //////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		if (StartMonitor) 
		{
			CopyData();
			m_power = CalculatePower();
			UpdateData(false);
		}


		// TODO: Add your message handler code here and/or call default
		WORD result;
		CRect imgRect ;
		m_MainPanel.GetClientRect(&imgRect);  //获得mainpanel的坐标
		CDC *pDC = m_MainPanel.GetDC();    //获得mainpanel设备环境，然后可以再mainpanel上面绘图
		CDC m_dcImg;

		CBitmap *m_pBitmapOldBackground;  
		CBitmap m_bitmapBackground;
		CMemDC memDC(pDC,&imgRect);
		if(m_dcImg.GetSafeHdc() == NULL|| (m_bitmapBackground.m_hObject == NULL))
		{
			m_dcImg.CreateCompatibleDC(pDC);
			m_bitmapBackground.CreateCompatibleBitmap(pDC, imgRect.Width(),imgRect.Height()) ;
			m_pBitmapOldBackground = m_dcImg.SelectObject(&m_bitmapBackground) ;
		}

		result = sdMainPanelDrawGrid((HDC)m_dcImg,&View);  //This function is used for drawing grid on panel. If successful return 1, else return 0. 
		if(ScrollMode)
		{
			CTime mTime = GetCurrentTime();
			TimeData.Timer = (mTime.GetHour()*3600)+(mTime.GetMinute()*60)+(mTime.GetSecond());  //the number of seconds elapsed since midnight
			TimeData.Time = Time;  //the time of Timebase
			result = sdGetScrollData(DeviceIndex, &ControlState, &Levers, &TimeData, Ch1.Voltage, Ch2.Voltage, Ch1.ScrollData, Ch2.ScrollData, Ch1.DisplayData, Ch2.DisplayData, Trigger.TPosition, Ch1InGND, Ch2InGND);  //This function is used for getting and processing data when channel is in scroll mode. If successful return 1, else return 0.
		}  
		else
		{
			result = sdGetData(0, Ch1.Voltage, Ch2.Voltage, Ch1.HardwareData, Ch2.HardwareData, &ControlState, &FiltAndTrigger, &Levers, Level, StartCapture);
		}

		GetSamplingAndTime();

		if(Trigger.Mode == 2)
		{
			if(StartCapture)
			{
				ProcessData();
			}
			StartCapture = 0;
		}
		else
		{
			ProcessData();
		}

		if(!XYMode)
		{
			result = sdDisplayData((HDC)m_dcImg, &View, PointOrLine, Ch1.DisplayData, &(Ch1.ChannelColor));
			result = sdDisplayData((HDC)m_dcImg, &View, PointOrLine, Ch2.DisplayData, &(Ch2.ChannelColor));
		}
		else
		{
			result = sdDisplayDataXYMode((HDC)m_dcImg, &View, PointOrLine, Ch1.DisplayData, Ch2.DisplayData);
		}
		memDC.BitBlt(0, 0, imgRect.Width(), imgRect.Height(), 
						   &m_dcImg, 0, 0, SRCCOPY) ;

		memDC.ReleaseMemDC();
		ReleaseDC(&m_dcImg);
		ReleaseDC(pDC);
	}
	if(nIDEvent == 1){
		CString sad;
		m_power_edit.GetWindowText(sad);
		//MessageBox(sad);
		if (StartMonitor) //StartMonitor
		{
			//static int x=5;
			//static int y=0;
			TotalVoltage5s += CalculatePower();
			//TotalVoltage5s += 20;
			xx123++;
			//CString str="";
			//str.Format("%d, %d", xx123, TotalTime);
			//SetDlgItemText(IDC_STATIC13131, str);
			CString sad;
			m_power_edit.GetWindowText(sad);

			int num1 = _ttoi(sad);
			if(xx123 >= num1){
				if(TotalTime > 19){
					//x+=5;
					//m_Chart2d_voltage.SetRange(x-5, x, 0, 100);
					m_Chart2d_voltage.ClearChart();
					TotalTime = 0;
				}

				CTime tm;
				tm=CTime::GetCurrentTime();
				CString str=tm.Format("%X");
				ostringstream os;
				float ds= (float)atof((char *)(LPTSTR)(LPCTSTR)sad);
				os << TotalVoltage5s/ds;
				ostringstream os1;
				m_power_list.InsertColumn(Current_columns,"",LVCFMT_CENTER,80,0);
				m_power_list.SetItemText(0, Current_columns, str);
				m_power_list.SetItemText(1, Current_columns, os.str().c_str());
				m_power_list.SetItemState(Current_columns, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED);  
				m_power_list.EnsureVisible(Current_columns, FALSE);


				m_Chart2d_voltage.SetXYValue(TotalTime, TotalVoltage5s/ds, TotalTime, 0);
				TotalTime++;
				TotalVoltage5s = 0;
				xx123 = 0;
			}
		}
		m_Chart2d_voltage.Invalidate();
	}
	CDialog::OnTimer(nIDEvent);
}


void CVCDlg :: InitVariables()
{
	CRect imgRect ;
	m_MainPanel.GetClientRect (&imgRect);
	View.Width =(WORD)imgRect.Width();
	View.Hight =(WORD)imgRect.Height();
	View.Bottom =2;
	View.Left= 2;
	View.Right= 2;
	View.Top= 2;
	
	Ch1.Position=127;
	Ch2.Position=127;
	Trigger.TPosition = Ch1.Position ;
	Ch1.SetChannelColor(0,255,0);
	Ch2.SetChannelColor(255,255,0);

	ControlState.BufferSize = 10;
	ControlState.ChannelSelect = 2;
	ControlState.DataLength = 1;
	ControlState.IsAlt = 0;
	ControlState.TIMEBASE = 12;
	ControlState.TriggerAddress = 50;
	ControlState.TriggerSource = 0;

	FiltAndTrigger.Ch1Filt = 0;
	FiltAndTrigger.Ch2Filt = 0;
	FiltAndTrigger.TriggerFilt = 0;
	FiltAndTrigger.TriggerMode = 0;
	FiltAndTrigger.TriggerSlope = 0;
	
	Levers.Ch1Lever = 127;
	Levers.Ch1TrigLever = 127;
	Levers.Ch2Lever = 127;
	Levers.Ch2TrigLever = 127;
	Levers.ExtTrigLever = 128;
	
	InterpolationLineMode = 1;
	PointOrLine = 1;
	DeviceIndex = 0;
	ScrollMode = 0;
	StartCapture = 1;
	
	XYMode = FALSE;
	Ch1InGND = FALSE;
	Ch2InGND = FALSE;
	m_txtCh1Position = 127;
	m_txtCh1Trigger = 127;
	m_txtCh2Position = 127;
	m_txtCh2Trigger = 127;
	AutosetData.Ch1Enabled = 1;
	AutosetData.Ch2Enabled = 1;
	AutosetData.Ch1InGND = 0;
	AutosetData.Ch2InGND = 0;

	StartMonitor = 0;
	Unit = 1000000;
	Capacitance = 0;
	UpdateData(FALSE);
}
void CVCDlg :: InitHardware()
{
	WORD Result;
	Result = sdGetLevel(DeviceIndex, Level);  //This function is used for reading the waveform position adjust data from hardware
    Result = sdSetTriggerAndSampleRate(DeviceIndex, Trigger.Slope, &ControlState);  //This function is used for setting trigger and timebase.
    Result = sdSetFilt(DeviceIndex, &FiltAndTrigger); //This function is used for setting channel and trigger filter
    Result = sdSetVoltageAndCoupling(DeviceIndex, Ch1.Voltage , Ch2.Voltage, Ch1.ACDC, Ch2.ACDC, Trigger.Source);  //This function is used for setting voltage and Coupling
    Result = sdSetOffset(DeviceIndex, &Levers, Ch1.Voltage, Ch2.Voltage, Trigger.Source, Level);	// This if used for adjusting the position of the channel. If successful return true, else return false.	
}
void CVCDlg :: ProcessData()
{
	WORD result;
	if(!ScrollMode)
	{
		if(!Ch1InGND)
		{
			result = sdChannelDataBuffer(&ControlState, InterpolationLineMode, Ch1.BufferData, Ch1.HardwareData);  //This function is used for processing data and copying data to ?chx_data? from ?ch_data?. If successful return 1, else return 0.
		}
		else
		{
			result = sdChannelInGND(Ch1.Position, Ch1.BufferData); //This function is used for processing data when channel is in GND. If successful return 1, else return 0.
		}
		if(!Ch2InGND)
		{
			result = sdChannelDataBuffer(&ControlState, InterpolationLineMode, Ch2.BufferData, Ch2.HardwareData);
		}
		else
		{
			result = sdChannelInGND(Ch2.Position, Ch2.BufferData);
		}
		result = sdGetDisplayData(&ControlState, Ch1.DisplayData, Ch1.BufferData);  //This function is used for getting display data. If successful return 1, else return 0.
		result = sdGetDisplayData(&ControlState, Ch2.DisplayData, Ch2.BufferData);
	}
}
void CVCDlg::OnBtnCh1positionOk() 
{
	// TODO: Add your control notification handler code here
	int Temp;
	WORD Result;
	CString str;
	CEdit *pEdit = (CEdit*)GetDlgItem(IDC_EDIT_CH1POSITION);
	pEdit->GetWindowText(str);
	Temp = m_txtCh1Position;
	m_txtCh1Position = atoi((const char *)str);
	if(m_txtCh1Position>=0 && m_txtCh1Position<256)
	{
		if(m_editCh1Trigger.IsWindowEnabled())
		{
			m_txtCh1Trigger = m_txtCh1Position;
		}
	}
	else
	{
		MessageBox("The Range is 0 to 255!");
		m_txtCh1Position = Temp;
		if(m_editCh1Trigger.IsWindowEnabled())
		{
			m_txtCh1Trigger = Temp;
		}
	}
	UpdateData(FALSE);
	Levers.Ch1Lever = m_txtCh1Position;
	if(m_editCh1Trigger.IsWindowEnabled())
	{
		Levers.Ch1TrigLever = m_txtCh1Position;
		Trigger.TPosition = m_txtCh1Position;
	}
	Result = sdSetOffset(DeviceIndex, &Levers, Ch1.Voltage, Ch2.Voltage, Trigger.Source, Level);
}


void CVCDlg::OnBtnCh1triggerOk() 
{
	// TODO: Add your control notification handler code here
	int Temp;
	WORD Result;
	CString str;
	CEdit *pEdit = (CEdit*)GetDlgItem(IDC_EDIT_CH1TRIGGER);
	pEdit->GetWindowText(str);
	Temp = m_txtCh1Trigger;
	m_txtCh1Trigger = atoi((const char *)str);
	if(m_txtCh1Trigger<0 || m_txtCh1Trigger>255)
	{
		MessageBox("The Range is 0 to 255!");
		m_txtCh1Trigger = Temp;
	}
	UpdateData(FALSE);
	Levers.Ch1TrigLever = m_txtCh1Trigger;
	Trigger.TPosition = m_txtCh1Position;
	Result = sdSetOffset(DeviceIndex, &Levers, Ch1.Voltage, Ch2.Voltage, Trigger.Source, Level);
}

void CVCDlg::OnBtnCh2positionOk() 
{
	// TODO: Add your control notification handler code here
	int Temp;
	WORD Result;
	CString str;
	CEdit *pEdit = (CEdit*)GetDlgItem(IDC_EDIT_CH2POSITION);
	pEdit->GetWindowText(str);
	Temp = m_txtCh2Position;
	m_txtCh2Position = atoi((const char *)str);
	if(m_txtCh2Position>=0 && m_txtCh2Position<256)
	{
		if(m_editCh2Trigger.IsWindowEnabled())
		{
			m_txtCh2Trigger = m_txtCh2Position;
		}
	}
	else
	{
		MessageBox("The Range is 0 to 255!");
		m_txtCh2Position = Temp;
		if(m_editCh2Trigger.IsWindowEnabled())
		{
			m_txtCh2Trigger = Temp;
		}
	}
	UpdateData(FALSE);
	Levers.Ch2Lever = m_txtCh2Position;
	if(m_editCh2Trigger.IsWindowEnabled())
	{
		Levers.Ch2TrigLever = m_txtCh2Position;
		Trigger.TPosition = m_txtCh2Position;
	}
	Result = sdSetOffset(DeviceIndex, &Levers, Ch1.Voltage, Ch2.Voltage, Trigger.Source, Level);
}

void CVCDlg::OnBtnCh2triggerOk() 
{
	// TODO: Add your control notification handler code here
	int Temp;
	WORD Result;
	CString str;
	CEdit *pEdit = (CEdit*)GetDlgItem(IDC_EDIT_CH2TRIGGER);
	pEdit->GetWindowText(str);
	Temp = m_txtCh2Trigger;
	m_txtCh2Trigger = atoi((const char *)str);
	if(m_txtCh2Trigger<0 || m_txtCh2Trigger>255)
	{
		MessageBox("The Range is 0 to 255!");
		m_txtCh2Trigger = Temp;
	}
	UpdateData(FALSE);
	Levers.Ch2TrigLever = m_txtCh2Trigger;
	Trigger.TPosition = m_txtCh2Position;
	Result = sdSetOffset(DeviceIndex, &Levers, Ch1.Voltage, Ch2.Voltage, Trigger.Source, Level);
}

void CVCDlg::OnSelchangeCboCh1voltage() 
{
	// TODO: Add your control notification handler code here
	WORD Result;
	CComboBox *pCbo =(CComboBox*) GetDlgItem(IDC_CBO_CH1VOLTAGE);
	Ch1.Voltage = pCbo->GetCurSel();
	Result = sdSetVoltageAndCoupling(DeviceIndex, Ch1.Voltage , Ch2.Voltage, Ch1.ACDC, Ch2.ACDC, Trigger.Source);
    Result = sdSetOffset(DeviceIndex, &Levers, Ch1.Voltage, Ch2.Voltage, Trigger.Source, Level);
}

void CVCDlg::OnSelchangeCboCh2voltage() 
{
	// TODO: Add your control notification handler code here
	WORD Result;
	CComboBox *pCbo =(CComboBox*) GetDlgItem(IDC_CBO_CH2VOLTAGE);
	Ch2.Voltage = pCbo->GetCurSel();
	Result = sdSetVoltageAndCoupling(DeviceIndex, Ch1.Voltage , Ch2.Voltage, Ch1.ACDC, Ch2.ACDC, Trigger.Source);
    Result = sdSetOffset(DeviceIndex, &Levers, Ch1.Voltage, Ch2.Voltage, Trigger.Source, Level);
}

void CVCDlg::OnSelchangeCboTriggersource() 
{
	// TODO: Add your control notification handler code here
	long Result;
	CComboBox *pCbo =(CComboBox*) GetDlgItem(IDC_CBO_TRIGGERSOURCE);
	Trigger.Source = pCbo->GetCurSel();
	if(Trigger.Source == 0)//CH1
	{
		m_editCh1Trigger.EnableWindow(TRUE);
		m_btnCh1Trigger.EnableWindow(TRUE);
		m_editCh2Trigger.EnableWindow(FALSE);
		m_btnCh2Trigger.EnableWindow (FALSE);
	}
	else if(Trigger.Source == 1)//CH2
	{
		m_editCh1Trigger.EnableWindow(FALSE);
		m_btnCh1Trigger.EnableWindow(FALSE);
		m_editCh2Trigger.EnableWindow(TRUE);
		m_btnCh2Trigger.EnableWindow (TRUE);
	}
	else if (Trigger.Source == 2)//ALT
	{
		m_editCh1Trigger.EnableWindow(TRUE);
		m_btnCh1Trigger.EnableWindow(TRUE);
		m_editCh2Trigger.EnableWindow(TRUE);
		m_btnCh2Trigger.EnableWindow (TRUE);
	}
	else//EXT
	{
		m_editCh1Trigger.EnableWindow(FALSE);
		m_btnCh1Trigger.EnableWindow(FALSE);
		m_editCh2Trigger.EnableWindow(FALSE);
		m_btnCh2Trigger.EnableWindow (FALSE);
	}
	ControlState.TriggerSource = Trigger.Source;
	if(Ch1.Enable && Ch2.Enable)
	{
		ControlState.ChannelSelect = 2;
	}
	else if(!Ch1.Enable && Ch2.Enable)
	{
		ControlState.ChannelSelect = 3;
	}
	else
	{
		ControlState.ChannelSelect = 0;
	}
	if(Trigger.Source == 2)
	{
		ControlState.IsAlt = 1;
		Result = sdCaptureStart(DeviceIndex);
        Result = sdTriggerEnabled(DeviceIndex);
	}
	else
	{
		ControlState.IsAlt = 0;
	}
	Result = sdSetTriggerAndSampleRate(DeviceIndex, Trigger.Slope, &ControlState);
	Result = sdSetOffset(DeviceIndex, &Levers, Ch1.Voltage, Ch2.Voltage, Trigger.Source, Level);
}

void CVCDlg::OnSelchangeCboTriggermode() 
{
	// TODO: Add your control notification handler code here
	long Result;
	CComboBox *pCbo =(CComboBox*) GetDlgItem(IDC_CBO_TRIGGERMODE);
	FiltAndTrigger.TriggerMode = pCbo->GetCurSel();
	Trigger.Mode = pCbo->GetCurSel();
	if(Trigger.Mode == 1 && Trigger.Source == 2)
	{
		Result = sdCaptureStart(DeviceIndex);
        Result = sdTriggerEnabled(DeviceIndex);
	}
	if(Trigger.Source != 2 && StartCapture == 0)
	{
		StartCapture = 1;
	}
}

void CVCDlg::OnSelchangeCboTimebase()
{
	// TODO: Add your control notification handler code here
	WORD Result;
	CComboBox *pCbo =(CComboBox*) GetDlgItem(IDC_CBO_TIMEBASE);
	ControlState.TIMEBASE = pCbo->GetCurSel();
	if(ControlState.TIMEBASE >24)
	{
		ScrollMode = 1;
		TimeData.ScrollStart = 1;
	}
	else
	{
		ScrollMode = 0;		
		TimeData.ScrollStart = 0;
	}
	Result = sdSetTriggerAndSampleRate(DeviceIndex, Trigger.Slope, &ControlState);
    Result = sdSetFilt(DeviceIndex, &FiltAndTrigger);
	Result = sdCaptureStart(DeviceIndex);
}

void CVCDlg::OnBtnAutoset() 
{
	// TODO: Add your control notification handler code here
	WORD Result;
	m_btnAutoset.EnableWindow(FALSE);
	KillTimer(0);
	if(Trigger.Source == 1)
	{
		AutosetData.WhichChannel = 1;
	}
	else
	{
		AutosetData.WhichChannel = 0;
	}
    Result = sdAutoset(DeviceIndex, &ControlState, &AutosetData, &FiltAndTrigger, &Levers, Level);
	Ch1.Voltage = AutosetData.Ch1Voltage;
	Ch2.Voltage = AutosetData.Ch2Voltage;
	if(Trigger.Source == 0)
	{
		ControlState.TIMEBASE = AutosetData.Ch1Timebase;
	}
	else
	{
		ControlState.TIMEBASE = AutosetData.Ch2Timebase;
	}
	m_cboCh1Voltage.SetCurSel(Ch1.Voltage);
	m_cboCh2Voltage.SetCurSel(Ch2.Voltage);
	m_cboTIMEBASE.SetCurSel(ControlState.TIMEBASE);

	ControlState.TriggerAddress = 50;
	ControlState.TriggerSource = Trigger.Source;
	Result = sdSetTriggerAndSampleRate(DeviceIndex, Trigger.Slope, &ControlState);
    Result = sdSetFilt(DeviceIndex, &FiltAndTrigger);
    Result = sdSetVoltageAndCoupling(DeviceIndex, Ch1.Voltage , Ch2.Voltage, Ch1.ACDC, Ch2.ACDC, Trigger.Source);
    Result = sdSetOffset(DeviceIndex, &Levers, Ch1.Voltage, Ch2.Voltage, Trigger.Source, Level);	
	Result = sdCaptureStart(DeviceIndex);

	SetTimer(0,10,NULL);
	m_btnAutoset.EnableWindow(TRUE);
}

void CVCDlg::OnBtnStart() 
{
	// TODO: Add your control notification handler code here
	StartCapture = 1;
	SetTimer(0,10,NULL);

	// For power monitoring test
	//m_voltage = 5;
	//m_power = 10;
	//UpdateData(false);
}

void CVCDlg::OnBtnStop() 
{
	// TODO: Add your control notification handler code here
	StartCapture = 0;
	KillTimer(0);
}
void CVCDlg :: GetSamplingAndTime()
{
	Sampling = sdDisplaySampling(Ch1.Enable, Ch2.Enable, Trigger.Source, ControlState.TIMEBASE, ControlState.BufferSize, &Time);
}

//DEL void CVCDlg::OnButtonSave() //保存数据  useless class
//DEL {
//DEL 	// TODO: Add your control notification handler code here
//DEL 	ofstream Data_ch1("ch1.txt", ios::out);
//DEL 	if (Time == 0)
//DEL 	{
//DEL 		Data_ch1<<Time_saved_1<<endl;
//DEL 	}
//DEL 	else
//DEL 	{
//DEL 		Data_ch1<<Time<<endl;
//DEL 	}
//DEL 	Data_ch1<<Ch1.Voltage<<endl;
//DEL 	for (int i = 0; i < 32780; i++)
//DEL 	{
//DEL 		//Data_ch1<<Data1[i]<<" ";
//DEL 		Data_ch1<<Ch1.HardwareData[i]<<" ";
//DEL 	}
//DEL 	Data_ch1.close();
//DEL 
//DEL 	ofstream Data_ch2("ch2.txt", ios::out);
//DEL 	if (Time == 0)
//DEL 	{
//DEL 		Data_ch2<<Time_saved_1<<endl;
//DEL 	}
//DEL 	else
//DEL 	{
//DEL 		Data_ch2<<Time<<endl;
//DEL 	}
//DEL 	Data_ch2<<Ch2.Voltage<<endl;
//DEL 	for (int j = 0; j < 32780; j++)
//DEL 	{
//DEL 		//Data_ch2<<Data2[j]<<" ";
//DEL 		Data_ch2<<Ch2.HardwareData[j]<<" ";
//DEL 	}
//DEL 	Data_ch2.close();
//DEL }

//DEL void CVCDlg::OnButtonLoad()  //载入数据 useless class
//DEL {
//DEL 	// TODO: Add your control notification handler code here
//DEL 	// Read data to Data1 form ch1.txt
//DEL 	ifstream Data_ch1("ch1.txt", ios::in);
//DEL 	Data_ch1>>Time_saved_1;
//DEL 	Data_ch1>>Ch1.Voltage;
//DEL 	for (int i = 0; i < 32780; i++)
//DEL 	{
//DEL 		Data_ch1>>Data1[i];
//DEL 	}
//DEL 	Data_ch1.close();
//DEL 	// Read data to Data2 form ch2.txt
//DEL 	ifstream Data_ch2("ch2.txt", ios::in);
//DEL 	Data_ch2>>Time_saved_2;
//DEL 	Data_ch2>>Ch2.Voltage;
//DEL 	for (int j = 0; j < 32780; j++)
//DEL 	{
//DEL 		Data_ch2>>Data2[j];
//DEL 	}
//DEL 	Data_ch2.close();
//DEL 	// if Time_saved_1 is not equal to Time_saved_2, print error
//DEL }

void CVCDlg::OnRadioOn()
{
	// TODO: Add your control notification handler code here
	StartMonitor = 1;
	
}

void CVCDlg::OnRadioOff() 
{
	// TODO: Add your control notification handler code here
	StartMonitor = 0;
}

double CVCDlg::CalculatePower()
{
	CString str;
	CEdit *pEdit = (CEdit*)GetDlgItem(IDC_EDIT_C);  //IDC_EDIT_C 是电压值
	pEdit->GetWindowText(str);
	// Calculate Capacitance
	m_capacitance = atof((const char *)str);
	Capacitance = m_capacitance / Unit;
	// Calculate valid range
	int index1, index2, index;
	for (int i = 0; i < 32780; i++)
	{
		if (Data1[i] != 0) 
			index1 = i;   
		if (Data2[i] != 0) 
			index2 = i;
	}
	// Prevent invalid input
	if (index1 < index2)
	{
		index = index1 - 5;
	}
	else
	{
		index = index2 - 5;
	}
	// Backup & smooth
	int q,n;
	//int span = 0;
	// Read span
/*	CString str2;
	CEdit *pEdit2 = (CEdit*)GetDlgItem(IDC_EDIT_SPAN);
	pEdit2->GetWindowText(str2);
	span = atoi((const char *)str2); //read smooth number
*/
/*	
	int span = 5;
	//int span = atoi((const char *)str2);

	if (span % 2 == 0) 
	{
		span +=1;
	}
	int n = (span - 1) / 2;  // 2
*/
	//int n = span / 2;
/*	for (q = 0; q < n; q++)
	{
		s_sum = 0;
		for (i_sum = 0; i_sum <= 2 * q; i_sum++)
		{
			s_sum += Data1[i_sum];
		}
		Data1_b[q] = s_sum / (2 * q + 1);

		s_sum = 0;
		for (i_sum = 0; i_sum <= 2 * q; i_sum++)
		{
			s_sum += Data2[i_sum];
		}
		Data2_b[q] = s_sum / (2 * q + 1);
	}
*/
	//store hardware data for further output
	for (q =0; q< index; q++)
	{
		Data1_HardWareData[q] = Data1[q];
		Data2_HardWareData[q] = Data2[q];
	}
	
	Data1_b[0] = (((69) * Data1[0]) + (4 * Data1[1]) + ((-6) * Data1[2]) + (4 * Data1[3]) + ((-1) * Data1[4])) / 70;
    Data1_b[1] = (((2) * Data1[1]) + (27 * Data1[2]) + ((12) * Data1[3]) + ((-8) * Data1[4]) + ((2) * Data1[5])) / 35;
	Data1_b[index-1] = (((2) * Data1[index-4]) + ((-8) * Data1[index-3]) + ((12) * Data1[index-2]) + ((27) * Data1[index-1]) + (1 * Data1[index])) / 35;
	Data1_b[index] = (((-1) * Data1[index-4]) + (4 * Data1[index-3]) + ((-6) * Data1[index-2]) + ((4) * Data1[index-1]) + ((69) * Data1[index])) / 70;

    for (q = 2 ; q < index-2 ; q++)
	{
		Data1_m[q] = Data1[q];
        Data2_m[q] = Data2[q];
	}
	for (n = 0; n < span; n++)
	{
		for (q = 2 ; q < index-2 ; q++)
		{
			Data1_n[q] = (((-3) * Data1_m[q-2]) + (12 * Data1_m[q-1]) + (17 * Data1_m[q]) + (12 * Data1_m[q+1]) + ((-3) * Data1_m[q+2])) / 35;
			Data2_n[q] = (((-3) * Data2_m[q-2]) + (12 * Data2_m[q-1]) + (17 * Data2_m[q]) + (12 * Data2_m[q+1]) + ((-3) * Data2_m[q+2])) / 35;
		}
	//	for (q = 2 ; q < index-2 ; q++)
	//	{
	//		Data1_m[q] = (((-3) * Data1_n[q-2]) + (12 * Data1_n[q-1]) + (17 * Data1_n[q]) + (12 * Data1_n[q+1]) + ((-3) * Data1_n[q+2])) / 35;
	//		Data2_m[q] = (((-3) * Data2_n[q-2]) + (12 * Data2_n[q-1]) + (17 * Data2_n[q]) + (12 * Data2_n[q+1]) + ((-3) * Data2_n[q+2])) / 35;
	//	}
		for (q = 2 ; q < index-2 ; q++)
		{
			Data1_m[q] = Data1_n[q];
			Data2_m[q] = Data2_n[q];
		}

	}

	for (q = 2 ; q < index-2 ; q++)
	{
		Data1_b[q] = Data1_m[q];
		Data2_b[q] = Data2_m[q];
	}
	
	

	// Regulation
	//CComboBox *pCbo =(CComboBox*) GetDlgItem(IDC_CBO_CH1VOLTAGE);
	//Ch1.Voltage = pCbo->GetCurSel();
	for (q = 0; q <= index; q++)
	{
		Data1_b[q] = (Data1_b[q] - (255 - m_txtCh1Position)) * 0.025 * GetVoltageDiv(Ch1.Voltage);   //ch1: capacitor voltage
		Data2_b[q] = (Data2_b[q] - (255 - m_txtCh2Position)) * 0.025 * GetVoltageDiv(Ch2.Voltage) * 1000; //ch2: applied voltage
		//Data1_b[q] = Data1_b[q] / 10; // debug
        //Data2_b[q] = Data2_b[q];
	}
	for (q = 0; q <= index; q++)
	{
		Data1_c[q] = (Data1[q] - (255 - m_txtCh1Position)) * 0.025 * GetVoltageDiv(Ch1.Voltage); 
		Data2_c[q] = (Data2[q] - (255 - m_txtCh2Position)) * 0.025 * GetVoltageDiv(Ch2.Voltage) * 1000;
		//Data1_c[q] = Data1_c[q]/10;
		//Data2_c[q] = Data2_c[q];
	}
	// Max & Min
	double max1b = Data1_b[0], max2b = Data2_b[0], min1b = 0, min2b = 0, test_ib = index;
	double indexb = index ;
	for (q = 0; q <= indexb; q++)
	{
		if (max1b < Data1_b[q]) 
			max1b = Data1_b[q];
		if (max2b < Data2_b[q]) 
			max2b = Data2_b[q];
		if (min1b > Data1_b[q]) 
			min1b = Data1_b[q];
		if (min2b > Data2_b[q]) 
		{
			min2b = Data2_b[q];
			test_ib = q;
		}
	}
	// second
	int startb, endb, controlb = 0;
	for (q = 0; q <= indexb; q++)
	{
		if (controlb == 0)
		{
			if (Data2_b[q] < 10 && Data2_b[q] > -10)
			{
				startb = q;
				controlb = 1;
			}
		}
		if (controlb == 1)
		{
			if (Data2_b[q] / max2b > 0.7 || Data2_b[q] / min2b > 0.8)
			{
				controlb = 2;
			}
			
		}
		
		if (controlb == 2)
		{
			if (Data2_b[q] < 10 && Data2_b[q] > -10)
			{
				endb = q;
				controlb = 3;
			}
		}
		/*
		if (controlb == 3)
		{
			if (Data2_b[q] / max2b > 0.7 || Data2_b[q] / min2b > 0.7)
			{
				endb = q;
				controlb = 4;
			}
			
		}
		
		if (controlb == 4)
		{
			if (Data2_b[q] < 10 && Data2_b[q] > -10)
			{
				endb = q;
				controlb = 5;
			}
		}
        
		if (controlb == 5)
		{
			if (Data2_b[q] / max2b > 0.7 || Data2_b[q] / min2b > 0.7)
			{
				endb = q;
				controlb = 6;
			}
			
		}
		
		if (controlb == 6)   
		{
			if (Data2_b[q] < 10 && Data2_b[q] > -10)
			{
				endb = q;
				controlb = 7;
			}
		}
		*/
		//if (control == 5){end = q;if (Data2_b[q] != 0){control = 6;}}
	}
	//endb += (endb - startb) * 0.005;
	
	startb += 0;
	endb += 0;
	//endb = endb + 25;
	
/*	
	UpdateData(false);
	//int k = (cycle_index[0] * 8.5 / 8) / 500;
	//int k = (cycle_index[count - 1]) / 500;
	int total = 5000;
	double k = double(endb - startb) / total;
	for (q = 0 ; q < total ; q++)
	//for (q = startb; q < startb+indexb/3.5; q++)
	{
		//m_Chart2d.SetXYValue((double)q * 100,(double)q,q,0);
		//m_Chart2d.SetXYValue(q*10,(double)Data1_b[int(start + q * k)+1],q,0);
		//m_Chart2d.SetXYValue(start+q*10,(double)Data2_b[int(start + q * k)+1] / 1000 / 3,q,0);
		m_Chart2d.SetXYValue((double)Data2_b[int(startb + q * k)] / 1000,(double)Data1_b[int(startb + q * k)] * Capacitance * 1000000,q,0);
	    //m_Chart2d.SetXYValue((double)Data2_b[q]/1000,(double)Data1_b[q] * Capacitance * 1000000,q,0);
	}
	//m_Chart2d.SetXYValue(q*10,(double)Data2_b[end] / 1000,500,0);
	//m_Chart2d.SetXYValue((double)Data2_b[endb]/1000,(double)Data1_b[endb] * Capacitance * 1000000, indexb/3.5, 0);
	m_Chart2d.Invalidate();
	
*/
	UpdateData(false);
	//int k = (cycle_index[0] * 8.5 / 8) / 500;
	//int k = (cycle_index[count - 1]) / 500;
	//int total = 5000;
	//double k = double(end - start) / total;
	for (q = 0 ; q < indexb/3.65; q++)
	{
		//m_Chart2d.SetXYValue((double)q * 100,(double)q,q,0);
		//m_Chart2d.SetXYValue(q*10,(double)Data1_c[int(start + q * k)+1],q,0);
		//m_Chart2d.SetXYValue(start+q*10,(double)Data2_c[int(start + q * k)+1] / 1000 / 3,q,0); //错误绘图方式
		//m_Chart2d.SetXYValue((double)Data2_c[int(start + q * k)],(double)Data1_c[int(start + q * k)] * Capacitance * 1000000,q,0);
		m_Chart2d.SetXYValue((double)Data2_b[startb + q]/1000,(double)Data1_b[startb + q] * Capacitance * 1000000,q,0);
		//m_Chart2d.SetXYValue((double)Data2_c[q],(double)Data1_c[q] * Capacitance * 1000000,q,0);
	}
	
	//m_Chart2d.SetXYValue(q*10,(double)Data2_b[end] / 1000,500,0);
	//m_Chart2d.SetXYValue((double)Data2_c[10000],(double)Data1_c[10000] * Capacitance * 1000000, 10000, 0);
	m_Chart2d.Invalidate();
	//真实值算法

	// Max & Min
	double max1 = Data1_c[0], max2 = Data2_c[0], min1 = 0, min2 = 0, test_i = index;
	//index = index - span;
	
	for (q = 0; q <= index; q++)
	{
		if (max1 < Data1_c[q]) 
			max1 = Data1_c[q];
		if (max2 < Data2_c[q]) 
			max2 = Data2_c[q];
		if (min1 > Data1_c[q]) 
			min1 = Data1_c[q];
		if (min2 > Data2_c[q]) 
		{
			min2 = Data2_c[q];
			test_i = q;
		}
	}
	// second
	int start, end, control = 0;
	for (q = 0; q <= index; q++)
	{
		if (control == 0)
		{
			if (Data2_c[q] < 10 && Data2_c[q] > -10)
			{
				start = q;
				control = 1;
			}
		}
		if (control == 1)
		{
			if (Data2_c[q] / max2 > 0.7 || Data2_c[q] / min2 > 0.7)
			{
				control = 2;
			}
			
		}
		if (control == 2)
		{
			if (Data2_c[q] < 10 && Data2_c[q] > -10)
			{
				control = 3;
			}
		}
		if (control == 3)
		{
			if (Data2_c[q] / max2 > 0.7 || Data2_c[q] / min2 > 0.7)
			{
				control = 4;
			}
			
		}
		if (control == 4)
		{
			if (Data2_c[q] < 10 && Data2_c[q] > -10)
			{
				end = q;
				control = 5;
			}
		}
		//if (control == 5){end = q;if (Data2_b[q] != 0){control = 6;}}
	}
	end += (end - start) * 0.005;
	
	index1 = 0;
	index2 = 0;
	
	////////////////////
	// MAIN PROCEDURE //
	////////////////////
	// SEE FLOW CHART //
	////////////////////
	// DO SUM
	double answer = 0;
	//for (int j = 0; j < index; j++)
//	start += span;
//	end += span;
	for (int j = start; j <= end; j++)
	{
		answer += 0.5 * (Data2_c[j + 1] + Data2_c[j]) * (Data1_c[j+1] - Data1_c[j]);
	}
	// *C
	answer *= Capacitance;
	// f
	index = end - start;
	if (Time ==0)
	{
		m_frequency = 1 / (index * Time_saved_1);
	}
	else
	{
		
		m_frequency = 1 / (index * Time); //time is the interval of 2 sampling point, multiply a number of sampling point
	}
	m_voltage5 = answer; //displat power for one cycle
	m_frequency *= 1000;
	// answer
	answer *= m_frequency;
	m_power = answer;
	m_frequency *= 1;
	////////////////////
	// PROCEDURE  END //
	////////////////////
	
	m_voltage = max1;
	m_voltage2 = max2; //输出峰值
	m_voltage3 = 2 * max2; //输出峰峰值
	m_voltage4 = 2 * max1;
	
	return answer;
}

void CVCDlg::CopyData() //Save data from DSO-2090
{
	for (int i = 0; i < 32780; i++)
	{
		Data1[i] = Ch1.HardwareData[i];
		Data2[i] = Ch2.HardwareData[i];

	}
}

double CVCDlg::GetVoltageDiv(int sel) //unit charge quantity
{
	double ch_div;
	switch (sel) {
	case 8:
		ch_div = 5;
		break;
	case 7:
		ch_div = 2;
		break;
	case 6:
		ch_div = 1;
		break;
	case 5:
		ch_div = 0.5;
		break;
	case 4:
		ch_div = 0.2;
		break;
	case 3:
		ch_div = 0.1;
		break;
	case 2:
		ch_div = 0.05;
		break;
	case 1:
		ch_div = 0.02;
		break;
	case 0:
		ch_div = 0.01;
		break;
	}
	return ch_div;
}


//DEL void CVCDlg::OnButtonCal() //画图  useless
//DEL {
//DEL 	// TODO: Add your control notification handler code here
//DEL 	// Span
//DEL 	CString str;
//DEL 	CEdit *pEdits = (CEdit*)GetDlgItem(IDC_EDIT_SPAN);
//DEL 	pEdits->GetWindowText(str);
//DEL 	m_span = atoi((const char *)str);
//DEL 
//DEL 	m_power = CalculatePower();
//DEL 	UpdateData(false);
//DEL }

void CVCDlg::OnSelchangeComboCUnit() //调节电容大小
{
	// TODO: Add your control notification handler code here
	CComboBox *pCbo =(CComboBox*) GetDlgItem(IDC_COMBO_C_UNIT);
	int sel = pCbo->GetCurSel();
	if (sel == 0) {
		Unit = 1000000;
	}
	else if (sel == 1) {
		Unit = 1000000000;
	}
	else if (sel == 2) {
		Unit = 1000;
	}
	
}

//DEL void CVCDlg::OnButtonOutput() //输出李萨如图形  useless
//DEL {
//DEL 	// TODO: Add your control notification handler code here
//DEL 	ofstream Q_s("Q_smoothed.txt", ios::out);
//DEL 	Q_s<<"Unit: nC"<<endl;
//DEL 	if (Time == 0)
//DEL 	{
//DEL 		Q_s<<"Time interval:"<<Time_saved_1<<endl;
//DEL 	}
//DEL 	else
//DEL 	{
//DEL 		Q_s<<"Time interval:"<<Time<<endl;
//DEL 	}
//DEL 	for (int i = 0; i < 32780; i++)
//DEL 	{
//DEL 		if (Data1_b[i] != 0)
//DEL 		{
//DEL 			Q_s<<Data1_b[i] * Capacitance * 100000000<<endl;
//DEL 		}
//DEL 	}
//DEL 	Q_s.close();
//DEL 
//DEL 	ofstream V_s("V_smoothed.txt", ios::out);
//DEL 	V_s<<"Unit: kV"<<endl;
//DEL 	if (Time == 0)
//DEL 	{
//DEL 		V_s<<"Time interval:"<<Time_saved_2<<endl;
//DEL 	}
//DEL 	else
//DEL 	{
//DEL 		V_s<<"Time interval:"<<Time<<endl;
//DEL 	}
//DEL 	
//DEL 	for (int j = 0; j < 32780; j++)
//DEL 	{
//DEL 		if (Data2_b[j] != 0)
//DEL 		{
//DEL 			V_s<<Data2_b[j]<<endl;
//DEL 		}
//DEL 	}
//DEL 	V_s.close();
//DEL 
//DEL 
//DEL 	ofstream Q("Q.txt", ios::out);
//DEL 	Q<<"Unit: nC"<<endl;
//DEL 	if (Time == 0)
//DEL 	{
//DEL 		Q<<"Time interval:"<<Time_saved_1<<endl;
//DEL 	}
//DEL 	else
//DEL 	{
//DEL 		Q<<"Time interval:"<<Time<<endl;
//DEL 	}
//DEL 	for (int p = 0; p < 32780; p++)
//DEL 	{
//DEL 		if (Data1_c[p] != 0)
//DEL 		{
//DEL 			Q<<Data1_c[p] * Capacitance * 100000000<<endl;
//DEL 		}
//DEL 	}
//DEL 	Q.close();
//DEL 
//DEL 	ofstream V("V.txt", ios::out);
//DEL 	V<<"Unit: kV"<<endl;
//DEL 	if (Time == 0)
//DEL 	{
//DEL 		V<<"Time interval:"<<Time_saved_2<<endl;
//DEL 	}
//DEL 	else
//DEL 	{
//DEL 		V<<"Time interval:"<<Time<<endl;
//DEL 	}
//DEL 	
//DEL 	for (int q = 0; q < 32780; q++)
//DEL 	{
//DEL 		if (Data2_c[q] != 0)
//DEL 		{
//DEL 			V<<Data2_c[q]<<endl;
//DEL 		}
//DEL 	}
//DEL 	V.close();
//DEL }

//DEL void CVCDlg::OnSubpanel() 
//DEL {
//DEL 	// TODO: Add your control notification handler code here
//DEL 	
//DEL }
/*
void CVCDlg::OnButtonPlot() 
{
	// TODO: Add your control notification handler code here
	//m_Chart2d.Create(WS_CHILD|WS_VISIBLE,Rect,this,IDC_SUBPANEL);
	for ( int i = 0 ; i < 100 ; i++)
	{
		m_Chart2d.SetXYValue((double)i * 100,(double)i,i,0);
	}
	m_Chart2d.Invalidate();
}

*/

void CVCDlg::OnButtonApplyrange() //调节坐标尺寸
{
	// TODO: Add your control notification handler code here
	CString str;
	CEdit *pEditx = (CEdit*)GetDlgItem(IDC_EDIT_XRANGE);
	pEditx->GetWindowText(str);
	m_xrange = atof((const char *)str);
	CEdit *pEdity = (CEdit*)GetDlgItem(IDC_EDIT_YRANGE);
	pEdity->GetWindowText(str);
	m_yrange = atof((const char *)str);
	m_Chart2d.SetRange(-1 * m_xrange, m_xrange,-1 * m_yrange, m_yrange);
	m_Chart2d.Invalidate(FALSE);

	if (StartMonitor == 1)
	{
		CString str2;
	    CEdit *pEdit2 = (CEdit*)GetDlgItem(IDC_EDIT_SPAN);
	    pEdit2->GetWindowText(str2);
	    span = atoi((const char *)str2); //read smooth number
	}
	else if (StartMonitor == 0)
	{
		CString str2;
	    CEdit *pEdit2 = (CEdit*)GetDlgItem(IDC_EDIT_SPAN);
	    pEdit2->GetWindowText(str2);
	    span = atoi((const char *)str2); //read smooth number
		CalculatePower();

	}
	
}

class CHelpDialog : public CDialog
{
public:
	enum { IDD = IDD_HELPBOX };

	CHelpDialog();
};

CHelpDialog::CHelpDialog()
	: CDialog(CHelpDialog::IDD, NULL)
{
}


//DEL void CVCDlg::OnButtonHelp() //useless code
//DEL {
//DEL 	// TODO: Add your control notification handler code here
//DEL 	CHelpDialog *Floater = new CHelpDialog;
//DEL 	Floater->Create(IDD_HELPBOX, this);
//DEL 	Floater->ShowWindow(SW_SHOW);
//DEL }




void CVCDlg::OnButton1() //减半屏幕大小键
{
	// TODO: Add your control notification handler code here
	CString str;
    if(GetDlgItemText(IDC_BUTTON1,str), str == "Striction<<")
	{
		SetDlgItemText(IDC_BUTTON1, "Expend>>");
	}
	else
	{
		SetDlgItemText(IDC_BUTTON1, "Striction<<");
	}

	static CRect rectLarge;  //保存还原后的尺寸（静态）
	static CRect rectSmall;  
 
	if(rectLarge.IsRectNull())
	{
		CRect rectSeparator;
		GetWindowRect(&rectLarge);
		GetDlgItem(IDC_SEPARATOR)->GetWindowRect(&rectSeparator);

		rectSmall.left = rectLarge.left;
		rectSmall.top = rectLarge.top;
        rectSmall.right = rectSeparator.right;  //左下角横坐标改变
		rectSmall.bottom = rectLarge.bottom;
	}
	if(str == "Striction<<")
	{
		SetWindowPos(NULL, 0,0, rectSmall.Width(), rectSmall.Height(), SWP_NOMOVE | SWP_NOZORDER);
	}
	else
	{
        SetWindowPos(NULL, 0,0, rectLarge.Width(), rectLarge.Height(), SWP_NOMOVE | SWP_NOZORDER);
	}
}


void CVCDlg::OnButton2() //变换 q - u 横纵坐标 //已经删除
{
	CString str="";
	str.Format("%d", xx123);
	SetDlgItemText(IDC_STATIC13131, str);
	xx123 = xx123 + 1;
	if(xx123==2){
		for(int i=0; i<=5; i++){
			if(i%2==0){
				m_Chart2d_voltage.SetXYValue(i*5, 20, i, 0);
			}else{
				m_Chart2d_voltage.SetXYValue(i*5, 40, i, 0);
			}
		}
		m_Chart2d_voltage.Invalidate();
		SetDlgItemText(IDC_STATIC13131,"2");
	}
	if(xx123 == 3){
		for(int i=5; i<=10; i++){
			if(i%2==0){
				m_Chart2d_voltage.SetXYValue(i*5, 20, i, 0);
			}else{
				m_Chart2d_voltage.SetXYValue(i*5, 40, i, 0);
			}
		}
		m_Chart2d_voltage.Invalidate();
		SetDlgItemText(IDC_STATIC13131,"3");
	}
}

void CVCDlg::OnAbout() //open about box
{
	// TODO: Add your command handler code here
	CHelpDialog *Floater = new CHelpDialog;
	Floater->Create(IDD_ABOUTBOX, this);
	Floater->ShowWindow(SW_SHOW);
}

void CVCDlg::OnHelp() //open help box
{
	// TODO: Add your command handler code here
	CHelpDialog *Floater = new CHelpDialog;
	Floater->Create(IDD_HELPBOX, this);
	Floater->ShowWindow(SW_SHOW);
}

void CVCDlg::OnLoadData() //load data
{
	CString str1;
	CFileDialog FileDlg1(TRUE," ","ch1.txt", NULL, "TXT File(*.txt)|*.txt|All(*.*)|*.*|");
	if(FileDlg1.DoModal()==IDOK)
	{
		str1=FileDlg1.GetPathName();
		SetDlgItemText(IDM_LOAD_DATA, str1);
		AfxMessageBox("CH1 loaded.");
	}
	else
	{
		AfxMessageBox("Failed.");
	}

	// Read data to Data1 from ch1.txt
	ifstream Data_ch1("ch1.txt", ios::in);
	Data_ch1>>Time_saved_1;
	Data_ch1>>Ch1.Voltage;
	for (int i = 0; i < 32780; i++)
	{
		Data_ch1>>Data1[i];
	}
	Data_ch1.close();

	CString str2;
	CFileDialog FileDlg2(TRUE," ","ch2.txt", NULL, "TXT File(*.txt)|*.txt|All(*.*)|*.*|");
	if(FileDlg2.DoModal()==IDOK)
	{
		str2=FileDlg2.GetPathName();
		SetDlgItemText(IDM_LOAD_DATA, str2);
		AfxMessageBox("CH2 loaded.");
	}
	else
	{
		AfxMessageBox("Failed.");
	}
	// Read data to Data2 from ch2.txt
	ifstream Data_ch2("ch2.txt", ios::in);
	Data_ch2>>Time_saved_2;
	Data_ch2>>Ch2.Voltage;
	for (int j = 0; j < 32780; j++)
	{
		Data_ch2>>Data2[j];
	}
	Data_ch2.close();
}

void CVCDlg::OnSaveData() //save data
{
	// TODO: Add your command handler code here
	
	CString str1;
	CFileDialog   FileDlg1(FALSE," ","ch1.txt",OFN_FILEMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT , "TXT File(*.txt)|*.txt|All(*.*)|*.*|");
	if(FileDlg1.DoModal()==IDOK)
	{
		ofstream ofs(FileDlg1.GetPathName());
		ofs.write(str1,str1.GetLength());
		ofs.close();
		AfxMessageBox("CH1 Data Saved!");
	}
	
	ofstream Data_ch1("ch1.txt", ios::out);
	if (Time == 0)
	{
		Data_ch1<<Time_saved_1<<endl;
	}
	else
	{
		Data_ch1<<Time<<endl;
	}
	Data_ch1<<Ch1.Voltage<<endl;
	for (int i = 0; i < 32780; i++)
	{

		Data_ch1<<Data1_HardWareData[i]<<" "; 
	}
	Data_ch1.close();


	CString str2;
	CFileDialog   FileDlg2(FALSE," ","ch2.txt",OFN_FILEMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT , "TXT File(*.txt)|*.txt|All(*.*)|*.*|");
	if(FileDlg2.DoModal()==IDOK)
	{
		ofstream ofs(FileDlg2.GetPathName());
		ofs.write(str2,str2.GetLength());
		ofs.close();
		AfxMessageBox("CH2 Data Saved!");
	}
	ofstream Data_ch2("ch2.txt", ios::out);
	if (Time == 0)
	{
		Data_ch2<<Time_saved_1<<endl;
	}
	else
	{
		Data_ch2<<Time<<endl;
	}
	Data_ch2<<Ch2.Voltage<<endl;
	for (int j = 0; j < 32780; j++)
	{

		Data_ch2<<Data2_HardWareData[j]<<" ";
	}
	Data_ch2.close();

	CString str3;
	CFileDialog   FileDlg3(FALSE," ","data.csv",OFN_FILEMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT , "TXT File(*.txt)|*.txt|All(*.*)|*.*|");
	if(FileDlg3.DoModal()==IDOK)
	{
		ofstream ofs(FileDlg3.GetPathName());
		ofs.write(str3,str3.GetLength());
		ofs.close();
		AfxMessageBox("Data file Saved!");
	}
	ofstream Data_ch3("data.csv", ios::out);

	Data_ch3<<"#CLOCK=0.000040000"<<endl;
	Data_ch3<<"#size=32780"<<endl;
	Data_ch3<<"time"<<"   "<<"ch1"<<"   "<<"ch2"<<endl;
	//Data_ch3<<Ch1.Voltage<<" "<<Ch2.Voltage<<endl;
	
	for (int k = 0; k < 32780; k++)
	{
		Data_ch3<<setprecision(5)<<fixed<<k * Time<<", ";
		Data_ch3<<Data1_HardWareData[k]<<", "<<Data2_HardWareData[k]<<endl; 
	}
	Data_ch3.close();
}

void CVCDlg::OnPlotLissajous() //draw lissjous
{
	// TODO: Add your command handler code here
	CString str;
	CEdit *pEdits = (CEdit*)GetDlgItem(IDC_EDIT_SPAN);
	pEdits->GetWindowText(str);
	m_span = atoi((const char *)str);

	m_power = CalculatePower();
	UpdateData(false);
}

void CVCDlg::OnOutputLissajous() //output lissajous
{
	// TODO: Add your command handler code here
	ofstream Q_s("Q_smoothed.txt", ios::out);
	Q_s<<"Unit: nC"<<endl;
	if (Time == 0)
	{
		Q_s<<"Time interval:"<<Time_saved_1<<endl;
	}
	else
	{
		Q_s<<"Time interval:"<<Time<<endl;
	}
	for (int i = 0; i < 32780; i++)
	{
		if (Data1_b[i] != 0)
		{
			Q_s<<Data1_c[i] * Capacitance * 100000000<<endl;
		}
	}
	Q_s.close();

	ofstream V_s("V_smoothed.txt", ios::out);
	V_s<<"Unit: kV"<<endl;
	if (Time == 0)
	{
		V_s<<"Time interval:"<<Time_saved_2<<endl;
	}
	else
	{
		V_s<<"Time interval:"<<Time<<endl;
	}
	
	for (int j = 0; j < 32780; j++)
	{
		if (Data2_b[j] != 0)
		{
			V_s<<Data2_c[j]<<endl;
		}
	}
	V_s.close();


	ofstream Q("Q.txt", ios::out);
	Q<<"Unit: nC"<<endl;
	if (Time == 0)
	{
		Q<<"Time interval:"<<Time_saved_1<<endl;
	}
	else
	{
		Q<<"Time interval:"<<Time<<endl;
	}
	for (int p = 0; p < 32780; p++)
	{
		if (Data1_c[p] != 0)
		{
			Q<<Data1_c[p] * Capacitance * 100000000<<endl;
		}
	}
	Q.close();

	ofstream V("V.txt", ios::out);
	V<<"Unit: kV"<<endl;
	if (Time == 0)
	{
		V<<"Time interval:"<<Time_saved_2<<endl;
	}
	else
	{
		V<<"Time interval:"<<Time<<endl;
	}
	
	for (int q = 0; q < 32780; q++)
	{
		if (Data2_c[q] != 0)
		{
			V<<Data2_c[q]<<endl;
		}
	}
	V.close();
}

void CVCDlg::OnCustomdrawSlider5(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	int nPos = m_ctrlSlider.GetPos(); //获得滑块的当前位置
   //另外做一个编辑框 显示所调节的数据；
	CString str="";
	str.Format("%f",nPos/10.0);
	m_Chart2d.SetRange(-10,10,-nPos/10.0,nPos/10.0);
	SetDlgItemText(IDC_STATIC13131,str);
	*pResult = 0;
	m_Chart2d.Invalidate();
}

void CVCDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	/*
	// TODO: Add your message handler code here
	if (m_listRect.GetCount() > 0)
	{
		CRect dlgNow;
		GetWindowRect(&dlgNow);
		POSITION pos = m_listRect.GetHeadPosition();//第一个保存的是对话框的Rect

		CRect dlgSaved;
		dlgSaved = m_listRect.GetNext(pos);
		ScreenToClient(dlgNow);

		float x = dlgNow.Width() * 1.0 / dlgSaved.Width();//根据当前和之前保存的对话框的宽高求比例
		float y = dlgNow.Height()  * 1.0/ dlgSaved.Height();
		ClientToScreen(dlgNow);

		CRect childSaved;

		CWnd* pWnd = GetWindow(GW_CHILD);
		int index = m_listRect.GetCount();
		while(pWnd && index>=2)
		{
			childSaved = m_listRect.GetNext(pos);//依次获取子窗体的Rect
			childSaved.left = dlgNow.left + (childSaved.left - dlgSaved.left)*x;//根据比例调整控件上下左右距离对话框的距离
			childSaved.right = dlgNow.right + (childSaved.right - dlgSaved.right)*x;
			childSaved.top = dlgNow.top + (childSaved.top - dlgSaved.top)*y;
			childSaved.bottom = dlgNow.bottom + (childSaved.bottom - dlgSaved.bottom)*y;
			ScreenToClient(childSaved);
			pWnd->MoveWindow(childSaved);
			pWnd = pWnd->GetNextWindow();
			index--;
		}
		CRect rc;
		GetDlgItem(IDC_SUBPANEL)->GetWindowRect(&rc);
		ScreenToClient(rc);
		m_Chart2d.DestroyWindow();
		m_Chart2d.Create(WS_CHILD|WS_VISIBLE,rc,this,IDC_SUBPANEL);

		CRect rc1;
		GetDlgItem(IDC_SUBPANEL2)->GetWindowRect(&rc1);
		ScreenToClient(rc1);
		m_Chart2d_voltage.DestroyWindow();
		m_Chart2d_voltage.Create(WS_CHILD|WS_VISIBLE,rc1,this,IDC_SUBPANEL2);
	}
	*/
}
