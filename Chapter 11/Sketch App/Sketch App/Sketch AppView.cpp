
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

IMPLEMENT_DYNCREATE(CSketchAppView, CScrollView)

BEGIN_MESSAGE_MAP(CSketchAppView, CScrollView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_ELEMENT_DELETE, &CSketchAppView::OnElementDelete)
	ON_COMMAND(ID_ELEMENT_MOVE, &CSketchAppView::OnElementMove)
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_ELEMENT_SENDTOBACK, &CSketchAppView::OnElementSendtoback)
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
				pElement->Draw(pDC, m_pSelected);
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
	CClientDC aDC{ this }; // Create a device context
	OnPrepareDC(&aDC); // Get origin adjusted
	aDC.DPtoLP(&point); // Convert point to logical coordinates

	if (m_MoveMode)
	{
		// In moving mode, so drop the element
		m_MoveMode = false; // Kill move mode
		auto pElement(m_pSelected); // Store selected address
		m_pSelected.reset(); // De-select the element
		GetDocument()->UpdateAllViews(nullptr, 0,pElement.get()); // Redraw all the views
	}
	else
	{
		// Record current position as starting pos.
		m_FirstPoint = point;
		SetCapture();
	}
}


void CSketchAppView::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (this == GetCapture())
		ReleaseCapture();
	
	// Make sure there is an element
	if (m_pTempElement)
	{
		CRect aRect{ m_pTempElement->GetEnclosingRect() }; // Get enclosing rectangle

		GetDocument()->AddElement(m_pTempElement); // Add element pointer to sketch

		CClientDC aDC{ this }; // Create a device context
		OnPrepareDC(&aDC); // Get origin adjusted
		aDC.LPtoDP(aRect); // Convert to client coordinates
		InvalidateRect(aRect); // Get the area redrawn
		m_pTempElement.reset(); // Reset the element pointer
	}
}


void CSketchAppView::OnMouseMove(UINT nFlags, CPoint point)
{
	// Define a Device Context object for the view
	CClientDC aDC{ this }; // DC is for this view
	OnPrepareDC(&aDC); // Get origin adjusted
	aDC.DPtoLP(&point); // Convert point to logical coordinates

	if (m_MoveMode)
	{
		MoveElement(aDC, point);
	}
	else if ((nFlags & MK_LBUTTON) && (this == GetCapture())) // Verify the left button is down
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
	else
	{
		auto pOldSelected = m_pSelected;
		m_pSelected = GetDocument()->FindElement(point);
		if (m_pSelected != pOldSelected)
		{
			if (m_pSelected)
				GetDocument()->UpdateAllViews(nullptr, 0, m_pSelected.get());
			if (pOldSelected)
				GetDocument()->UpdateAllViews(nullptr, 0, pOldSelected.get());
		}
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

void CSketchAppView::MoveElement(CClientDC& aDC, const CPoint& point)
{
	CSize distance{ point - m_CursorPos };
	m_CursorPos = point;

	if(m_pSelected)
	{
		CSketchAppDoc* pDoc{ GetDocument() };

		pDoc->UpdateAllViews(this, 0L, m_pSelected.get());
		
		aDC.SetROP2(R2_NOTXORPEN);
		m_pSelected->Draw(&aDC, m_pSelected);
		m_pSelected->Move(distance);
		m_pSelected->Draw(&aDC, m_pSelected);

		pDoc->UpdateAllViews(this, 0L, m_pSelected.get());
	}
}


void CSketchAppView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	// Invalidate the area corresponding to the element pointed to
	// by the third argument, otherwise invalidate the whole client area
	if (pHint)
	{
		CClientDC aDC{ this }; // Create a device context
		OnPrepareDC(&aDC); // Get origin adjusted
		// Get the enclosing rectangle and convert to client coordinates
		CRect aRect{ dynamic_cast<CElement*>(pHint)->GetEnclosingRect() };
		aDC.LPtoDP(aRect);
		InvalidateRect(aRect); // Get the area redrawn
	}
	else
	{
		InvalidateRect(nullptr);
	}
}


void CSketchAppView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize DocSize{ 3000, 3000 };

	SetScrollSizes(MM_LOENGLISH, DocSize); // Set mapping mode and document size
	// SetScrollSizes(MM_TEXT, DocSize, CSize{ 500, 500 }, CSize{ 20, 20 });
}


void CSketchAppView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CMenu menu;
	menu.LoadMenu(IDR_CONTEXT_MENU);              // Load the context menu 
	CMenu* pContext{};
	if (m_pSelected)
	{
		pContext = menu.GetSubMenu(0);
	}
	else
	{
		pContext = menu.GetSubMenu(1);
		// Check color menu items
		ElementColour color{ GetDocument()->GetElementColor() };
		menu.CheckMenuItem(ID_COLOUR_BLACK,
			(ElementColour::BLACK == color ? MF_CHECKED : MF_UNCHECKED) | MF_BYCOMMAND);
		menu.CheckMenuItem(ID_COLOUR_RED,
			(ElementColour::RED == color ? MF_CHECKED : MF_UNCHECKED) | MF_BYCOMMAND);
		menu.CheckMenuItem(ID_COLOUR_GREEN,
			(ElementColour::GREEN == color ? MF_CHECKED : MF_UNCHECKED) | MF_BYCOMMAND);
		menu.CheckMenuItem(ID_COLOUR_BLUE,
			(ElementColour::BLUE == color ? MF_CHECKED : MF_UNCHECKED) | MF_BYCOMMAND);
		// Check element menu items
		ElementType type{ GetDocument()->GetElementType() };
		menu.CheckMenuItem(ID_ELEMENT_LINE,
			(ElementType::LINE == type ? MF_CHECKED : MF_UNCHECKED) | MF_BYCOMMAND);
		menu.CheckMenuItem(ID_ELEMENT_RECTANGLE,
			(ElementType::RECTANGLE == type ? MF_CHECKED : MF_UNCHECKED) | MF_BYCOMMAND);
		menu.CheckMenuItem(ID_ELEMENT_CIRCLE,
			(ElementType::CIRCLE == type ? MF_CHECKED : MF_UNCHECKED) | MF_BYCOMMAND);
		menu.CheckMenuItem(ID_ELEMENT_CURVE,
			(ElementType::CURVE == type ? MF_CHECKED : MF_UNCHECKED) | MF_BYCOMMAND);
		menu.CheckMenuItem(ID_ELEMENT_ELLIPSE,
			(ElementType::ELLIPSE == type ? MF_CHECKED : MF_UNCHECKED) | MF_BYCOMMAND);
	}
	ASSERT(pContext != nullptr);                  // Ensure it's there
	pContext->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
}


void CSketchAppView::OnElementDelete()
{
	if (m_pSelected)
	{
		GetDocument()->DeleteElement(m_pSelected);
		m_pSelected.reset();
	}
}


void CSketchAppView::OnElementMove()
{
	CClientDC aDC{ this };
	OnPrepareDC(&aDC); // Set up the device context
	GetCursorPos(&m_CursorPos); // Get cursor position in screen coords
	ScreenToClient(&m_CursorPos); // Convert to client coords
	aDC.DPtoLP(&m_CursorPos); // Convert to logical
	m_FirstPos = m_CursorPos; // Remember first position
	m_MoveMode = true; // Start move mode
}


void CSketchAppView::OnRButtonDown(UINT nFlags, CPoint point)
{
	if (m_MoveMode)
	{
		// In moving mode, so drop element back in original position
		CClientDC aDC{ this };
		OnPrepareDC(&aDC); // Get origin adjusted
		MoveElement(aDC, m_FirstPos); // Move element to original position
		m_pSelected.reset(); // De-select element
		GetDocument()->UpdateAllViews(nullptr); // Redraw all the views
	}
}


void CSketchAppView::OnRButtonUp(UINT nFlags, CPoint point)
{
	if (m_MoveMode)
	{
		m_MoveMode = false;
	}
	else
	{
		CScrollView::OnRButtonUp(nFlags, point);
	}
}


void CSketchAppView::OnElementSendtoback()
{
	GetDocument()->SendToBack(m_pSelected);
}
