// Movie_OpenCV.h : main header file for the MOVIE_OPENCV application
//

#if !defined(AFX_MOVIE_OPENCV_H__9421A146_69A0_4C6D_B1EB_077FD67073EA__INCLUDED_)
#define AFX_MOVIE_OPENCV_H__9421A146_69A0_4C6D_B1EB_077FD67073EA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMovie_OpenCVApp:
// See Movie_OpenCV.cpp for the implementation of this class
//

class CMovie_OpenCVApp : public CWinApp
{
public:
	CMovie_OpenCVApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMovie_OpenCVApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMovie_OpenCVApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MOVIE_OPENCV_H__9421A146_69A0_4C6D_B1EB_077FD67073EA__INCLUDED_)
