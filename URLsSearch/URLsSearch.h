﻿#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       




class CURLsSearchApp : public CWinAppEx
{
public:
	CURLsSearchApp() noexcept;


public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CURLsSearchApp theApp;
