#pragma once


// CPenDialog dialog

class CPenDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CPenDialog)

public:
	CPenDialog(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CPenDialog();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PENWIDTH_DLG };
#endif

	int m_penWidth;		// Record the current pen width
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
