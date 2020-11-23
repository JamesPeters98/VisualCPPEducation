
// Sketch App.h : main header file for the Sketch App application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CSketchApp:
// See Sketch App.cpp for the implementation of this class
//

class CSketchApp : public CWinApp
{
public:
	CSketchApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CSketchApp theApp;
