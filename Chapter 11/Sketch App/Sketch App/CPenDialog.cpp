// CPenDialog.cpp : implementation file
//

#include "pch.h"
#include "Sketch App.h"
#include "CPenDialog.h"
#include "afxdialogex.h"


// CPenDialog dialog

IMPLEMENT_DYNAMIC(CPenDialog, CDialogEx)

CPenDialog::CPenDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PENWIDTH_DLG, pParent), m_penWidth{}
{

}

CPenDialog::~CPenDialog()
{
}

void CPenDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPenDialog, CDialogEx)
END_MESSAGE_MAP()


// CPenDialog message handlers
