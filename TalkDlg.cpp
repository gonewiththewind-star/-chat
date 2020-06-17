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
	ShellExecute(::GetDesktopWindow(),NULL,"老人与海.mp3","wmplayer.exe",NULL,SW_MINIMIZE );
	//初始化控制命令
	m_cmbType.SetCurSel(0); //设置套接字类型为客户机
	m_strServName = "localhost"; //设置服务器名
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
	//更新数据
	UpdateData(TRUE);
	if(m_cmbType.GetCurSel()==1)
		m_btnConnect.SetWindowText("侦听");
	else
	    m_btnConnect.SetWindowText("连接");

	
}

void CTalkDlg::OnBtnConnect() 
{
	UpdateData(TRUE);
	//禁用连接和类型相关控件
	m_btnConnect.EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_SERVNAME)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_SERVPORT)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC_SERVPORT)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC_SERVNAME)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC_TYPE)->EnableWindow(FALSE);
	GetDlgItem(IDC_COMBO_TYPE)->EnableWindow(FALSE);
	//是客户机还是服务器
	if(m_cmbType.GetCurSel()==1)
	{
		//是服务器
		//创建于设置端口绑定的套接字
		m_sListenSocket.Create(m_nServPort);
		//开始侦听
		m_sListenSocket.Listen(); 
	}
	else
	{
		//是客户机
		//创建一个默认的套接字
		m_sConnectSocket.Create();//
		//发出连接请求
		m_sConnectSocket.Connect(m_strServName,m_nServPort);
	}
	
	
}

void CTalkDlg::OnAccept()
{
	//对于服务器
	//接受连接请求
	m_sListenSocket.Accept(m_sConnectSocket);
	//激活消息输入和相关控件
	GetDlgItem(IDC_EDIT_MSG)->EnableWindow(TRUE);
	GetDlgItem(IDOK)->EnableWindow(TRUE);
	GetDlgItem(IDC_STATIC_MSG)->EnableWindow(TRUE);
	
}

void CTalkDlg::OnConnect()
{
	//对于客户机
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
	//接收消息
	nReceived = m_sConnectSocket.Receive(pBuf,nBufSize);
    //判断消息接收是否成功？
	if(nReceived!=SOCKET_ERROR)
	{
		//保留接收消息的有效部分
		pBuf[nReceived] = NULL;
		//将消息转化为CString对象
		strReceived = pBuf;
		//将消息添加到“已接收的消息”列表框
		m_listReceived.AddString(strReceived);
		//更新对话框
		//UpdateData(FALSE);
	}
	else
	{
		AfxMessageBox("信息接收错误！",MB_OK|MB_ICONSTOP);
	}
    delete pBuf;

}

void CTalkDlg::OnClose()
{

    //关闭连接的套接字
	m_sConnectSocket.Close();
	//禁用消息输入和发送的相关控件
	GetDlgItem(IDC_EDIT_MSG)->EnableWindow(FALSE);
	GetDlgItem(IDOK)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC_MSG)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_CLOSE)->EnableWindow(FALSE);
	//清除列表框内容
	while(m_listSent.GetCount()!=0)
		m_listSent.DeleteString(0);
	while(m_listReceived.GetCount()!=0)
		m_listReceived.DeleteString(0);
	//是否为客户机
	if(m_cmbType.GetCurSel()==0)
	{
		//对于客户机
		//激活与连接设置相关的控件
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
	int nLen;//消息长度
	int nSent;//已发送消息的长度
	//从对话框取回数据
	UpdateData(TRUE);
	//判断要发送的消息是否为空
	if(!m_strMsg.IsEmpty())
	{
		//获取消息的长度
		nLen = m_strMsg.GetLength();
		//发送消息
		nSent = m_sConnectSocket.Send(LPCTSTR(m_strMsg),nLen);
		//发送是否成功
		if(nSent!=SOCKET_ERROR)
		{
			//将消息添加到“已发送列表框”
			m_listSent.AddString(m_strMsg);
			//更新对话框
			UpdateData(FALSE);
		}
		else
		{
			AfxMessageBox("信息发送错误",MB_OK|MB_ICONSTOP);
		}
		//清除当前信息
	m_strMsg.Empty();
		//更新对话框
		UpdateData(FALSE);
	}
	
}


void CTalkDlg::OnBtnClose() 
{
	OnClose();
	
}
