#pragma once
#include <KWindow.h>


class GMPlayerWindow :
	public KWindow
{
public:
	GMPlayerWindow() {};
	~GMPlayerWindow() {};

public:
	int set_window(
		_In_ HINSTANCE _hInstance,
		KWindow* _Parent);

private:
	static LRESULT CALLBACK PlayerProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

