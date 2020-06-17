// Talk.h : main header file for the TALK application
//

#if !defined(AFX_TALK_H__898DD455_BBA3_494C_907F_A06F41D4E0C6__INCLUDED_)
#define AFX_TALK_H__898DD455_BBA3_494C_907F_A06F41D4E0C6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTalkApp:
// See Talk.cpp for the implementation of this class
//

class CTalkApp : public CWinApp
{
public:
	CTalkApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTalkApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTalkApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TALK_H__898DD455_BBA3_494C_907F_A06F41D4E0C6__INCLUDED_)
