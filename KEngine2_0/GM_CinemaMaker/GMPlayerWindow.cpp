#include "GMPlayerWindow.h"



int GMPlayerWindow::set_window(
	_In_ HINSTANCE _hInstance, 
	KWindow* _Parent)
{
	MyInstance = _hInstance;

	WndClass.cbClsExtra = 0; // ���� �޸�
	WndClass.cbWndExtra = 0; // ���� �޸�
	WndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH); // �� �ڸ� ĥ�� ��
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW); // Ŀ�� ���
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION); // ���� ������ ������
	WndClass.hInstance = _hInstance; // �ν��Ͻ�
	WndClass.lpfnWndProc = PlayerProc; // ���ν��� �Լ� ������
	WndClass.lpszClassName = KName::sName.c_str(); // ������ �̸�
	WndClass.lpszMenuName = NULL; // �޴� �ְ� �� �ų�
	WndClass.style = CS_HREDRAW | CS_VREDRAW; // âũ�� ���Ҷ� �׸��ų�

	RegisterClass(&WndClass);

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
