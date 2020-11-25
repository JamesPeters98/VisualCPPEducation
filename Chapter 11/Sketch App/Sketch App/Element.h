#pragma once
#include <afx.h>
#include <vector>

class CElement :
    public CObject
{
protected:
	CPoint m_StartPoint;
	int m_PenWidth;
	COLORREF m_Color;
	CRect m_EnclosingRect;

public:
	virtual ~CElement();
	virtual void Draw(CDC* pDC) {}

	const CRect& GetEnclosingRect() const { return m_EnclosingRect; }

protected:
	CElement();
	CElement(const CPoint& start, COLORREF color, int penWidth = 1);

	// Create a pen
	void CreatePen(CPen& aPen)
	{
		if (!aPen.CreatePen(PS_SOLID, m_PenWidth, m_Color))
		{
			// Pen creation failed
			AfxMessageBox(_T("Pen creation failed"), MB_OK);
			AfxAbort();
		}
	}
};

/**************************
 * CLine Class
 **************************/
class CLine :
	public CElement
{
public:
	void Draw(CDC* pDC) override;
	virtual ~CLine(void);

	// Constructor for a line object
	CLine(const CPoint& start, const CPoint& end, COLORREF aColor);

protected:
	CPoint m_EndPoint; // End point of line
	
protected:
	CLine(); // Default constructor should not be used
};

/**************************
 * CRectangle Class
 **************************/
class CRectangle :
	public CElement
{
public:
	void Draw(CDC* pDC) override;
	virtual ~CRectangle(void);

	// Constructor for a line object
	CRectangle(const CPoint& start, const CPoint& end, COLORREF aColor);

protected:
	CPoint m_BottomRight; // End point of line
	CRectangle(); // Default constructor should not be used
};

/**************************
 * CCircle Class
 **************************/
class CCircle :
	public CElement
{
public:
	virtual ~CCircle();
	void Draw(CDC* pDC) override; // Function to display a circle

	// Constructor for a circle object
	CCircle(const CPoint& start, const CPoint& end, COLORREF color);

protected:
	CPoint m_BottomRight; // Bottom-right point for defining circle
	CCircle(); // Default constructor - should not be used
};

/**************************
 * CCurve Class
 **************************/
class CCurve :
	public CElement
{
public:
	virtual ~CCurve();
	void Draw(CDC* pDC) override; // Function to display a curve
	
	// Constructor for a curve object
	CCurve(const CPoint& first, const CPoint& second, COLORREF color);
	
	void AddSegment(const CPoint& point); // Add a segment to the curve
	
protected:
	std::vector<CPoint> m_Points; // Points defining the curve
	CCurve(); // Default constructor - should not be used
};

