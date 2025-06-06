#include "pch.h"
#include "framework.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "URLsSearch.h"
#include "MainFrm.h"
#include "URLsSearchDlg.h"
#include "Logger.h"

#include "ChildFrm.h"
#include "URLsSearchDoc.h"
#include "URLsSearchView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



BEGIN_MESSAGE_MAP(CURLsSearchApp, CWinAppEx)
	ON_COMMAND(ID_HELP, &CWinAppEx::OnHelp)
END_MESSAGE_MAP()



CURLsSearchApp::CURLsSearchApp() noexcept
	: m_nAppLook(0)
	, m_bHiColorIcons(TRUE)
{
	SetAppID(_T("URLsSearch.AppID.NoVersion"));
}

CURLsSearchApp theApp;



BOOL CURLsSearchApp::InitInstance()
{
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();

	AfxEnableControlContainer();

	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	SetRegistryKey(_T("URLsSearch"));

	InitContextMenuManager();
	InitKeyboardManager();
	InitTooltipManager();

	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	Logger::initialize();
	Logger::log(LogLevel::Info, L"Application starting...");

	CURLsSearchDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();

	Logger::cleanup();

	return FALSE;
}

int CURLsSearchApp::ExitInstance()
{
	AfxOleTerm(FALSE);
	return CWinAppEx::ExitInstance();
}



class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg() noexcept;

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    

protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() noexcept : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


void CURLsSearchApp::PreLoadState()
{
}

void CURLsSearchApp::LoadCustomState()
{
}

void CURLsSearchApp::SaveCustomState()
{
}




