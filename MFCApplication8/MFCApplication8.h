
// MFCApplication8.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMFCApplication8App: 
// �йش����ʵ�֣������ MFCApplication8.cpp
//

class CMFCApplication8App : public CWinApp
{
public:
	CMFCApplication8App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMFCApplication8App theApp;
