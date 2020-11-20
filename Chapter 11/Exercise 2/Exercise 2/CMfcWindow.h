#pragma once
#include <afxwin.h>
class CMfcWindow : public CFrameWnd
{
public:
	CMfcWindow()
	{
		Create(nullptr, _T("Basic MFC Application"));
	}
};

