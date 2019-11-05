#pragma once
#include <KWindow.h>


class GMPlayerWindow;
class GMMainWindow :
	public KWindow
{
public:
	GMMainWindow() {};
	~GMMainWindow() {};

private:
	GMPlayerWindow* PlayerWnd;
	KWindow* TransformWnd;
	KWindow* ShaderWnd;
	KWindow* EditWnd;


private:
	void init() override;
	void update() override;

	void init_player();
	void init_transform();
	void init_shader();
	void init_edit();


	void release() override;

public:
	int set_window(
		_In_ HINSTANCE _hInstance,
		_In_ LPWSTR    _lpCmdLine,
		_In_ int       _nCmdShow) override;

private:
	static LRESULT CALLBACK MainProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

