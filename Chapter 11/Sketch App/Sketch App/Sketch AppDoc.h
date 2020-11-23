
// Sketch AppDoc.h : interface of the CSketchAppDoc class
//


#pragma once
#include "ElementColour.h"
#include "ElementType.h"


class CSketchAppDoc : public CDocument
{
protected: // create from serialization only
	CSketchAppDoc() noexcept;
	DECLARE_DYNCREATE(CSketchAppDoc)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CSketchAppDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	afx_msg void OnColourBlack();
	afx_msg void OnColourRed();
	afx_msg void OnColourGreen();
	afx_msg void OnColourBlue();
	afx_msg void OnElementLine();
	afx_msg void OnElementRectangle();
	afx_msg void OnElementCircle();
	afx_msg void OnElementCurve();

	ElementType GetElementType()const { return m_Element; }
	ElementColour GetElementColor()const { return m_Color; }
	
protected:
	ElementType m_Element {ElementType::LINE};
	ElementColour m_Color {ElementColour::BLACK};
public:
	afx_msg void OnUpdateColourBlack(CCmdUI* pCmdUI);
	afx_msg void OnUpdateColourRed(CCmdUI* pCmdUI);
	afx_msg void OnUpdateColourGreen(CCmdUI* pCmdUI);
	afx_msg void OnUpdateColourBlue(CCmdUI* pCmdUI);
	afx_msg void OnUpdateElementLine(CCmdUI* pCmdUI);
	afx_msg void OnUpdateElementRectangle(CCmdUI* pCmdUI);
	afx_msg void OnUpdateElementCircle(CCmdUI* pCmdUI);
	afx_msg void OnUpdateElementCurve(CCmdUI* pCmdUI);
};
