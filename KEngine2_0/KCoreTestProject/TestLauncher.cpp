#include <KCore.h>
#include <crtdbg.h>

#include "TestInitiator.h"
#include "TestUpdator.h"
#include "TestReleaser.h"
#include "TestWindow.h"


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

#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")


#define MAX_LOADSTRING 100

HWND hWnd;

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: 여기에 코드를 입력합니다.

	// 전역 문자열을 초기화합니다.

	TestWindow* Newwindow = new TestWindow;
	Newwindow->set_window(hInstance, lpCmdLine, nCmdShow);
	Newwindow->size({ 800, 600 });

	return core_launch<TestInitiator, TestUpdator, TestReleaser>(Newwindow);
}