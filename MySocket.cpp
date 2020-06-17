// MySocket.cpp: implementation of the CMySocket class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Talk.h"
#include "MySocket.h"
#include "TalkDlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMySocket::CMySocket()
{
	m_pDlg = NULL;

}

CMySocket::~CMySocket()
{
	m_pDlg = NULL;

}

void CMySocket::SetParent(CTalkDlg *pDlg)
{
	//设置成员变量
	m_pDlg = pDlg;
	//return;

}

void CMySocket::OnAccept(int nErrorCode)
{
	if(nErrorCode==0)
		m_pDlg->OnAccept();

}

void CMySocket::OnConnect(int nErrorCode)
{
	if(nErrorCode==0)
		m_pDlg->OnConnect();

}

void CMySocket::OnClose(int nErrorCode)
{
	if(nErrorCode==0)
		m_pDlg->OnClose();

}

void CMySocket::OnReceive(int nErrorCode)
{
	if(nErrorCode==0)
		m_pDlg->OnReceive();

}
