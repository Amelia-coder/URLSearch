#include "pch.h"
#include "framework.h"
#ifndef SHARED_HANDLERS
#include "URLsSearch.h"
#endif

#include "URLsSearchDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CURLsSearchDoc, CDocument)

BEGIN_MESSAGE_MAP(CURLsSearchDoc, CDocument)
END_MESSAGE_MAP()


CURLsSearchDoc::CURLsSearchDoc() noexcept
{

}

CURLsSearchDoc::~CURLsSearchDoc()
{
}

BOOL CURLsSearchDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;


	return TRUE;
}




void CURLsSearchDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
	}
	else
	{
	}
}

#ifdef SHARED_HANDLERS

void CURLsSearchDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
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

void CURLsSearchDoc::InitializeSearchContent()
{
	CString strSearchContent;
	SetSearchContent(strSearchContent);
}

void CURLsSearchDoc::SetSearchContent(const CString& value)
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

#endif 

#ifdef _DEBUG
void CURLsSearchDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CURLsSearchDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif 

