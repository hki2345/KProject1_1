#include <KPathManager.h>

#include <Windows.h>
#include <math.h>
#include <vector>

#include "BattleCityUpdater.h"
#include "BattleCityInitiator.h"
#include "KCore.h"



#if _DEBUG
#if Win32
#pragma comment(lib, "KCore_Debug32")
#elif x64
#pragma comment(lib, "KCore_Debug64")
#endif // WIN32

#else
#if Win32
#pragma comment(lib, "KCore_Release32")
#elif x64
#pragma comment(lib, "KCore_Release64")
#endif
#endif


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	return core_launch<BattleCityInitiator, BattleCityUpdater>(hInstance, lpCmdLine, nCmdShow);
}