#pragma once


class CURLsSearchView : public CView
{
protected:
	CURLsSearchView() noexcept;
	DECLARE_DYNCREATE(CURLsSearchView)

public:
	CURLsSearchDoc* GetDocument() const;

public:

public:
	virtual void OnDraw(CDC* pDC); 
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

public:
	virtual ~CURLsSearchView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG 
inline CURLsSearchDoc* CURLsSearchView::GetDocument() const
   { return reinterpret_cast<CURLsSearchDoc*>(m_pDocument); }
#endif

