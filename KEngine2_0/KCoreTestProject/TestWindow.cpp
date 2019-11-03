#include "TestWindow.h"
#include <KWindowManager.h>
#include <KSceneManager.h>
#include <KScene.h>
#include <KMacro.h>
#include <KCore.h>

#include <OhMohCommon.h>

TestWindow::TestWindow()
{
}


TestWindow::~TestWindow()
{
}


void TestWindow::init()
{
	KWindow::init();
}
void TestWindow::update()
{
	KWindow::update();
}


int TestWindow::set_window(
	_In_ HINSTANCE _hInstance,
	_In_ LPWSTR    _lpCmdLine,
	_In_ int       _nCmdShow)
{
	MyInstance = _hInstance;
	MyCmd = _lpCmdLine;
	MyiCmd = _nCmdShow;

	WndClass.cbClsExtra = 0; // ���� �޸�
	WndClass.cbWndExtra = 0; // ���� �޸�
	WndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH); // �� �ڸ� ĥ�� ��
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW); // Ŀ�� ���
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION); // ���� ������ ������
	WndClass.hInstance = _hInstance; // �ν��Ͻ�
	WndClass.lpfnWndProc = this->WndProc; // ���ν��� �Լ� ������
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


LRESULT CALLBACK TestWindow::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
	{
		SetTimer(hWnd, 1, 10, NULL);
		MoveWindow(hWnd, 100, 100, (int)MyWinSize.x, (int)MyWinSize.y, TRUE);
		return 0;
	}
	case WM_SOCKET:
	{
		int addrlen = 0;
		int retval = 0;

		if (WSAGETSELECTERROR(lParam))
		{
			int err_code = WSAGETSELECTERROR(lParam);
			return 0;
		}

		switch (WSAGETSELECTEVENT(lParam))
		{
		case FD_READ:
		{
			char szBuf[KBUFSIZE];

			retval = recv(wParam, szBuf, KBUFSIZE, 0);
			if (retval == SOCKET_ERROR)
			{
				if (WSAGetLastError() != WSAEWOULDBLOCK)
				{
					//cout << "err on recv!!" << endl;
				}
			}
			KSceneManager::instance()->process_packet<PACKET_HEADER>(szBuf, retval);
		}
		}
	}
	break;
	case FD_CLOSE:
	{
		closesocket(wParam);
		break;
	}

	return 0;

	case WM_GETMINMAXINFO:
	{
		((MINMAXINFO*)lParam)->ptMaxTrackSize.x = (LONG)MyWinSize.x;
		((MINMAXINFO*)lParam)->ptMaxTrackSize.y = (LONG)MyWinSize.y;
		((MINMAXINFO*)lParam)->ptMinTrackSize.x = (LONG)MyWinSize.x;
		((MINMAXINFO*)lParam)->ptMinTrackSize.y = (LONG)MyWinSize.y;

		return FALSE;
	}
	case WM_TIMER:
	{
		// KCore::instance()->loop();
		break;
	}

	case WM_DESTROY:
		KSocketManager<PACKET_HEADER>::instance()->release();
		KCore::instance()->shut_down();
		PostQuitMessage(0);
		break;


	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}