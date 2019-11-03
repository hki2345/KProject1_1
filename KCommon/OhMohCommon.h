#pragma once
#include <KMacro.h>
#pragma pack(1)


#include <Windows.h>

#define ROOMCOUNT (6)
#define USERCOUNT (30)


#define VOIDSTONE 5
#define BLACKSTONE 0
#define WHITESTONE 1

#define OHMOKFONT  L"12롯데마트행복Bold"

enum PACKET_INDEX
{
	PACKET_INDEX_LOGIN_RET = 1,
	PACKET_INDEX_USER_DATA,
	PACKET_INDEX_SEND_ROOMINITDATA,
	PACKET_INDEX_SEND_ROOMDATA,
	PACKET_INDEX_SEND_ROOMINDATA,
	PACKET_INDEX_SEND_ROOMOUTDATA,
	PACKET_INDEX_SEND_GAMEDATA,
	PACKET_INDEX_SEND_PANCALL,
	PACKET_INDEX_SEND_PANDATA,
	PACKET_INDEX_SEND_CHATDATA,
};

struct PACKET_HEADER
{
	WORD wIndex;
	WORD wLen;
};

struct USER_DATA
{
	char szPlayerNAME[KNAMING];
};

struct ROOM_DATA
{
	SOCKET iPlayerID;
	WORD iRoomID;
	WORD iPlayerCount;
};

struct GAME_DATA
{
	SOCKET iPlayerID;
	WORD iRoomNumber;
	WORD wX;
	WORD wY;
	bool bisBlackStone;
	bool bisCorrectTurn;
};

struct PAN_DATA
{
	BYTE PanData[KHALFBUFSIZE];
};

struct CHAT_DATA
{
	SOCKET iPlayerID;
	char szPlayerNAME[KNAMING];
	char sChat[KPATHBUFSIZE];
};




struct PACKET_LOGIN_RET
{
	PACKET_HEADER header;
	SOCKET iPlayerId;
	char szPlayerNAME[KNAMING];
	char szPlayerPASSWARD[KHASH];
};

struct PACKET_USER_DATA
{
	PACKET_HEADER header;
	WORD InRoomID;
	WORD wCount;
	WORD TypeOhmok;
	USER_DATA data[USERCOUNT];
};

struct PACKET_SEND_ROOMINITDATA
{
	PACKET_HEADER header;
	WORD wCount;
	ROOM_DATA data[8];
	WORD wUserCount;
	USER_DATA UserData[USERCOUNT];
};


struct PACKET_SEND_ROOMDATA
{
	PACKET_HEADER header;
	ROOM_DATA data;
};
struct PACKET_SEND_ROOMINDATA
{
	PACKET_HEADER header;
	WORD InRoomID;
};


struct PACKET_SEND_GAMEDATA
{
	PACKET_HEADER header;
	GAME_DATA data;
};

struct PACKET_SEND_PANCALLDATA
{
	PACKET_HEADER header;
	SOCKET iPlayerId;
	WORD RoomID;
};
struct PACKET_SEND_PANDATA
{
	PACKET_HEADER header;
	SOCKET iPlayerID;
	PAN_DATA data;
};
struct PACKET_SEND_CHATDATA
{
	PACKET_HEADER header;
	CHAT_DATA data;
};
struct PACKET_SEND_ROOMOUTDATA
{
	PACKET_HEADER header;
	WORD PlayerIdx;
	bool GiveUpGame;
};

#pragma pack()