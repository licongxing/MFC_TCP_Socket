
// 02_TCPServerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "02_TCPServer.h"
#include "02_TCPServerDlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy02_TCPServerDlg 对话框



CMy02_TCPServerDlg::CMy02_TCPServerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MY02_TCPSERVER_DIALOG, pParent)
	, m_port(0), m_serverSocket(this)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy02_TCPServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_port);
	DDX_Control(pDX, IDC_BUTTON1, m_startBtn);
	DDX_Control(pDX, IDC_BUTTON2, m_stopBtn);
	DDX_Control(pDX, IDC_BUTTON3, m_clearBtn);
	DDX_Control(pDX, IDC_LIST1, m_listCtrl);
}

BEGIN_MESSAGE_MAP(CMy02_TCPServerDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON3, &CMy02_TCPServerDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON1, &CMy02_TCPServerDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMy02_TCPServerDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CMy02_TCPServerDlg 消息处理程序

BOOL CMy02_TCPServerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	m_port = 8888;// 服务器端口
	m_stopBtn.EnableWindow(FALSE);
	UpdateData(FALSE);
	//m_listCtrl.SetExtendedStyle(m_listCtrl.GetExtendedStyle() | LVS_EX_FULLROWSELECT);


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMy02_TCPServerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMy02_TCPServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


// 清空消息列表
void CMy02_TCPServerDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	m_listCtrl.DeleteAllItems();
	//m_serverSocket.SendMsg(_T("aaaa"));
}

// 启动服务器
void CMy02_TCPServerDlg::OnBnClickedButton1()
{
	UpdateData(TRUE);
	BOOL ret = m_serverSocket.Create(m_port, SOCK_STREAM);
	if (ret)
	{
		
		ret = m_serverSocket.Listen();
		if (ret)
		{
			//m_serverSocket.a
			m_startBtn.EnableWindow(FALSE);
			m_stopBtn.EnableWindow(TRUE);
			return;
		}
		else
		{
			MessageBox(_T("监听套接字监听失败"));
		}
	}
	else 
	{
		MessageBox(_T("创建监听套接字失败"));
	}
	m_startBtn.EnableWindow(TRUE);
	m_stopBtn.EnableWindow(FALSE);
}

// 停止服务器
void CMy02_TCPServerDlg::OnBnClickedButton2()
{
	m_serverSocket.CloseAllConn();
	m_startBtn.EnableWindow(TRUE);
	m_stopBtn.EnableWindow(FALSE);
}

void CMy02_TCPServerDlg::AddMsg(CString msg)
{
	m_listCtrl.InsertItem(0, msg);
}
