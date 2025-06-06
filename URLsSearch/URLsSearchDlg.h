#pragma once
#include "URLSearcher.h"

class CURLsSearchDlg : public CDialogEx
{
public:
    CURLsSearchDlg(CWnd* pParent = nullptr);

#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_URLSSEARCH_DIALOG };
#endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX);
    virtual BOOL OnInitDialog();
    afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
    afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();
    DECLARE_MESSAGE_MAP()

private:
    HICON m_hIcon;
    CEdit m_editFileList;
    CListCtrl m_listResults;
    URLSearcher m_urlSearcher;

public:
    afx_msg void OnBnClickedButtonSearch();
    void DisplayResults(const std::map<std::wstring, std::vector<URLOccurrence>>& results);
}; 