#pragma once

class SocketRecipient
{
public:
	SocketRecipient();
	~SocketRecipient();

	virtual void OnAccept(const CString& ipAddress, UINT port, int errorCode) = 0;
	virtual void OnReceive(const CString& ipAddress, UINT port, const CString& msg, int errorCode) = 0;
	virtual void OnClose(const CString& ipAddress, UINT port, int errorCode) = 0;
};

