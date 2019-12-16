#pragma once
//#define _WINSOCK_DEPRECATED_NO_WARNINGS 1
#include  "ConnSocket.h"

#include <list>
using namespace std;
// CServerSocket 命令目标
class CMy02_TCPServerDlg;
class CServerSocket : public CSocket
{
public:
	CServerSocket(CMy02_TCPServerDlg* dlg = NULL);
	virtual ~CServerSocket();
	// 接受到客户端连接的 回调函数
	virtual void OnAccept(int nErrorCode);
	// 关闭所有连接套接字
	void CloseAllConn();
private:
	CMy02_TCPServerDlg* m_dlg;
	list<CConnSocket*> m_clientList;
public:
};


