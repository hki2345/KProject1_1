#pragma once
#include <map>
#include <KCommon.h>
#include <string>

#include "KVector.h"


class KWindow;
class KWindowManager : public KSingleton<KWindowManager>
{
public:
	friend class KCore;

private:
	std::map<std::wstring, KWindow*> MapWindow;
	_In_ HINSTANCE hInst = nullptr;
	_In_ LPWSTR   WCmdLine = nullptr;
	_In_ int      iCmdShow = 0;


private:
	bool init(
		_In_ HINSTANCE _hInstance,
		_In_ LPWSTR    _lpCmdLine,
		_In_ int       _nCmdShow);
	bool init(KWindow* _Window);
	void init();

public:
	// 에디터용
	void update();
	void release() override;

public:
	int create_window(const wchar_t* _Name, const KSize2& _Size = KSize2::Zero);
	int create_window(HWND _Name, const KSize2& _Size = KSize2::Zero);
	
public:
	void backcolor(const COLORREF& _Color);

public:
	KWindow* window(const int& _Idx = 0);
	inline HINSTANCE& hinstance()
	{
		return hInst;
	}
	inline int& cmdshow()
	{
		return iCmdShow;
	}
	HDC& back_hdc();
	HDC& main_hdc();
	HWND& main_hwnd();
	KSize2& main_size();
};

