// TalkDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Talk.h"
#include "TalkDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTalkDlg dialog

CTalkDlg::CTalkDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTalkDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTalkDlg)
	m_strMsg = _T("");
	m_strServName = _T("");
	m_nServPort = 0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTalkDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTalkDlg)
	DDX_Control(pDX, IDC_LIST_SENT, m_listSent);
	DDX_Control(pDX, IDC_LIST_RECEIVED, m_listReceived);
	DDX_Control(pDX, IDC_COMBO_TYPE, m_cmbType);
	DDX_Control(pDX, IDC_BTN_CONNECT, m_btnConnect);
	DDX_Text(pDX, IDC_EDIT_MSG, m_strMsg);
	DDX_Text(pDX, IDC_EDIT_SERVNAME, m_strServName);
	DDX_Text(pDX, IDC_EDIT_SERVPORT, m_nServPort);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTalkDlg, CDialog)
	//{{AFX_MSG_MAP(CTalkDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_CBN_SELCHANGE(IDC_COMBO_TYPE, OnSelchangeComboType)
	ON_BN_CLICKED(IDC_BTN_CONNECT, OnBtnConnect)
	ON_BN_CLICKED(IDOK, OnSendMsg)
	ON_BN_CLICKED(IDC_BTN_CLOSE, OnBtnClose)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTalkDlg message handlers

BOOL CTalkDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	ShellExecute(::GetDesktopWindow(),NULL,"�����뺣.mp3","wmplayer.exe",NULL,SW_MINIMIZE );
	//��ʼ����������
	m_cmbType.SetCurSel(0); //�����׽�������Ϊ�ͻ���
	m_strServName = "localhost"; //���÷�������
	m_nServPort = 8000;

	UpdateData(FALSE);

    m_sListenSocket.SetParent(this);
	m_sConnectSocket.SetParent(this);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTalkDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTalkDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTalkDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CTalkDlg::OnSelchangeComboType() 
{
	//��������
	UpdateData(TRUE);
	if(m_cmbType.GetCurSel()==1)
		m_btnConnect.SetWindowText("����");
	else
	    m_btnConnect.SetWindowText("����");

	
}

void CTalkDlg::OnBtnConnect() 
{
	UpdateData(TRUE);
	//�������Ӻ�������ؿؼ�
	m_btnConnect.EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_SERVNAME)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_SERVPORT)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC_SERVPORT)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC_SERVNAME)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC_TYPE)->EnableWindow(FALSE);
	GetDlgItem(IDC_COMBO_TYPE)->EnableWindow(FALSE);
	//�ǿͻ������Ƿ�����
	if(m_cmbType.GetCurSel()==1)
	{
		//�Ƿ�����
		//���������ö˿ڰ󶨵��׽���
		m_sListenSocket.Create(m_nServPort);
		//��ʼ����
		m_sListenSocket.Listen(); 
	}
	else
	{
		//�ǿͻ���
		//����һ��Ĭ�ϵ��׽���
		m_sConnectSocket.Create();//
		//������������
		m_sConnectSocket.Connect(m_strServName,m_nServPort);
	}
	
	
}

void CTalkDlg::OnAccept()
{
	//���ڷ�����
	//������������
	m_sListenSocket.Accept(m_sConnectSocket);
	//������Ϣ�������ؿؼ�
	GetDlgItem(IDC_EDIT_MSG)->EnableWindow(TRUE);
	GetDlgItem(IDOK)->EnableWindow(TRUE);
	GetDlgItem(IDC_STATIC_MSG)->EnableWindow(TRUE);
	
}

void CTalkDlg::OnConnect()
{
	//���ڿͻ���
	GetDlgItem(IDC_EDIT_MSG)->EnableWindow(TRUE);
	GetDlgItem(IDOK)->EnableWindow(TRUE);
	GetDlgItem(IDC_STATIC_MSG)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTN_CLOSE)->EnableWindow(TRUE);


}

void CTalkDlg::OnSend()
{



}

void CTalkDlg::OnReceive()
{
	char* pBuf = new char[1025];
	//char pBuf[1025];
	int nBufSize = 1024;
	int nReceived;
	CString strReceived;
	//������Ϣ
	nReceived = m_sConnectSocket.Receive(pBuf,nBufSize);
    //�ж���Ϣ�����Ƿ�ɹ���
	if(nReceived!=SOCKET_ERROR)
	{
		//����������Ϣ����Ч����
		pBuf[nReceived] = NULL;
		//����Ϣת��ΪCString����
		strReceived = pBuf;
		//����Ϣ��ӵ����ѽ��յ���Ϣ���б��
		m_listReceived.AddString(strReceived);
		//���¶Ի���
		//UpdateData(FALSE);
	}
	else
	{
		AfxMessageBox("��Ϣ���մ���",MB_OK|MB_ICONSTOP);
	}
    delete pBuf;

}

void CTalkDlg::OnClose()
{

    //�ر����ӵ��׽���
	m_sConnectSocket.Close();
	//������Ϣ����ͷ��͵���ؿؼ�
	GetDlgItem(IDC_EDIT_MSG)->EnableWindow(FALSE);
	GetDlgItem(IDOK)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC_MSG)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_CLOSE)->EnableWindow(FALSE);
	//����б������
	while(m_listSent.GetCount()!=0)
		m_listSent.DeleteString(0);
	while(m_listReceived.GetCount()!=0)
		m_listReceived.DeleteString(0);
	//�Ƿ�Ϊ�ͻ���
	if(m_cmbType.GetCurSel()==0)
	{
		//���ڿͻ���
		//����������������صĿؼ�
		GetDlgItem(IDC_BTN_CONNECT)->EnableWindow(TRUE);
	    GetDlgItem(IDC_EDIT_SERVNAME)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_SERVPORT)->EnableWindow(TRUE);
	    GetDlgItem(IDC_STATIC_SERVNAME)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC_SERVPORT)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC_TYPE)->EnableWindow(TRUE);
	    GetDlgItem(IDC_COMBO_TYPE)->EnableWindow(TRUE);

	}

}

void CTalkDlg::OnSendMsg() 
{
	int nLen;//��Ϣ����
	int nSent;//�ѷ�����Ϣ�ĳ���
	//�ӶԻ���ȡ������
	UpdateData(TRUE);
	//�ж�Ҫ���͵���Ϣ�Ƿ�Ϊ��
	if(!m_strMsg.IsEmpty())
	{
		//��ȡ��Ϣ�ĳ���
		nLen = m_strMsg.GetLength();
		//������Ϣ
		nSent = m_sConnectSocket.Send(LPCTSTR(m_strMsg),nLen);
		//�����Ƿ�ɹ�
		if(nSent!=SOCKET_ERROR)
		{
			//����Ϣ��ӵ����ѷ����б��
			m_listSent.AddString(m_strMsg);
			//���¶Ի���
			UpdateData(FALSE);
		}
		else
		{
			AfxMessageBox("��Ϣ���ʹ���",MB_OK|MB_ICONSTOP);
		}
		//�����ǰ��Ϣ
	m_strMsg.Empty();
		//���¶Ի���
		UpdateData(FALSE);
	}
	
}


void CTalkDlg::OnBtnClose() 
{
	OnClose();
	
}
