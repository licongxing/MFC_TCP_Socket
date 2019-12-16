// ServerSocket.cpp : 实现文件
//

#include "stdafx.h"
#include "02_TCPServer.h"
#include "ServerSocket.h"

#include "02_TCPServerDlg.h"

// CServerSocket

CServerSocket::CServerSocket(CMy02_TCPServerDlg* dlg)
{
	m_dlg = dlg;
}

CServerSocket::~CServerSocket()
{
}


// CServerSocket 成员函数

// 新的连接请求来了，该函数将被回调
void CServerSocket::OnAccept(int nErrorCode)
{
	// 由框架调用，通知监听套接字现在可以调用Accept成员函数来接收悬挂的（pending）连接请求。
	CConnSocket * client = new CConnSocket(m_dlg);
	SOCKADDR_IN addr;
	memset(&addr, 0, sizeof(addr));
	int addrLen = sizeof(addr);

	// 获取通信套接字
	Accept(*client,(SOCKADDR*)&addr,&addrLen);
	char* ip = inet_ntoa(addr.sin_addr);
	client->SetClientAddr(CString(ip), addr.sin_port);
	m_clientList.push_back(client);

	// 界面添加连接消息
	CString msg;
	SYSTEMTIME t;
	GetLocalTime(&t);
	msg.Format(_T("[%d:%d:%d] %s:%d: connect success!"),t.wHour,t.wMinute,t.wSecond,CString(ip),addr.sin_port);
	m_dlg->AddMsg(msg);

	CSocket::OnAccept(nErrorCode);
}

void CServerSocket::CloseAllConn()
{
	// 关闭监听套接字，先关闭 连接的套接字
	list<CConnSocket*>::iterator it = m_clientList.begin();
	for (; it != m_clientList.end(); )
	{
		(*it)->Close();
		delete (*it);
		it = m_clientList.erase(it);
	}
	this->Close();
}