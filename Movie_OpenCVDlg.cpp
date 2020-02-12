// Movie_OpenCVDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Movie_OpenCV.h"
#include "Movie_OpenCVDlg.h"
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/videoio/videoio_c.h>

//#include <opencv2\core\core_c.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About
CMovie_OpenCVDlg* pDlg;

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
// CMovie_OpenCVDlg dialog

CMovie_OpenCVDlg::CMovie_OpenCVDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMovie_OpenCVDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMovie_OpenCVDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	movie_width=0;
	movie_height=0;
	movie_fps=0;
	movie_frames=0;

	mode = 0;

	m_capture = NULL;
	m_Image = NULL;
	gray_img = NULL;
	temp = NULL;
}

void CMovie_OpenCVDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMovie_OpenCVDlg)
	DDX_Control(pDX, IDC_SLIDER1, m_SliderBar);
	DDX_Control(pDX, IDC_PICTURE, m_display);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMovie_OpenCVDlg, CDialog)
	//{{AFX_MSG_MAP(CMovie_OpenCVDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_FILE_OPEN, OnFileOpen)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMovie_OpenCVDlg message handlers

BOOL CMovie_OpenCVDlg::OnInitDialog()
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
	
	// TODO: Add extra initialization here
	pDlg = this;

	pWnd = (CWnd*)GetDlgItem(IDC_PICTURE);
	pWnd->MoveWindow(25, 20, 320, 240);

	pWnd = (CWnd*)GetDlgItem(IDC_STATIC_MOVIE);
	pWnd->MoveWindow(10, 5, 355, 300);

	m_SliderBar.MoveWindow(15, 270, 340, 30);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMovie_OpenCVDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMovie_OpenCVDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
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
HCURSOR CMovie_OpenCVDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CMovie_OpenCVDlg::OnFileOpen() 
{
	// TODO: Add your control notification handler code here
	
	double timer_set=0;
	CString strPathName;
	
	char szFilter[] = "movie (*.avi) | *.avi; | All Files(*.*)|*.*||";
	
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, szFilter);
	if(IDOK == dlg.DoModal())
	{
		strPathName = dlg.GetPathName();
	}

	m_capture = cvCaptureFromFile(strPathName);
	movie_width = (int)cvGetCaptureProperty(m_capture, CV_CAP_PROP_FRAME_WIDTH);
	movie_height = (int)cvGetCaptureProperty(m_capture, CV_CAP_PROP_FRAME_HEIGHT);
	movie_fps = (int)cvGetCaptureProperty(m_capture, CV_CAP_PROP_FPS);
	movie_frames = (int)cvGetCaptureProperty(m_capture, CV_CAP_PROP_FRAME_COUNT);
	
	pDC = m_display.GetDC();
	m_display.GetClientRect(&display_rect);

	m_Image = cvCreateImage(cvSize(movie_width, movie_height), IPL_DEPTH_8U, 3);
	gray_img = cvCreateImage(cvSize(movie_width, movie_height), IPL_DEPTH_8U, 1);
	temp = cvCreateImage(cvSize(movie_width, movie_height), IPL_DEPTH_8U, 1);
	
	timer_set = 1.0/movie_fps;
	m_SliderBar.SetRange(0, movie_frames);
	SetTimer(0, (int)(timer_set*1000), NULL);

	UpdateData(FALSE);
}

void CMovie_OpenCVDlg::OnTimer(UINT nIDEvent) 
{
	//// TODO: Add your message handler code here and/or call default
	//if(nIDEvent == 0)
	//{
	//	if(cvGrabFrame(m_capture))
	//	{	
	//		m_Image = cvRetrieveFrame(m_capture);

	//		m_cvvImage.CopyOf(m_Image);

	//		pDlg->m_SliderBar.SetPos((int)cvGetCaptureProperty(pDlg->m_capture, CV_CAP_PROP_POS_FRAMES));
	//		m_cvvImage.DrawToHDC(pDC->GetSafeHdc(), &display_rect);
	//	}
	//}

	//UpdateData(FALSE);

	//m_Image = NULL;
	//cvReleaseImage(&m_Image);
	
	CDialog::OnTimer(nIDEvent);
}

void CMovie_OpenCVDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	if (m_capture)
	{
		cvReleaseCapture(&m_capture);
	}
}

void CMovie_OpenCVDlg::OnCannyEdge() 
{
	// TODO: Add your control notification handler code here
	mode = MODE_CANNY_EDGE;
}

void CMovie_OpenCVDlg::OnSobelEdge() 
{
	// TODO: Add your control notification handler code here
	mode = MODE_SOBEL_EDGE;
}
