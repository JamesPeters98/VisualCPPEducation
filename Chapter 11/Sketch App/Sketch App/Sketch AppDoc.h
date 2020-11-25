// Sketch AppDoc.h : interface of the CSketchAppDoc class
//

#pragma once
#include <list>
#include <memory>

#include "Element.h"
#include "ElementColour.h"
#include "ElementType.h"

using SketchIterator = std::list<std::shared_ptr<CElement>>::const_iterator;

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

	// Add a sketch element
	void AddElement(std::shared_ptr<CElement>& pElement)
	{
		m_Sketch.push_back(pElement);
	}
	
	// Delete a sketch element
	void DeleteElement(std::shared_ptr<CElement>& pElement)
	{
		m_Sketch.remove(pElement);
	}

	// Provide a begin iterator for the sketch
	SketchIterator begin() const { return std::begin(m_Sketch); }
	// Provide an end iterator for the sketch
	SketchIterator end() const { return std::end(m_Sketch); }
	
protected:
	ElementType m_Element {ElementType::LINE};
	ElementColour m_Color {ElementColour::BLACK};
	std::list<std::shared_ptr<CElement>> m_Sketch;
public:
	afx_msg void OnUpdateColourBlack(CCmdUI* pCmdUI);
	afx_msg void OnUpdateColourRed(CCmdUI* pCmdUI);
	afx_msg void OnUpdateColourGreen(CCmdUI* pCmdUI);
	afx_msg void OnUpdateColourBlue(CCmdUI* pCmdUI);
	afx_msg void OnUpdateElementLine(CCmdUI* pCmdUI);
	afx_msg void OnUpdateElementRectangle(CCmdUI* pCmdUI);
	afx_msg void OnUpdateElementCircle(CCmdUI* pCmdUI);
	afx_msg void OnUpdateElementCurve(CCmdUI* pCmdUI);
	afx_msg void OnElementEllipse();
	void onColourUpdates(CCmdUI* pCmdUI, ElementColour colour);
	afx_msg void OnUpdateElementEllipse(CCmdUI* pCmdUI);
};
