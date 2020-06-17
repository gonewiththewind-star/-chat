// MySocket.h: interface for the CMySocket class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYSOCKET_H__DF8F252A_EB90_4AEC_A4D9_B025B682712D__INCLUDED_)
#define AFX_MYSOCKET_H__DF8F252A_EB90_4AEC_A4D9_B025B682712D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CTalkDlg;

class CMySocket : public CAsyncSocket  
{
public:
	void SetParent(CTalkDlg* pDlg);
	CMySocket();
	virtual ~CMySocket();

private:
	CTalkDlg* m_pDlg;
protected:
	virtual void OnReceive(int nErrorCode);
    virtual void OnClose(int nErrorCode);
	virtual void OnConnect(int nErrorCode);
	virtual void OnAccept(int nErrorCode);
};

#endif // !defined(AFX_MYSOCKET_H__DF8F252A_EB90_4AEC_A4D9_B025B682712D__INCLUDED_)
