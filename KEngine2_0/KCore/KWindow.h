#pragma once
#include <Windows.h>

#include "KVector.h"
#include "KName.h"


#pragma comment(lib, "Ws2_32.lib")

class KBitMap;
class KWindow : public KName
{
public:
	KWindow();
	~KWindow();

public:
	friend class KWindowManager;


protected:
	static KVec2 MyWinSize;
	KVec2 MyClientSize;
	MSG Message;
	HDC hMainDC;
	HDC hBackDC;

	HINSTANCE MyInstance;
	LPWSTR MyCmd;
	int MyiCmd;

	HWND MyhWnd;
	WNDCLASS WndClass;
	KBitMap* BackBitMap;
	
	COLORREF BackColor;

protected:
	virtual void init();
	virtual void update();
	virtual void render();
	virtual void release();
	virtual int create();

public:
	virtual int set_window(
		_In_ HINSTANCE _hInstance,
		_In_ LPWSTR    _lpCmdLine,
		_In_ int       _nCmdShow) { return 0; };

public:
	BOOL show_window();

private:
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);


public:
	void set_clienttowindow(const KSize2& _Size);
	void size(const KSize2& _Size);
	void client_size(const KSize2& _Size);

	inline KSize2& client_size()
	{
		return MyClientSize;
	}

	inline KSize2& size()
	{
		return MyWinSize;
	}
	inline HDC& bhdc()
	{
		return hBackDC;
	}
	inline HDC& hdc()
	{
		return hMainDC;
	}
	inline HWND& hwnd()
	{
		return MyhWnd;
	}
	inline HINSTANCE& hinst()
	{
		return MyInstance;
	}
};

