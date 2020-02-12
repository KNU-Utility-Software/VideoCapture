// Movie_OpenCVDlg.h : header file
//

#include <opencv2\core\types_c.h>

#if !defined(AFX_MOVIE_OPENCVDLG_H__8F305B7E_1D45_4340_9AC8_F1E158F40F92__INCLUDED_)
#define AFX_MOVIE_OPENCVDLG_H__8F305B7E_1D45_4340_9AC8_F1E158F40F92__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMovie_OpenCVDlg dialog

class CMovie_OpenCVDlg : public CDialog
{
// Construction
public:
	CDC* pDC;
	CWnd* pWnd;

	CvCapture* m_capture;
	IplImage* m_Image;
	IplImage* temp;
	IplImage* gray_img;

	//CvvImage m_cvvImage;
	
	CRect display_rect;

	int movie_width;
	int movie_height;
	int movie_fps;
	int movie_frames;

	int mode;

	CMovie_OpenCVDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMovie_OpenCVDlg)
	enum { IDD = IDD_MOVIE_OPENCV_DIALOG };
	CSliderCtrl	m_SliderBar;
	CStatic	m_display;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMovie_OpenCVDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMovie_OpenCVDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnFileOpen();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDestroy();
	afx_msg void OnCannyEdge();
	afx_msg void OnSobelEdge();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MOVIE_OPENCVDLG_H__8F305B7E_1D45_4340_9AC8_F1E158F40F92__INCLUDED_)
