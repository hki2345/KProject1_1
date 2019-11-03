#pragma once
#include <KWindow.h>

class TestWindow : public KWindow
{
public:
	TestWindow();
	~TestWindow();

protected:
	void init() override;
	void update() override;

public:
	int set_window(
		_In_ HINSTANCE _hInstance,
		_In_ LPWSTR    _lpCmdLine,
		_In_ int       _nCmdShow) override;

private:
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

