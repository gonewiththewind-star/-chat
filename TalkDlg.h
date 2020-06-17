// TalkDlg.h : header file
//

#if !defined(AFX_TALKDLG_H__BCA877EC_F508_4D1D_8F99_D937059492B1__INCLUDED_)
#define AFX_TALKDLG_H__BCA877EC_F508_4D1D_8F99_D937059492B1__INCLUDED_

#include "MySocket.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CTalkDlg dialog

class CTalkDlg : public CDialog
{
// Construction
public:
	void OnClose();
	void OnReceive();
	void OnSend();
	void OnConnect();
	void OnAccept();
	CTalkDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTalkDlg)
	enum { IDD = IDD_TALK_DIALOG };
	CListBox	m_listSent;
	CListBox	m_listReceived;
	CComboBox	m_cmbType;
	CButton	m_btnConnect;
	CString	m_strMsg;
	CString	m_strServName;
	int		m_nServPort;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTalkDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTalkDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSelchangeComboType();
	afx_msg void OnBtnConnect();
	afx_msg void OnSendMsg();
	afx_msg void OnBtnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CMySocket m_sConnectSocket;
	CMySocket m_sListenSocket;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TALKDLG_H__BCA877EC_F508_4D1D_8F99_D937059492B1__INCLUDED_)
