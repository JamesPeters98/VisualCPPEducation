#include "CMfcApp.h"

#include "CMfcWindow.h"

CMfcApp app;

BOOL CMfcApp::InitInstance()
{
	m_pMainWnd = new CMfcWindow;
	m_pMainWnd->ShowWindow(m_nCmdShow);
	return TRUE;
}
