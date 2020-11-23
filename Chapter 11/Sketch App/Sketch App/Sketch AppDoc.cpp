
// Sketch AppDoc.cpp : implementation of the CSketchAppDoc class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Sketch App.h"
#endif

#include "Sketch AppDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CSketchAppDoc

IMPLEMENT_DYNCREATE(CSketchAppDoc, CDocument)

BEGIN_MESSAGE_MAP(CSketchAppDoc, CDocument)
	ON_COMMAND(ID_COLOUR_BLACK, &CSketchAppDoc::OnColourBlack)
	ON_COMMAND(ID_COLOUR_RED, &CSketchAppDoc::OnColourRed)
	ON_COMMAND(ID_COLOUR_GREEN, &CSketchAppDoc::OnColourGreen)
	ON_COMMAND(ID_COLOUR_BLUE, &CSketchAppDoc::OnColourBlue)
	ON_COMMAND(ID_ELEMENT_LINE, &CSketchAppDoc::OnElementLine)
	ON_COMMAND(ID_ELEMENT_RECTANGLE, &CSketchAppDoc::OnElementRectangle)
	ON_COMMAND(ID_ELEMENT_CIRCLE, &CSketchAppDoc::OnElementCircle)
	ON_COMMAND(ID_ELEMENT_CURVE, &CSketchAppDoc::OnElementCurve)
	ON_UPDATE_COMMAND_UI(ID_COLOUR_BLACK, &CSketchAppDoc::OnUpdateColourBlack)
	ON_UPDATE_COMMAND_UI(ID_COLOUR_RED, &CSketchAppDoc::OnUpdateColourRed)
	ON_UPDATE_COMMAND_UI(ID_COLOUR_GREEN, &CSketchAppDoc::OnUpdateColourGreen)
	ON_UPDATE_COMMAND_UI(ID_COLOUR_BLUE, &CSketchAppDoc::OnUpdateColourBlue)
	ON_UPDATE_COMMAND_UI(ID_ELEMENT_LINE, &CSketchAppDoc::OnUpdateElementLine)
	ON_UPDATE_COMMAND_UI(ID_ELEMENT_RECTANGLE, &CSketchAppDoc::OnUpdateElementRectangle)
	ON_UPDATE_COMMAND_UI(ID_ELEMENT_CIRCLE, &CSketchAppDoc::OnUpdateElementCircle)
	ON_UPDATE_COMMAND_UI(ID_ELEMENT_CURVE, &CSketchAppDoc::OnUpdateElementCurve)
END_MESSAGE_MAP()


// CSketchAppDoc construction/destruction

CSketchAppDoc::CSketchAppDoc() noexcept
{
	// TODO: add one-time construction code here

}

CSketchAppDoc::~CSketchAppDoc()
{
}

BOOL CSketchAppDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CSketchAppDoc serialization

void CSketchAppDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CSketchAppDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CSketchAppDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data.
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CSketchAppDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CSketchAppDoc diagnostics

#ifdef _DEBUG
void CSketchAppDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSketchAppDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CSketchAppDoc commands


void CSketchAppDoc::OnColourBlack()
{
	m_Color = ElementColour::BLACK;
}


void CSketchAppDoc::OnColourRed()
{
	m_Color = ElementColour::RED;
}


void CSketchAppDoc::OnColourGreen()
{
	m_Color = ElementColour::GREEN;
}


void CSketchAppDoc::OnColourBlue()
{
	m_Color = ElementColour::BLUE;
}


void CSketchAppDoc::OnElementLine()
{
	m_Element = ElementType::LINE;
}


void CSketchAppDoc::OnElementRectangle()
{
	m_Element = ElementType::RECTANGLE;
}


void CSketchAppDoc::OnElementCircle()
{
	m_Element = ElementType::CIRCLE;
}


void CSketchAppDoc::OnElementCurve()
{
	m_Element = ElementType::CURVE;
}


void CSketchAppDoc::OnUpdateColourBlack(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_Color == ElementColour::BLACK);
}

void CSketchAppDoc::OnUpdateColourRed(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_Color == ElementColour::RED);
}

void CSketchAppDoc::OnUpdateColourGreen(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_Color == ElementColour::GREEN);
}

void CSketchAppDoc::OnUpdateColourBlue(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_Color == ElementColour::BLUE);
}

void CSketchAppDoc::OnUpdateElementLine(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_Element == ElementType::LINE);
}


void CSketchAppDoc::OnUpdateElementRectangle(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_Element == ElementType::RECTANGLE);
}


void CSketchAppDoc::OnUpdateElementCircle(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_Element == ElementType::CIRCLE);
}


void CSketchAppDoc::OnUpdateElementCurve(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_Element == ElementType::CURVE);
}
