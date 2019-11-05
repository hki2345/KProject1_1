#include <KCore.h>
#include <KWindowManager.h>

#include "GMMainWindow.h"
#include "GMPlayerWindow.h"

void GMMainWindow::init()
{
	KWindow::init();

	KName::sName = L"Main Window";
	init_player();
}
void GMMainWindow::update()
{
	KWindow::update();
}

void GMMainWindow::init_player()
{
	PlayerWnd = new GMPlayerWindow();

	KWindowManager::instance()->create_window(L"Player Window", PlayerWnd);
	PlayerWnd->size({ 1000, 180 });
	PlayerWnd->set_color(RGB(122, 122, 122));
	PlayerWnd->set_window(MyInstance, this);
	PlayerWnd->show_window();

	int MaxX = 400;
	int MaxY = 650;

	CreateWindow(TEXT("button"), TEXT("Play"), WS_CHILD | WS_VISIBLE |
		BS_PUSHBUTTON, MaxX - 240, MaxY, 100, 25, PlayerWnd->hwnd(), (HMENU)10000, MyInstance, NULL);
	CreateWindow(TEXT("button"), TEXT("Pause"), WS_CHILD | WS_VISIBLE |
		BS_PUSHBUTTON, MaxX - 120, MaxY, 100, 25, PlayerWnd->hwnd(), (HMENU)10001, MyInstance, NULL);
	CreateWindow(TEXT("button"), TEXT("Stop"), WS_CHILD | WS_VISIBLE |
		BS_PUSHBUTTON, MaxX - 0, MaxY, 100, 25, PlayerWnd->hwnd(), (HMENU)10002, MyInstance, NULL);
}

void GMMainWindow::init_transform()
{
}

void GMMainWindow::init_shader()
{
}

void GMMainWindow::init_edit()
{
}

void GMMainWindow::release()
{
	KWindow::release();
}

int GMMainWindow::set_window(
	_In_ HINSTANCE _hInstance,
	_In_ LPWSTR    _lpCmdLine,
	_In_ int       _nCmdShow)
{
	MyInstance = _hInstance;
	MyCmd = _lpCmdLine;
	MyiCmd = _nCmdShow;

	WNDCLASS NewWnd = WNDCLASS();
	WndClass = NewWnd;
	
	
	NewWnd.cbClsExtra = 0; // 여분 메모리
	NewWnd.cbWndExtra = 0; // 여분 메모리
	NewWnd.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH); // 맨 뒤를 칠할 색
	NewWnd.hCursor = LoadCursor(NULL, IDC_ARROW); // 커서 모양
	NewWnd.hIcon = LoadIcon(NULL, IDI_APPLICATION); // 왼쪽 귀퉁이 아이콘
	NewWnd.hInstance = _hInstance; // 인스턴스
	NewWnd.lpfnWndProc = this->MainProc; // 프로시져 함수 포인터
	NewWnd.lpszClassName = KName::sName.c_str(); // 윈도우 이름
	NewWnd.lpszMenuName = NULL; // 메뉴 있게 할 거냐
	NewWnd.style = CS_HREDRAW | CS_VREDRAW; // 창크기 변할때 그릴거냐

	RegisterClass(&NewWnd);

	MyhWnd = CreateWindow(
		KName::sName.c_str(),
		KName::sName.c_str(),
		WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
		// 띄우는 위치 - 크기
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL, (HMENU)NULL, _hInstance, NULL);


	RECT rc;
	GetClientRect(MyhWnd, &rc);

	MyWinSize.x = (float)rc.right;
	MyWinSize.y = (float)rc.bottom;

	hMainDC = GetDC(MyhWnd);

	UnregisterClass(KName::sName.c_str(), MyInstance);

	return (int)Message.wParam;
}


LRESULT CALLBACK GMMainWindow::MainProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_GETMINMAXINFO:
	{
		((MINMAXINFO*)lParam)->ptMaxTrackSize.x = (LONG)MyWinSize.x;
		((MINMAXINFO*)lParam)->ptMaxTrackSize.y = (LONG)MyWinSize.y;
		((MINMAXINFO*)lParam)->ptMinTrackSize.x = (LONG)MyWinSize.x;
		((MINMAXINFO*)lParam)->ptMinTrackSize.y = (LONG)MyWinSize.y;
	}
	break;

	case WM_DESTROY:
	{
		KCore::instance()->shut_down();
		PostQuitMessage(0);
	}
	break;


	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
