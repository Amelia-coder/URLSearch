#include "pch.h"
#include "framework.h"
#include "URLsSearch.h"
#include "URLsSearchDlg.h"
#include "Logger.h"
#include <sstream>
#include <vector>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CURLsSearchDlg::CURLsSearchDlg(CWnd* pParent)
    : CDialogEx(IDD_URLSSEARCH_DIALOG, pParent)
{
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CURLsSearchDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT_FILES, m_editFileList);
    DDX_Control(pDX, IDC_LIST_RESULTS, m_listResults);
}

BEGIN_MESSAGE_MAP(CURLsSearchDlg, CDialogEx)
    ON_WM_SYSCOMMAND()
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDC_BUTTON_SEARCH, &CURLsSearchDlg::OnBnClickedButtonSearch)
END_MESSAGE_MAP()

BOOL CURLsSearchDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    SetIcon(m_hIcon, TRUE);
    SetIcon(m_hIcon, FALSE);

    m_listResults.InsertColumn(0, L"URL", LVCFMT_LEFT, 300);
    m_listResults.InsertColumn(1, L"File", LVCFMT_LEFT, 200);
    m_listResults.InsertColumn(2, L"Line", LVCFMT_LEFT, 60);
    m_listResults.InsertColumn(3, L"Column", LVCFMT_LEFT, 60);

    Logger::initialize();
    Logger::log(LogLevel::Info, L"Application started");

    return TRUE;
}

void CURLsSearchDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
    CDialogEx::OnSysCommand(nID, lParam);
}

void CURLsSearchDlg::OnPaint()
{
    if (IsIconic())
    {
        CPaintDC dc(this);
        SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);
        int cxIcon = GetSystemMetrics(SM_CXICON);
        int cyIcon = GetSystemMetrics(SM_CYICON);
        CRect rect;
        GetClientRect(&rect);
        int x = (rect.Width() - cxIcon + 1) / 2;
        int y = (rect.Height() - cyIcon + 1) / 2;
        dc.DrawIcon(x, y, m_hIcon);
    }
    else
    {
        CDialogEx::OnPaint();
    }
}

HCURSOR CURLsSearchDlg::OnQueryDragIcon()
{
    return static_cast<HCURSOR>(m_hIcon);
}

void CURLsSearchDlg::OnBnClickedButtonSearch()
{
    CString fileListStr;
    m_editFileList.GetWindowText(fileListStr);

    if (fileListStr.IsEmpty()) {
        MessageBox(L"Please enter file paths separated by commas", L"Error", MB_ICONERROR);
        Logger::log(LogLevel::Error, L"Empty file list provided");
        return;
    }

    std::vector<std::wstring> files;
    CString token;
    int curPos = 0;
    token = fileListStr.Tokenize(L",", curPos);
    while (!token.IsEmpty()) {
        token.Trim();
        if (!token.IsEmpty()) {
            files.push_back(static_cast<LPCWSTR>(token));
        }
        token = fileListStr.Tokenize(L",", curPos);
    }

    try {
        auto results = m_urlSearcher.searchURLs(files);
        DisplayResults(results);
        Logger::log(LogLevel::Info, L"URL search completed successfully");
    }
    catch (const std::exception& e) {
        std::wstringstream ss;
        ss << L"Error during URL search: " << e.what();
        Logger::log(LogLevel::Error, ss.str());
        MessageBox(CString(e.what()), L"Error", MB_ICONERROR);
    }
}

void CURLsSearchDlg::DisplayResults(const std::map<std::wstring, std::vector<URLOccurrence>>& results)
{
    m_listResults.DeleteAllItems();
    int itemIndex = 0;

    for (const auto& result : results) {
        const auto& url = result.first;
        const auto& occurrences = result.second;

        for (const auto& occurrence : occurrences) {
            int nIndex = m_listResults.InsertItem(itemIndex, url.c_str());
            
            m_listResults.SetItem(nIndex, 1, LVIF_TEXT, occurrence.filePath.c_str(), 0, 0, 0, 0);
            
            CString lineStr, columnStr;
            lineStr.Format(L"%d", occurrence.line);
            columnStr.Format(L"%d", occurrence.column);
            
            m_listResults.SetItem(nIndex, 2, LVIF_TEXT, lineStr, 0, 0, 0, 0);
            m_listResults.SetItem(nIndex, 3, LVIF_TEXT, columnStr, 0, 0, 0, 0);
            
            itemIndex++;
        }
    }
} 