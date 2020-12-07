
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


#include <iostream>
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
	ON_COMMAND(ID_ELEMENT_ELLIPSE, &CSketchAppDoc::OnElementEllipse)
	ON_UPDATE_COMMAND_UI(ID_ELEMENT_ELLIPSE, &CSketchAppDoc::OnUpdateElementEllipse)
	ON_COMMAND(ID_PENSTYLE_SOLID, &CSketchAppDoc::OnPenstyleSolid)
	ON_COMMAND(ID_PENSTYLE_DASHED, &CSketchAppDoc::OnPenstyleDashed)
	ON_COMMAND(ID_PENSTYLE_DOTTED, &CSketchAppDoc::OnPenstyleDotted)
	ON_COMMAND(ID_PENSTYLE_DASH, &CSketchAppDoc::OnPenstyleDashDotted)
	ON_UPDATE_COMMAND_UI(ID_PENSTYLE_SOLID, &CSketchAppDoc::OnUpdatePenstyleSolid)
	ON_UPDATE_COMMAND_UI(ID_PENSTYLE_DASHED, &CSketchAppDoc::OnUpdatePenstyleDashed)
	ON_UPDATE_COMMAND_UI(ID_PENSTYLE_DOTTED, &CSketchAppDoc::OnUpdatePenstyleDotted)
	ON_UPDATE_COMMAND_UI(ID_PENSTYLE_DASH, &CSketchAppDoc::OnUpdatePenstyleDashDotted)
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

void CSketchAppDoc::OnElementEllipse()
{
	m_Element = ElementType::ELLIPSE;
}

void CSketchAppDoc::doUpperCase(CCmdUI* pCmdUI, ElementColour colour)
{
	pCmdUI->SetCheck(m_Color == colour);

	CMenu* menu = pCmdUI->m_pMenu;
	if (menu) {
		// Select String from selected menu item.
		CString str;
		menu->GetMenuStringW(pCmdUI->m_nID, str, MF_BYCOMMAND);

		// Create upper or lower case version of the string
		CString newStr;
		if (m_Color == colour)
		{
			newStr = str.MakeUpper();
		} else
		{
			newStr = str.MakeLower();
			newStr.SetAt(0, str.MakeUpper().GetAt(0));
		}

		// Set value of menu item text
		pCmdUI->SetText(newStr);
	}
}

void CSketchAppDoc::OnPenstyleSolid()
{
	m_PenStyle = PS_SOLID;
}


void CSketchAppDoc::OnPenstyleDashed()
{
	m_PenStyle = PS_DASH;
}


void CSketchAppDoc::OnPenstyleDotted()
{
	m_PenStyle = PS_DOT;
}


void CSketchAppDoc::OnPenstyleDashDotted()
{
	m_PenStyle = PS_DASHDOT;
}


void CSketchAppDoc::OnUpdateColourBlack(CCmdUI* pCmdUI)
{
	doUpperCase(pCmdUI, ElementColour::BLACK);
}

void CSketchAppDoc::OnUpdateColourRed(CCmdUI* pCmdUI)
{
	doUpperCase(pCmdUI, ElementColour::RED);
}

void CSketchAppDoc::OnUpdateColourGreen(CCmdUI* pCmdUI)
{
	doUpperCase(pCmdUI, ElementColour::GREEN);
}

void CSketchAppDoc::OnUpdateColourBlue(CCmdUI* pCmdUI)
{
	doUpperCase(pCmdUI, ElementColour::BLUE);
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

void CSketchAppDoc::OnUpdateElementEllipse(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_Element == ElementType::ELLIPSE);
}





void CSketchAppDoc::OnUpdatePenstyleSolid(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_PenStyle == PS_SOLID);
}


void CSketchAppDoc::OnUpdatePenstyleDashed(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_PenStyle == PS_DASH);
}


void CSketchAppDoc::OnUpdatePenstyleDotted(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_PenStyle == PS_DOT);
}


void CSketchAppDoc::OnUpdatePenstyleDashDotted(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_PenStyle == PS_DASHDOT);
}


std::shared_ptr<CElement> CSketchAppDoc::FindElement(const CPoint& point)const
{
	for (const auto& element : m_Sketch)
	{
		if (element->GetEnclosingRect().PtInRect(point))
			return element;
	}
	return nullptr;
}


void CSketchAppDoc::SendToBack(std::shared_ptr<CElement>& pElement)
{
	if(pElement)
	{
		auto pos = std::find(m_Sketch.begin(), m_Sketch.end(), pElement);
		if (pos != m_Sketch.end()) m_Sketch.erase(pos);
		m_Sketch.push_back(pElement);
	}
}
