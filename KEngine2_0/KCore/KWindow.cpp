#include "KWindow.h"
#include "KWindowManager.h"
#include "KCore.h"

#include <vector>
#include <KPathManager.h>
#include <KMacro.h>

#include "KSceneManager.h"
#include "KTimeManager.h"


#include <KResourceManager.h>
#include "KBitMap.h"

KSize2 KWindow::MyWinSize = { 800, 600 };

KWindow::KWindow() :
	MyClientSize(KSize2::Zero),
	Message(MSG()),
	hMainDC(nullptr),
	hBackDC(nullptr),

	MyInstance(nullptr),
	MyCmd(nullptr),
	MyiCmd(0),

	MyhWnd(nullptr),
	WndClass(WNDCLASS()),
	BackBitMap(nullptr),

	BackColor(RGB(0,0,0))
{
}


KWindow::~KWindow()
{
}

void KWindow::init()
{
	if (nullptr == BackBitMap)
	{
		BackBitMap = KResourceManager<KBitMap>::instance()->load(L"KCore", L"BackBuffer");
		hBackDC = BackBitMap->kwindow_size(MyClientSize);
	}

	KSceneManager::instance()->kwindow(this);
	KSceneManager::instance()->create();
	KSceneManager::instance()->init();

	BackColor = RGB(0, 0, 0);
}

void KWindow::update()
{
	if (TRUE == PeekMessage(&Message, NULL, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}

	// else
	{
		KTimeManager::instance()->update();
		KSceneManager::instance()->update();
	}
}


void KWindow::render()
{
	//  API Render
	KSceneManager::instance()->render();
	BitBlt(hMainDC, 0, 0, (int)MyClientSize.x, (int)MyClientSize.y, hBackDC, 0, 0, SRCCOPY);

	// ������ ��ĥ
	HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	myBrush = CreateSolidBrush(BackColor);
	HBRUSH oldBrush = (HBRUSH)SelectObject(hBackDC, myBrush);
	Rectangle(hBackDC, 0, 0, (int)MyClientSize.x, (int)MyClientSize.y);
	SelectObject(hBackDC, oldBrush);
	DeleteObject(myBrush);
}

void KWindow::release()
{
	ReleaseDC(MyhWnd, hMainDC);
	KSceneManager::instance()->release();
}




int KWindow::create()
{
	WndClass.cbClsExtra = 0; // ���� �޸�
	WndClass.cbWndExtra = 0; // ���� �޸�
	WndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH); // �� �ڸ� ĥ�� ��
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW); // Ŀ�� ���
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION); // ���� ������ ������
	WndClass.hInstance = KWindowManager::instance()->hinstance(); // �ν��Ͻ�
	WndClass.lpfnWndProc = this->WndProc; // ���ν��� �Լ� ������
	WndClass.lpszClassName = KName::sName.c_str(); // ������ �̸�
	WndClass.lpszMenuName = NULL; // �޴� �ְ� �� �ų�
	WndClass.style = CS_HREDRAW | CS_VREDRAW; // âũ�� ���Ҷ� �׸��ų�

	RegisterClass(&WndClass);

	MyhWnd = CreateWindow(
		KName::sName.c_str(), KName::sName.c_str(), WS_OVERLAPPEDWINDOW,
		// ���� ��ġ - ũ��
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, (HMENU)NULL, KWindowManager::instance()->hinstance(), NULL);


	RECT rc;
	GetClientRect(MyhWnd, &rc);

	MyClientSize.x = (float)rc.right;
	MyClientSize.y = (float)rc.bottom;

	hMainDC = GetDC(MyhWnd);

	return (int)Message.wParam;
}



BOOL KWindow::show_window()
{
	UpdateWindow(MyhWnd);
	return ShowWindow(MyhWnd, KWindowManager::instance()->cmdshow());
}



LRESULT CALLBACK KWindow::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
	{
		MoveWindow(hWnd, 100, 100, (int)MyWinSize.x, (int)MyWinSize.y, TRUE);
		break;
	}
	case WM_GETMINMAXINFO:
	{
		((MINMAXINFO*)lParam)->ptMaxTrackSize.x = (LONG)MyWinSize.x;
		((MINMAXINFO*)lParam)->ptMaxTrackSize.y = (LONG)MyWinSize.y;
		((MINMAXINFO*)lParam)->ptMinTrackSize.x = (LONG)MyWinSize.x;
		((MINMAXINFO*)lParam)->ptMinTrackSize.y = (LONG)MyWinSize.y;

		return FALSE;
	}
	case WM_DESTROY:
		KCore::instance()->shut_down();
		PostQuitMessage(0);
		return 0;
	}
	return (DefWindowProc(hWnd, message, wParam, lParam));
}



void KWindow::size(const KSize2& _Size)
{
	MyWinSize = _Size;
	RECT rc = { 0,0, (LONG)MyWinSize.x, (LONG)MyWinSize.y};
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, false);


	UpdateWindow(MyhWnd);

	GetClientRect(MyhWnd, &rc);

	MyClientSize = KSize2(rc.right, rc.bottom);
}

void KWindow::client_size(const KSize2& _Size)
{
	MyClientSize = _Size;
}

void KWindow::set_clienttowindow(const KSize2& _Size)
{
	MyWinSize = _Size + KSize2(16, 39); // KSize2(GetSystemMetrics(SM_CXVSCROLL), GetSystemMetrics(SM_CYVSCROLL));
	RECT rc = { 0,0, (LONG)MyWinSize.x, (LONG)MyWinSize.y };
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, false);

	MyClientSize = _Size;
}
