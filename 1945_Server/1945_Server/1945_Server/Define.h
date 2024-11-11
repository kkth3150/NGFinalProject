#pragma once
#include <windows.h>
#include <cstdint>

#define PURE	= 0
#define PI		3.14f
#define VK_MAX	0xff

#define		OBJ_NOEVENT			0
#define		OBJ_DEAD			1

#define SERVERPORT 9000
#define BUFSIZE 512

enum LEVEL_ID : uint8_t { LEVEL_MENU, LEVEL_GAMEPLAY, LEVEL_GAME_END, LEVEL_END };
enum SEND_EVENT_TYPE : uint8_t { S_PLAYER_CHOICE, S_KEY_INPUT, S_EVENT_END };
enum RECEIVE_EVENT_TYPE : uint8_t { R_PLAYER_CHOICE, R_LEVEL_CHANGE, R_EVENT_END };
enum CLIENT_ID{CLIENT_1,CLIENT_2,CLIENT_END};

template<typename T>
void Safe_Delete(T& Temp)
{
	if (Temp)
	{
		delete Temp;
		Temp = nullptr;
	}
}

class CDeleteObj
{
public:
	template<typename T>
	void operator()(T& Temp)
	{
		if (Temp)
		{
			delete Temp;
			Temp = nullptr;
		}
	}
};

class CDeleteMap
{
public:
	template<typename T>
	void operator()(T& MyPair)
	{
		if (MyPair.second)
		{
			delete MyPair.second;
			MyPair.second = nullptr;
		}
	}
};


class CTagFinder
{
public:
	CTagFinder(const TCHAR* pKey) : m_pKey(pKey) {}

public:
	template<typename T>
	bool	operator()(T& Pair)
	{
		if (!lstrcmp(m_pKey, Pair.first))
			return true;

		return false;
	}

private:
	const TCHAR* m_pKey;
};

struct SendHeaderPacket {
	uint8_t length; // 두 번째 데이터의 길이
	SEND_EVENT_TYPE event; // 이벤트 타입
};


struct S_PlayerChoicePacket {

	uint8_t Choiced_Character;
};

struct S_KeyInputPacket {

	bool Left;
	bool Right;
	bool Up;
	bool Down;
	bool Shoot;
};

//
//For Receive

struct RecvHeaderPacket {
	uint8_t length; // 두 번째 데이터의 길이
	SEND_EVENT_TYPE event; // 이벤트 타입
};

struct R_LevelChangePacket {

	LEVEL_ID Level;
};

struct  R_PlayerMovePacket {

	bool Player_ID;
	float X;
	float Y;

};

struct R_PlayerChoicePacket {

	uint8_t Choiced_Character_P1;
	uint8_t Choiced_Character_P2;
};

struct ReceiveDataResult {
	RECEIVE_EVENT_TYPE eventType;
	void* data;
};

#pragma endregion For Server