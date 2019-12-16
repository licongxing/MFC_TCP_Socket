
// 02_TCPClientDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "ConnSocket.h"

// CMy02_TCPClientDlg 对话框
class CMy02_TCPClientDlg : public CDialogEx
{
// 构造
public:
	CMy02_TCPClientDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MY02_TCPCLIENT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
//	CIPAddressCtrl m_serverIp;
private:
	UINT m_port;
	CIPAddressCtrl m_ip;
	CButton m_connBtn;
	CButton m_disConnBtn;
	CString m_sendBuf;
	CButton m_sendBtn;
	CButton m_clearBtn;
	CListCtrl m_listCtrl;
	CConnSocket m_connSocket;
	bool m_connSuc;
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	// 往消息列表中添加一条消息
	void AddMsg(CString msg);
	
	void MyEnableBtn();
};
