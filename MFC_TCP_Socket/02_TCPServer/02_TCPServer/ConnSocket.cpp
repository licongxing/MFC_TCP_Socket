// ConnSocket.cpp : 实现文件
//

#include "stdafx.h"
#include "02_TCPServer.h"
#include "ConnSocket.h"

#include "02_TCPServerDlg.h"

// CConnSocket

CConnSocket::CConnSocket(CMy02_TCPServerDlg* dlg)
{
	m_dlg = dlg;
}

CConnSocket::~CConnSocket()
{
}


// CConnSocket 成员函数

// 当服务器和客户端成功建立好连接，服务器端自动调用此函数
void CConnSocket::OnSend(int nErrorCode)
{
	// 本函数由框架调用，通知套接字现在可以调用Send成员函数发送数据了。
	char buf[] = "your connect success";
	Send(buf, strlen(buf)); //给客户端发送信息
	CSocket::OnSend(nErrorCode);
}

// 当对方发送消息，自动调用此函数
// 可以在函数内容做接收处理
void CConnSocket::OnReceive(int nErrorCode)
{
	// 本函数由框架调用，通知套接字缓冲中有数据，可以调用Receive成员函数取出
	char recvBuf[512] = { 0 };
	int recvLen = this->Receive(recvBuf, sizeof(recvBuf));
	CString msg;
	SYSTEMTIME t;
	GetLocalTime(&t);
	msg.Format(_T("[%d:%d:%d] %s:%d: %s"),t.wHour,t.wMinute,t.wSecond, m_ip, m_port,CString(recvBuf));
	m_dlg->AddMsg(msg);
	// 回射信息
	CharUpperA(recvBuf);
	this->Send(recvBuf, strlen(recvBuf));
}

// 对方主动断开连接，自动调用此函数
void CConnSocket::OnClose(int nErrorCode)
{
	CString msg;
	SYSTEMTIME t;
	GetLocalTime(&t);
	msg.Format(_T("[%d:%d:%d] %s:%d: already close!"), t.wHour,t.wMinute,t.wSecond,m_ip, m_port);
	m_dlg->AddMsg(msg);
	CSocket::OnClose(nErrorCode);
}

void CConnSocket::SetClientAddr(CString ip, USHORT port)
{
	m_ip = ip;
	m_port = port;
}
