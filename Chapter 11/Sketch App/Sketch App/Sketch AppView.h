
// Sketch AppView.h : interface of the CSketchAppView class
//

#pragma once


class CSketchAppView : public CView
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
};

#ifndef _DEBUG  // debug version in Sketch AppView.cpp
inline CSketchAppDoc* CSketchAppView::GetDocument() const
   { return reinterpret_cast<CSketchAppDoc*>(m_pDocument); }
#endif

