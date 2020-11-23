
// Sketch AppView.cpp : implementation of the CSketchAppView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Sketch App.h"
#endif

#include "Sketch AppDoc.h"
#include "Sketch AppView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSketchAppView

IMPLEMENT_DYNCREATE(CSketchAppView, CView)

BEGIN_MESSAGE_MAP(CSketchAppView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CSketchAppView construction/destruction

CSketchAppView::CSketchAppView() noexcept
{
	// TODO: add construction code here

}

CSketchAppView::~CSketchAppView()
{
}

BOOL CSketchAppView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CSketchAppView drawing

void CSketchAppView::OnDraw(CDC* /*pDC*/)
{
	CSketchAppDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CSketchAppView printing

BOOL CSketchAppView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CSketchAppView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CSketchAppView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CSketchAppView diagnostics

#ifdef _DEBUG
void CSketchAppView::AssertValid() const
{
	CView::AssertValid();
}

void CSketchAppView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSketchAppDoc* CSketchAppView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSketchAppDoc)));
	return (CSketchAppDoc*)m_pDocument;
}
#endif //_DEBUG


// CSketchAppView message handlers
