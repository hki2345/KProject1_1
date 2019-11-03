#include "KEngineinitiator.h"
#include "KEngineUpdater.h"
#include "KEngineReleaser.h"
#include <KPathManager.h>

#include <math.h>
#include <vector>

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
	core_launch<KEngineinitiator, KEngineUpdater, KEngineReleaser>(hInstance, lpCmdLine, nCmdShow);
}

//int main(int argc, wchar_t* argv[])
//{
//	// 위에껀 업데이터까지 장착 - 루프 돌때마다 업데이터까지 실행 된다.
//	// 단, 많이쓰진 않을듯
//	// core_launch<KEngineinitiator, KEngineUpdater>(argc, argv);
//	core_launch<KEngineinitiator>(argc, argv);
//	return 0;
//}