
// 02_TCPClientDlg.cpp : 实现文件
//

#include "stdafx.h"
#include <Windows.h>
#include <WinSock2.h>
#include <winerror.h>
#include "02_TCPClient.h"
#include "02_TCPClientDlg.h"
#include "afxdialogex.h"
#include "ConnSocket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy02_TCPClientDlg 对话框



CMy02_TCPClientDlg::CMy02_TCPClientDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MY02_TCPCLIENT_DIALOG, pParent)
	, m_port(0)
	, m_sendBuf(_T(""))
	, m_connSocket(this)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy02_TCPClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_IPADDRESS1, m_serverIp);
	DDX_Text(pDX, IDC_EDIT1, m_port);
	DDX_Control(pDX, IDC_IPADDRESS1, m_ip);
	DDX_Control(pDX, IDC_BUTTON1, m_connBtn);
	DDX_Control(pDX, IDC_BUTTON2, m_disConnBtn);
	DDX_Text(pDX, IDC_EDIT3, m_sendBuf);
	DDX_Control(pDX, IDC_BUTTON3, m_sendBtn);
	DDX_Control(pDX, IDC_BUTTON4, m_clearBtn);
	DDX_Control(pDX, IDC_LIST1, m_listCtrl);
}

BEGIN_MESSAGE_MAP(CMy02_TCPClientDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMy02_TCPClientDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMy02_TCPClientDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CMy02_TCPClientDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CMy02_TCPClientDlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// CMy02_TCPClientDlg 消息处理程序

BOOL CMy02_TCPClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	m_ip.SetAddress(127, 0, 0, 1);
	m_port = 8888;
	UpdateData(FALSE);
	m_disConnBtn.EnableWindow(FALSE);
	m_sendBtn.EnableWindow(FALSE);


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMy02_TCPClientDlg::OnPaint()
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
HCURSOR CMy02_TCPClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


// 连接TCP服务器
void CMy02_TCPClientDlg::OnBnClickedButton1()
{
	UpdateData(TRUE);
	BYTE a, b, c, d;
	m_ip.GetAddress(a, b, c, d);
	CString ip;
	ip.Format(_T("%d.%d.%d.%d"), a, b, c, d);
	BOOL ret = m_connSocket.Create();
	if (ret)
	{
		ret = m_connSocket.Connect(ip, m_port);
		if (ret)
		{
			m_connBtn.EnableWindow(FALSE);
			m_disConnBtn.EnableWindow(TRUE);
			m_sendBtn.EnableWindow(TRUE);
		}
		else
		{
			MessageBox(_T("连接服务器失败"));
			m_connSocket.Close();
		}
	}
	else
	{
		MessageBox(_T("创建套接字失败"));
	}
	
}

// 断开连接
void CMy02_TCPClientDlg::OnBnClickedButton2()
{
	m_connBtn.EnableWindow(TRUE);
	m_disConnBtn.EnableWindow(FALSE);
	m_sendBtn.EnableWindow(FALSE);

	m_connSocket.Close();
}

// 向服务器发送消息
void CMy02_TCPClientDlg::OnBnClickedButton3()
{
	UpdateData(TRUE);
	USES_CONVERSION;
	//函数T2A和W2A均支持ATL和MFC中的字符
	char * send = T2A(m_sendBuf);
	m_connSocket.Send(send, strlen(send));
}

// 清空消息列表
void CMy02_TCPClientDlg::OnBnClickedButton4()
{
	m_listCtrl.DeleteAllItems();
}

void CMy02_TCPClientDlg::AddMsg(CString msg)
{
	m_listCtrl.InsertItem(0, msg);
}

void CMy02_TCPClientDlg::MyEnableBtn()
{
	m_connBtn.EnableWindow(TRUE);
	m_disConnBtn.EnableWindow(FALSE);
}
