
// Ex1_03View.cpp : implementation of the CEx103View class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Ex1_03.h"
#endif

#include "Ex1_03Doc.h"
#include "Ex1_03View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEx103View

IMPLEMENT_DYNCREATE(CEx103View, CView)

BEGIN_MESSAGE_MAP(CEx103View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CEx103View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CEx103View construction/destruction

CEx103View::CEx103View() noexcept
{
	// TODO: add construction code here

}

CEx103View::~CEx103View()
{
}

BOOL CEx103View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CEx103View drawing

void CEx103View::OnDraw(CDC* /*pDC*/)
{
	CEx103Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CEx103View printing


void CEx103View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CEx103View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CEx103View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CEx103View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CEx103View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CEx103View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CEx103View diagnostics

#ifdef _DEBUG
void CEx103View::AssertValid() const
{
	CView::AssertValid();
}

void CEx103View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CEx103Doc* CEx103View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx103Doc)));
	return (CEx103Doc*)m_pDocument;
}
#endif //_DEBUG


// CEx103View message handlers
