#pragma once
#include <string>
#include <map>

#include <KMacro.h>
#include <KCommon.h>

#define _WINSOCKAPI_
#include <WinSock2.h>
#include <Windows.h>



struct SOCKETINFO
{
	OVERLAPPED overlapped;
	SOCKET sock;
	char buf[KBUFSIZE + 1];
	int recvbytes;
	WSABUF wsabuf;
};


struct KSocket
{
	char szBuf[KBUFSIZE];
	int len;
};

template <typename SOC>
class KSocketManager : public  KSingleton<KSocketManager<SOC>>
{
private:
	std::map<SOCKET, SOC*> MapSocket;

public:
	void insert_socket(const SOCKET& _Key, SOC* _Info)
	{
		MapSocket.insert(std::make_pair(_Key, _Info));
	}
	std::map<SOCKET, SOC*>* map_socket()
	{
		return &MapSocket;
	}


	void delete_socket(SOC* _Info)
	{
		typename std::map<SOCKET, SOC*>::iterator Siter = MapSocket.begin();
		typename std::map<SOCKET, SOC*>::iterator Eiter = MapSocket.end();

		for (; Siter != Eiter; Siter++)
		{
			if (Siter->second == _Info)
			{
				RELEASE_PTR(Siter->second);
				MapSocket.erase(Siter);
				return;
			}
		}
	}

	void delete_socket(const SOCKET& _Info)
	{
		typename std::map<SOCKET, SOC*>::iterator Siter = MapSocket.begin();
		typename std::map<SOCKET, SOC*>::iterator Eiter = MapSocket.end();

		for (; Siter != Eiter; Siter++)
		{
			if (Siter->first == _Info)
			{
				RELEASE_PTR(Siter->second);
				MapSocket.erase(Siter);
				return;
			}
		}
	}

	void release() override
	{
		typename std::map<SOCKET, SOC*>::iterator Siter = MapSocket.begin();
		typename std::map<SOCKET, SOC*>::iterator Eiter = MapSocket.end();

		for (; Siter != Eiter; Siter++)
		{
			RELEASE_PTR(Siter->second);
		}

		MapSocket.clear();

		RELEASE_PTR(KSingleton<KSocketManager<SOC>>::MyPtr);
	}



	bool check_bytepacket(char* szBuf, int& len, KSocket& _Recv)
	{
		if (len > 0)
		{
			memcpy(&_Recv.szBuf[_Recv.len], szBuf, len);
			_Recv.len += len;
			len = 0;
		}

		if (_Recv.len < sizeof(SOC))
		{
			return false;
		}

		SOC Pac;
		memcpy(&Pac, szBuf, sizeof(Pac));

		if (_Recv.len < Pac.wLen)
		{
			return false;
		}



		memcpy(&_Recv.szBuf, &_Recv.szBuf[Pac.wLen], _Recv.len - Pac.wLen);
		_Recv.len -= Pac.wLen;

		return true;
	}
};

