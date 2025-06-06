#include "pch.h"
#include "framework.h"
#ifndef SHARED_HANDLERS
#include "URLsSearch.h"
#endif

#include "URLsSearchDoc.h"
#include "URLsSearchView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CURLsSearchView, CView)

BEGIN_MESSAGE_MAP(CURLsSearchView, CView)
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CURLsSearchView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()


CURLsSearchView::CURLsSearchView() noexcept
{

}

CURLsSearchView::~CURLsSearchView()
{
}

BOOL CURLsSearchView::PreCreateWindow(CREATESTRUCT& cs)
{

	return CView::PreCreateWindow(cs);
}

void CURLsSearchView::OnDraw(CDC*)
{
	CURLsSearchDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;


}




void CURLsSearchView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CURLsSearchView::OnPreparePrinting(CPrintInfo* pInfo)
{
	return DoPreparePrinting(pInfo);
}

void CURLsSearchView::OnBeginPrinting(CDC*, CPrintInfo*)
{
}

void CURLsSearchView::OnEndPrinting(CDC*, CPrintInfo*)
{
}

void CURLsSearchView::OnRButtonUp(UINT, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CURLsSearchView::OnContextMenu(CWnd*, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


#ifdef _DEBUG
void CURLsSearchView::AssertValid() const
{
	CView::AssertValid();
}

void CURLsSearchView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CURLsSearchDoc* CURLsSearchView::GetDocument() const
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CURLsSearchDoc)));
	return (CURLsSearchDoc*)m_pDocument;
}
#endif

