#include "pch.h"
#include "Element.h"

CElement::CElement(const CPoint& start, COLORREF color, int penStyle, int penWidth)
	: m_StartPoint{ start }, m_PenWidth{ penWidth }, m_PenStyle{ penStyle }, m_Color{ color }
{
	
}

/**************************
 * CLine Class
 **************************/
CLine::CLine(const CPoint& start, const CPoint& end, COLORREF aColor, int penStyle)
	: CElement{start, aColor, penStyle}, m_EndPoint{end}
{
	// Define the enclosing rectangle
	m_EnclosingRect = CRect{ start, end };
	m_EnclosingRect.NormalizeRect();
	m_EnclosingRect.InflateRect(m_PenWidth, m_PenWidth);
}

void CLine::Draw(CDC* pDC)
{
	CPen aPen;
	CreatePen(aPen);

	CPen* pOldPen{ pDC->SelectObject(&aPen) };

	pDC->MoveTo(m_StartPoint);
	pDC->LineTo(m_EndPoint);

	pDC->SelectObject(pOldPen);
}

/**************************
 * CRectangle Class
 **************************/
CRectangle::CRectangle(const CPoint& start, const CPoint& end, COLORREF aColor, int penStyle) : CElement {start, aColor, penStyle}
{
	// Normalise the rectangle defining points
	m_StartPoint = CPoint{ (std::min)(start.x, end.x), (std::min)(start.y, end.y) };
	m_BottomRight = CPoint{ (std::max)(start.x, end.x), (std::max)(start.y, end.y) };

	// ensure width and height between the points is at least 2
	if ((m_BottomRight.x - m_StartPoint.x) < 2)
		m_BottomRight.x = m_StartPoint.x + 2;
	if ((m_BottomRight.y - m_StartPoint.y) < 2)
		m_BottomRight.y = m_StartPoint.y + 2;

	// Define the enclosing rectangle
	m_EnclosingRect = CRect{ m_StartPoint, m_BottomRight };
	m_EnclosingRect.InflateRect(m_PenWidth, m_PenWidth);
}

void CRectangle::Draw(CDC* pDC)
{
	// Create a pen for this object and initialize it
	CPen aPen;
	CreatePen(aPen);

	// Select the pen and the null brush
	CPen* pOldPen{ pDC->SelectObject(&aPen) };
	CBrush* pOldBrush{ dynamic_cast<CBrush*>(pDC->SelectStockObject(NULL_BRUSH)) };

	// Now draw the rectangle
	pDC->Rectangle(m_StartPoint.x, m_StartPoint.y,
		m_BottomRight.x, m_BottomRight.y);

	pDC->SelectObject(pOldBrush); // Restore the old brush
	pDC->SelectObject(pOldPen); // Restore the old pen
}

/**************************
 * CCircle Class
 **************************/
CCircle::CCircle(const CPoint& start, const CPoint& end, COLORREF color, int penStyle)
	: CElement{ start, color, penStyle }
{
	// Calculate the radius using floating-point values
	// because that is required by sqrt() function (in cmath)
	long radius{ static_cast<long> (sqrt(
	static_cast<double>((end.x - start.x) * (end.x - start.x) +
	(end.y - start.y) * (end.y - start.y)))) };
	
	if (radius < 1L) radius = 1L; // Circle radius must be >= 1
	
	// Define left-top and right-bottom points of rectangle for MM_TEXT mode
	m_StartPoint = CPoint{ start.x - radius, start.y - radius };
	m_BottomRight = CPoint{ start.x + radius, start.y + radius };

	// Define the enclosing rectangle
	m_EnclosingRect = CRect{ m_StartPoint.x, m_StartPoint.y,
	m_BottomRight.x, m_BottomRight.y };
	m_EnclosingRect.InflateRect(m_PenWidth, m_PenWidth);
}

void CCircle::Draw(CDC* pDC)
{
	// Create a pen for this object and initialize it
	CPen aPen;
	CreatePen(aPen);

	CPen* pOldPen{ pDC->SelectObject(&aPen) }; // Select the pen

	// Select a null brush
	CBrush* pOldBrush{ dynamic_cast<CBrush*>(pDC->SelectStockObject(NULL_BRUSH)) };

	// Now draw the circle
	pDC->Ellipse(m_StartPoint.x, m_StartPoint.y,
		m_BottomRight.x, m_BottomRight.y);

	pDC->SelectObject(pOldPen); // Restore the old pen
	pDC->SelectObject(pOldBrush); // Restore the old brush
}

/**************************
 * CCurve Class
 **************************/
CCurve::CCurve(const CPoint& first, const CPoint& second, COLORREF color, int penStyle)
	: CElement{first, color, penStyle}
{
	m_Points.push_back(second);
	m_EnclosingRect = CRect{
		(std::min)(first.x, second.x), (std::min)(first.y, second.y),
		(std::max)(first.x, second.x), (std::max)(first.y, second.y)
	};
	m_EnclosingRect.InflateRect(m_PenWidth, m_PenWidth);
}

void CCurve::Draw(CDC* pDC)
{
	// Create a pen for this object and initialize it
	CPen aPen;
	CreatePen(aPen);

	CPen* pOldPen{ pDC->SelectObject(&aPen) }; // Select the pen

	// Now draw the curve
	pDC->MoveTo(m_StartPoint);
	for (const auto& point : m_Points)
		pDC->LineTo(point);

	pDC->SelectObject(pOldPen); // Restore the old pen

}

void CCurve::AddSegment(const CPoint& point)
{
	m_Points.push_back(point); // Add the point to the end

	// Modify the enclosing rectangle for the new point
	m_EnclosingRect.DeflateRect(m_PenWidth, m_PenWidth);
	
	m_EnclosingRect = CRect{
		(std::min)(point.x, m_EnclosingRect.left),
		(std::min)(point.y, m_EnclosingRect.top),
		(std::max)(point.x, m_EnclosingRect.right),
		(std::max)(point.y, m_EnclosingRect.bottom)
	};
	
	m_EnclosingRect.InflateRect(m_PenWidth, m_PenWidth);
}

/**************************
 * CEllipse Class
 **************************/
CEllipse::CEllipse(const CPoint& start, const CPoint& end, COLORREF color, int penStyle)
	: CElement{start, color, penStyle}
{
	int xLen {end.x - start.x};
	int yLen {end.y - start.y};

	m_StartPoint = CPoint{ start.x - xLen, start.y - yLen };
	m_EndPoint = CPoint{ end.x + xLen, end.y + yLen };

	// Define the enclosing rectangle
	m_EnclosingRect = CRect{ m_StartPoint.x, m_StartPoint.y,
	start.x + xLen, start.y + yLen };
	m_EnclosingRect.InflateRect(m_PenWidth, m_PenWidth);
}

void CEllipse::Draw(CDC* pDC)
{
	// Create a pen for this object and initialize it
	CPen aPen;
	CreatePen(aPen);

	CPen* pOldPen{ pDC->SelectObject(&aPen) }; // Select the pen

	// Select a null brush
	CBrush* pOldBrush{ dynamic_cast<CBrush*>(pDC->SelectStockObject(NULL_BRUSH)) };

	// Now draw the circle
	pDC->Ellipse(m_StartPoint.x, m_StartPoint.y,
		m_EndPoint.x, m_EndPoint.y);

	pDC->SelectObject(pOldPen); // Restore the old pen
	pDC->SelectObject(pOldBrush); // Restore the old brush
}

