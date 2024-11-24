#pragma once
#define WINCX 600
#define WINCY 900

#define PURE	= 0
#define PI		3.14f
#define VK_MAX	0xff

#define		OBJ_NOEVENT			0
#define		OBJ_DEAD			1

extern int MyClientID;

enum DIRECTION { DIR_LEFT, DIR_RIGHT, DIR_UP, DIR_DOWN, DIR_LU, DIR_RU, DIR_LD, DIR_RD, DIR_END };
enum OBJ_ID {OBJ_BOSS, OBJ_BOSSPART, OBJ_ENEMY_1, OBJ_ENEMY_2,OBJ_PLAYERBULLET,OBJ_BULLET_ENEMY , OBJ_PLAYER, OBJ_EXPLOSION, OBJ_BUTTON ,OBJ_UI ,OBJ_FINGER ,OBJ_END };
enum PLAYER_BULLET { PB_NORMAL, PB_LSUB, PB_RSUB, PB_LSIDE, PB_RSIDE, PB_END };
enum UISTATE { UI_ANIM, UI_NONANIM, UI_SCORE,UI_LIFE ,UI_END };
enum ENEMY_BULLET { E1, E2R, E2L, E3 };

enum LEVEL_ID : uint8_t { LEVEL_MENU, LEVEL_GAMEPLAY, LEVEL_GAME_END, LEVEL_END };
enum SEND_EVENT_TYPE : uint8_t { S_INIT_DATA , S_PLAYER_CHOICE, S_KEY_INPUT, S_EVENT_END };
enum RECEIVE_EVENT_TYPE : uint8_t {R_MY_CLIENT_ID ,R_PLAYER_CHOICE,R_LEVEL_CHANGE, R_EVENT_END };
enum PLAYERID {PLAYER_1,PLAYER_2,PLAYER_END};

template<typename T>
void Safe_Delete(T& Temp)
{
	if (Temp)
	{
		delete Temp;
		Temp = nullptr;
	}
}

typedef struct tagInfo
{
	float	fX;		// 중점 X
	float	fY;		// 중점 Y
	float	fCX;	// 가로 사이즈
	float	fCY;	// 세로 사이즈

}INFO;

struct Vector2 {
	float x;
	float y;

	Vector2() : x(0), y(0) {}
	Vector2(float x, float y) : x(x), y(y) {}

	
	Vector2 normalize() const {
		float length = sqrt(x * x + y * y);
		if (length != 0) {
			return Vector2(x / length, y / length);
		}
		return Vector2(0, 0);
	}
};

typedef struct tagFrame
{
	int		iFrameStart;
	int		iFrameEnd;
	int		iMotion;
	DWORD	dwSpeed;
	DWORD	dwTime;

}FRAME;

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



extern HWND g_hWnd;

#pragma region For Server

//For Send

struct SendHeaderPacket {
	uint8_t length; // 두 번째 데이터의 길이
	SEND_EVENT_TYPE event; // 이벤트 타입
};

struct SendQueue_data {

	SEND_EVENT_TYPE event;          
	uint8_t data[10];

};

struct S_InitDataPacket {

	bool Connected;

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
	RECEIVE_EVENT_TYPE event; // 이벤트 타입
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


struct RecvQueue_data {

	RECEIVE_EVENT_TYPE event;
	uint8_t data[sizeof(R_LevelChangePacket)];

};


#pragma endregion For Server