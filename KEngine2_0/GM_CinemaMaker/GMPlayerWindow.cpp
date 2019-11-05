#include "GMPlayerWindow.h"



int GMPlayerWindow::set_window(
	_In_ HINSTANCE _hInstance, 
	KWindow* _Parent)
{
	MyInstance = _hInstance;
	KName::sName = L"Player Window";

	WNDCLASS NewWnd = WNDCLASS();
	WndClass = NewWnd;

	NewWnd.cbClsExtra = 0; // 여분 메모리
	NewWnd.cbWndExtra = 0; // 여분 메모리
	NewWnd.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH); // 맨 뒤를 칠할 색
	NewWnd.hCursor = LoadCursor(NULL, IDC_ARROW); // 커서 모양
	NewWnd.hIcon = LoadIcon(NULL, IDI_APPLICATION); // 왼쪽 귀퉁이 아이콘
	NewWnd.hInstance = _hInstance; // 인스턴스
	NewWnd.lpfnWndProc = PlayerProc; // 프로시져 함수 포인터
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

	return (int)Message.wParam;
}


LRESULT CALLBACK GMPlayerWindow::PlayerProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
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
		PostQuitMessage(0);
	}
	break;


	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
