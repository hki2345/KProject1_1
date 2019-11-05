#include "GMPlayerWindow.h"



int GMPlayerWindow::set_window(
	_In_ HINSTANCE _hInstance, 
	KWindow* _Parent)
{
	MyInstance = _hInstance;
	KName::sName = L"Player Window";

	WNDCLASS NewWnd = WNDCLASS();
	WndClass = NewWnd;

	NewWnd.cbClsExtra = 0; // ���� �޸�
	NewWnd.cbWndExtra = 0; // ���� �޸�
	NewWnd.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH); // �� �ڸ� ĥ�� ��
	NewWnd.hCursor = LoadCursor(NULL, IDC_ARROW); // Ŀ�� ���
	NewWnd.hIcon = LoadIcon(NULL, IDI_APPLICATION); // ���� ������ ������
	NewWnd.hInstance = _hInstance; // �ν��Ͻ�
	NewWnd.lpfnWndProc = PlayerProc; // ���ν��� �Լ� ������
	NewWnd.lpszClassName = KName::sName.c_str(); // ������ �̸�
	NewWnd.lpszMenuName = NULL; // �޴� �ְ� �� �ų�
	NewWnd.style = CS_HREDRAW | CS_VREDRAW; // âũ�� ���Ҷ� �׸��ų�

	RegisterClass(&NewWnd);

	MyhWnd = CreateWindow(
		KName::sName.c_str(),
		KName::sName.c_str(),
		WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
		// ���� ��ġ - ũ��
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
