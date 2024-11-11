#include "pch.h"
#include "Level_Manager.h"

using namespace std;

const int targetFPS = 30;
const int frameDelay = 1000 / targetFPS;

int main() {


	LARGE_INTEGER frequency;
	LARGE_INTEGER frameStart, frameEnd;
	QueryPerformanceFrequency(&frequency);

	int frameCount = 0;
	DWORD fpsTimer = GetTickCount64();

	CLevel_Manager::Get_Instance()->Level_Change(LEVEL_MENU);

	while (true) {

		QueryPerformanceCounter(&frameStart);

		CLevel_Manager::Get_Instance()->Update();
		CLevel_Manager::Get_Instance()->Late_Update();

		do {
			QueryPerformanceCounter(&frameEnd);
		} while (((frameEnd.QuadPart - frameStart.QuadPart) * 1000.0 / frequency.QuadPart) < frameDelay);

	}

	CLevel_Manager::Get_Instance()->Release();

	return 0;
}
