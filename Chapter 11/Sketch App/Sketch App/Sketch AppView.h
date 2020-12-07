
// Sketch AppView.h : interface of the CSketchAppView class
//

#pragma once

#include <memory>
#include "Element.h"


class CSketchAppView : public CScrollView
{
protected: // create from serialization only
	CSketchAppView() noexcept;
	DECLARE_DYNCREATE(CSketchAppView)

// Attributes
public:
	CSketchAppDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CSketchAppView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);

	virtual void OnInitialUpdate();
protected:
	// First point recorded for an element
	CPoint m_FirstPoint;
	CPoint m_SecondPoint;
	CPoint m_CursorPos;
	CPoint m_FirstPos;
	std::shared_ptr<CElement> m_pTempElement;
	std::shared_ptr<CElement> m_pSelected;
	bool m_MoveMode{ false };

	// Create a new element on the heap
	std::shared_ptr<CElement> CreateElement() const;
	// Move an element.
	void MoveElement(CClientDC& aDC, const CPoint& point);

	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
public:
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg void OnElementDelete();
	afx_msg void OnElementMove();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnElementSendtoback();
};

#ifndef _DEBUG  // debug version in Sketch AppView.cpp
inline CSketchAppDoc* CSketchAppView::GetDocument() const
   { return reinterpret_cast<CSketchAppDoc*>(m_pDocument); }
#endif

