
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
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
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

void CSketchAppView::OnDraw(CDC* pDC)
{
	CSketchAppDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// Draw the sketch
	for (auto iter = pDoc->begin(); iter != pDoc->end(); ++iter)
		for (const auto& pElement : *pDoc)
		{
			if (pDC->RectVisible(pElement->GetEnclosingRect()))
				pElement->Draw(pDC);
		}
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


void CSketchAppView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// Record current position as starting pos.
	m_FirstPoint = point;
	SetCapture();
}


void CSketchAppView::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (this == GetCapture())
		ReleaseCapture();
	
	// Make sure there is an element
	if (m_pTempElement)
	{
		// Add the element pointer to the sketch
		GetDocument()->AddElement(m_pTempElement);
		InvalidateRect(&m_pTempElement->GetEnclosingRect());
		m_pTempElement.reset(); // Reset the element pointer
	}
}


void CSketchAppView::OnMouseMove(UINT nFlags, CPoint point)
{
	// Define a Device Context object for the view
	CClientDC aDC{ this }; // DC is for this view
	if ((nFlags & MK_LBUTTON) && (this == GetCapture())) // Verify the left button is down
	{
		m_SecondPoint = point; // Save the current cursor position
		if (m_pTempElement)
		{
			// An element was created previously
			if (ElementType::CURVE == GetDocument()->GetElementType()) // A curve?
			{ // We are drawing a curve so add a segment to the existing curve
				std::dynamic_pointer_cast<CCurve>(m_pTempElement)->AddSegment(m_SecondPoint);
				m_pTempElement->Draw(&aDC); // Now draw it
				return; // We are done
			}
			else
			{
				// If we get to here it's not a curve so
				// redraw the old element so it disappears from the view
				aDC.SetROP2(R2_NOTXORPEN); // Set the drawing mode
				m_pTempElement->Draw(&aDC); // Redraw the old element to erase it
			}
		}
		// Create a temporary element of the type and color that
		// is recorded in the document object, and draw it
		m_pTempElement = CreateElement();
		m_pTempElement->Draw(&aDC);
	}
}

std::shared_ptr<CElement> CSketchAppView::CreateElement() const
{
	// Get a pointer to the document for this view
	CSketchAppDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc); // Verify the pointer is good

	// Get the current element color
	COLORREF color{ static_cast<COLORREF>(pDoc->GetElementColor()) };
	int penStyle{ pDoc->GetPenStyle() };
	// Now select the element using the type stored in the document
	switch (pDoc->GetElementType())
	{
	case ElementType::RECTANGLE:
		return std::make_shared<CRectangle>(m_FirstPoint, m_SecondPoint, color, penStyle);

	case ElementType::CIRCLE:
		return std::make_shared<CCircle>(m_FirstPoint, m_SecondPoint, color, penStyle);

	case ElementType::CURVE:
		return std::make_shared<CCurve>(m_FirstPoint, m_SecondPoint, color, penStyle);

	case ElementType::LINE:
		return std::make_shared<CLine>(m_FirstPoint, m_SecondPoint, color, penStyle);

	case ElementType::ELLIPSE:
		return std::make_shared<CEllipse>(m_FirstPoint, m_SecondPoint, color, penStyle);

	default:
		// Something's gone wrong
		AfxMessageBox(_T("Bad Element code"), MB_OK);
		AfxAbort();
		return nullptr;
	}
}

