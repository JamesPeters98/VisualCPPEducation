#pragma once
#include <afx.h>
#include <memory>
#include <vector>

static const COLORREF SELECT_COLOR{ RGB(255,0,180) };
static const int SELECT_PEN_STYLE{PS_DASHDOTDOT};

class CElement :
    public CObject
{
protected:
	CPoint m_StartPoint;
	int m_PenWidth;
	COLORREF m_Color;
	CRect m_EnclosingRect;
	int m_PenStyle;

public:
	virtual ~CElement() = default;
	virtual void Draw(CDC* pDC, std::shared_ptr<CElement> pElement = nullptr) {}
	virtual void Move(const CSize& aSize) {}

	const CRect& GetEnclosingRect() const { return m_EnclosingRect; }

protected:
	CElement() = default;
	CElement(const CPoint& start, COLORREF color, int penStyle = PS_SOLID, int penWidth = 1);

	// Create a pen
	void CreatePen(CPen& aPen, std::shared_ptr<CElement> pElement = nullptr)
	{
		if (!aPen.CreatePen(this == pElement.get() ? SELECT_PEN_STYLE : m_PenStyle, m_PenWidth, this == pElement.get() ? SELECT_COLOR : m_Color))
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
	void Draw(CDC* pDC, std::shared_ptr<CElement> pElement = nullptr) override;
	void Move(const CSize& aSize) override; // Function to move an element
	virtual ~CLine() = default;

	// Constructor for a line object
	CLine(const CPoint& start, const CPoint& end, COLORREF aColor, int penStyle);

protected:
	CPoint m_EndPoint; // End point of line
	
protected:
	CLine() = default; // Default constructor should not be used
};

/**************************
 * CRectangle Class
 **************************/
class CRectangle :
	public CElement
{
public:
	void Draw(CDC* pDC, std::shared_ptr<CElement> pElement = nullptr) override;
	void Move(const CSize& aSize) override; // Function to move an element
	virtual ~CRectangle() = default;

	// Constructor for a line object
	CRectangle(const CPoint& start, const CPoint& end, COLORREF aColor, int penStyle);

protected:
	CPoint m_BottomRight; // End point of line
	CRectangle() = default; // Default constructor should not be used
};

/**************************
 * CCircle Class
 **************************/
class CCircle :
	public CElement
{
public:
	virtual ~CCircle() = default;
	void Draw(CDC* pDC, std::shared_ptr<CElement> pElement = nullptr) override; // Function to display a circle
	void Move(const CSize& aSize) override; // Function to move an element

	// Constructor for a circle object
	CCircle(const CPoint& start, const CPoint& end, COLORREF color, int penStyle);

protected:
	CPoint m_BottomRight; // Bottom-right point for defining circle
	CCircle() = default; // Default constructor - should not be used
};

/**************************
 * CCurve Class
 **************************/
class CCurve :
	public CElement
{
public:
	virtual ~CCurve() = default;
	void Draw(CDC* pDC, std::shared_ptr<CElement> pElement = nullptr) override; // Function to display a curve
	void Move(const CSize& aSize) override; // Function to move an element
	
	// Constructor for a curve object
	CCurve(const CPoint& first, const CPoint& second, COLORREF color, int penStyle);
	
	void AddSegment(const CPoint& point); // Add a segment to the curve
	
protected:
	std::vector<CPoint> m_Points; // Points defining the curve
	CCurve() = default; // Default constructor - should not be used
};

/**************************
 * CEllipse Class
 **************************/
class CEllipse : public CElement
{
public:
	virtual ~CEllipse() = default;
	void Draw(CDC* pDC, std::shared_ptr<CElement> pElement = nullptr) override; // Function to display a circle
	void Move(const CSize& aSize) override; // Function to move an element

	// Constructor for a circle object
	CEllipse(const CPoint& start, const CPoint& end, COLORREF color, int penStyle);

protected:
	CPoint m_EndPoint; // Bottom-right point for defining circle
	CEllipse() = default; // Default constructor - should not be used
};
