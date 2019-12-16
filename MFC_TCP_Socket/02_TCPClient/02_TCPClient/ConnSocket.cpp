// ConnSocket.cpp : 实现文件
//

#include "stdafx.h"
#include "02_TCPClient.h"
#include "ConnSocket.h"
#include "02_TCPClientDlg.h"

// CConnSocket

CConnSocket::CConnSocket(CMy02_TCPClientDlg* dlg)
{
	m_dlg = dlg;
}

CConnSocket::~CConnSocket()
{
}

BOOL CConnSocket::Connect(LPCTSTR lpszHostAddress, UINT nHostPort)
{
	m_ip = lpszHostAddress;
	m_port = nHostPort;
	return CAsyncSocket::Connect(lpszHostAddress, nHostPort);
}


// CConnSocket 成员函数

// 连接服务器成功，该函数会被调用
void CConnSocket::OnConnect(int nErrorCode)
{
	// 本函数由框架调用，通知该套接字连接操作已经完成，并且说明连接是成功还是失败了。

	CSocket::OnConnect(nErrorCode);
}


void CConnSocket::OnClose(int nErrorCode)
{
	// 由框架调用通知该套接字，它连接上的对应套接字已经被相关进程终止了
	CString msg;
	SYSTEMTIME t;
	GetLocalTime(&t);
	msg.Format(_T("[%d:%d:%d] %s:%d: already close!"), t.wHour, t.wMinute, t.wSecond, m_ip, m_port);
	m_dlg->AddMsg(msg);
	m_dlg->MyEnableBtn();

	this->Close();
	CSocket::OnClose(nErrorCode);
}


void CConnSocket::OnReceive(int nErrorCode)
{
	// 本函数由框架调用，通知套接字缓冲中有数据，可以调用Receive成员函数取出
	char recvBuf[512] = { 0 };
	int recvLen = this->Receive(recvBuf, sizeof(recvBuf));
	CString msg;
	SYSTEMTIME t;
	GetLocalTime(&t);
	msg.Format(_T("[%d:%d:%d] %s:%d: %s"), t.wHour,t.wMinute, t.wSecond, m_ip, m_port, CString(recvBuf));
	m_dlg->AddMsg(msg);

	CSocket::OnReceive(nErrorCode);
}
