#pragma once
#define WINCX 600
#define WINCY 900

#define PURE	= 0
#define PI		3.14f
#define VK_MAX	0xff

#define		OBJ_NOEVENT			0
#define		OBJ_DEAD			1

extern int MyClientID;

extern int P1_SCORE;
extern int P2_SCORE;

enum DIRECTION { DIR_LEFT, DIR_RIGHT, DIR_UP, DIR_DOWN, DIR_LU, DIR_RU, DIR_LD, DIR_RD, DIR_END };
enum OBJ_ID {OBJ_BOSS,OBJ_ENEMY,OBJ_BOSSPART,OBJ_PLAYERBULLET,OBJ_BULLET_ENEMY , OBJ_PLAYER1, OBJ_PLAYER2,OBJ_EXPLOSION, OBJ_BUTTON ,OBJ_UI ,OBJ_FINGER ,OBJ_END };
enum PLAYER_BULLET { PB_NORMAL, PB_LSUB, PB_RSUB, PB_LSIDE, PB_RSIDE, PB_END };
enum UISTATE { UI_ANIM, UI_NONANIM, UI_SCORE,UI_END_SCORE,UI_LIFE ,UI_END };
enum ENEMY_BULLET { E1, E2R, E2L, E3 };

enum LEVEL_ID : uint8_t { LEVEL_MENU, LEVEL_GAMEPLAY, LEVEL_GAME_END,LEVEL_GAME_OVER ,LEVEL_END };
enum SEND_EVENT_TYPE : uint8_t { S_INIT_DATA , S_PLAYER_CHOICE, S_START, S_MY_PLAYER_MOVE,S_PLAYER_DEAD, S_EVENT_END };
enum RECEIVE_EVENT_TYPE : uint8_t {	R_MY_CLIENT_ID, R_PLAYER_CHOICE, R_LEVEL_CHANGE, R_OTHER_PLAYER_MOVE,
	R_MONSTER_GEN, R_BOSS_GEN, R_OBJ_DEAD, R_BOSS_PART_DEAD,R_OTHER_PLAYER_DEAD,R_GAME_OVER,R_EVENT_END};
enum PLAYERID {PLAYER_1,PLAYER_2,PLAYER_END};
enum KEY_MOVE : uint8_t { MOVE_LEFT, MOVE_RIGHT, MOVE_UP, MOVE_DOWN, MOVE_END };

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
	uint8_t data[12];

};

struct S_InitDataPacket {

	bool Connected;

};

struct S_PlayerChoicePacket {

	uint8_t Choiced_Character;
};

struct S_GamePlayStartPacket {

	bool Connected;

};


struct S_MyPlayer_MovePacket {

	float fx;
	float fy;
	int	iFrameCnt;
};

struct S_MyPlayerDeadPacket {
	bool isDead;
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


struct R_PlayerChoicePacket {

	uint8_t Choiced_Character;
};

struct R_MonsterInitPosPacket {

	int	Kind;
	float	fx;
	float	fy;

};

struct R_Other_Player_MovePacket {

	float fx;
	float fy;
	int	iFrameCnt;
};

struct R_BossGenPacket {

	bool isGen;

};

struct R_OtherPlayerDeadPacket {

	bool isDead;

};

struct ReceiveDataResult {
	RECEIVE_EVENT_TYPE eventType;
	void* data;
};

struct R_GameOverPacket {

	bool isOver;
};

struct RecvQueue_data {
	RECEIVE_EVENT_TYPE event;
	uint8_t data[12];
};


#pragma endregion For Server