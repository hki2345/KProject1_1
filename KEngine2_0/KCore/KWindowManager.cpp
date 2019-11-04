#include "KWindowManager.h"
#include "KWindow.h"

#include "KMacro.h"




#include <Fmod/fmod.hpp>
#include <Fmod/common.h>


bool KWindowManager::init(
	_In_ HINSTANCE _hInstance,
	_In_ LPWSTR    _lpCmdLine,
	_In_ int       _nCmdShow)
{
	FMOD::System* system;
	FMOD_RESULT       result;
	unsigned int      version;
	void* extradriverdata = 0;
	FMOD::Channel* channel = 0;


	result = FMOD::System_Create(&system);
	result = system->getVersion(&version);
	result = system->init(32, FMOD_INIT_NORMAL, extradriverdata);

	FMOD::Sound* sound1 = nullptr;
	result = system->createSound("drumloop.wav", FMOD_DEFAULT, nullptr, &sound1);
	result = system->playSound(sound1, 0, false, &channel);




	hInst = _hInstance;
	WCmdLine = _lpCmdLine;
	iCmdShow = _nCmdShow;
	return true;
}

bool KWindowManager::init(KWindow* _Window)
{
	hInst = _Window->MyInstance;
	WCmdLine = _Window->MyCmd;
	iCmdShow = _Window->MyiCmd;

	_Window->show_window();
	MapWindow.insert(std::make_pair(_Window->sName, _Window));
	return true;
}


void KWindowManager::init()
{
	std::map<std::wstring, KWindow*>::iterator SIter = MapWindow.begin();
	std::map<std::wstring, KWindow*>::iterator EIter = MapWindow.end();

	for (; SIter != EIter; ++SIter)
	{
		SIter->second->init();
	}
}


void KWindowManager::update()
{
	std::map<std::wstring, KWindow*>::iterator SIter = MapWindow.begin();
	std::map<std::wstring, KWindow*>::iterator EIter = MapWindow.end();

	for (; SIter != EIter; ++SIter)
	{
		SIter->second->update();

		// Ãæµ¹ ¾îÂ¼±¸ ;;
		SIter->second->render();
	}
}


void KWindowManager::release()
{
	std::map<std::wstring, KWindow*>::iterator SIter = MapWindow.begin();
	std::map<std::wstring, KWindow*>::iterator EIter = MapWindow.end();

	for (; SIter != EIter; ++SIter)
	{
		SIter->second->release();
		RELEASE_PTR(SIter->second);
	}

	MapWindow.clear();
	RELEASE_PTR(KSingleton::MyPtr);
}

void KWindowManager::backcolor(const COLORREF& _Color)
{
	std::map<std::wstring, KWindow*>::iterator SIter = MapWindow.begin();
	std::map<std::wstring, KWindow*>::iterator EIter = MapWindow.end();

	for (; SIter != EIter; ++SIter)
	{
		SIter->second->BackColor = _Color;
	}
}



int KWindowManager::create_window(const wchar_t* _Name, const KSize2& _Size /*= KSize2::Zero*/)
{
	KWindow* NewWindow = new KWindow();
	NewWindow->sName = _Name;
	NewWindow->MyInstance = hInst;

	NewWindow->create();
	NewWindow->show_window();
	MapWindow.insert(std::make_pair(_Name, NewWindow));

	return true;
}

int KWindowManager::create_window(HWND _Name, const KSize2& _Size /*= KSize2::Zero*/)
{
	KWindow* NewWindow = new KWindow();
	NewWindow->sName = L"Custom";
	NewWindow->hMainDC = GetDC(_Name);
	NewWindow->MyhWnd = _Name;

	if (_Size == KSize2::Zero)
	{
		RECT rc;
		GetClientRect(_Name, &rc);
		NewWindow->MyWinSize.x = (float)rc.right;
		NewWindow->MyWinSize.y = (float)rc.bottom;
	}
	else
	{
		NewWindow->MyWinSize = _Size;
	}
	
	MapWindow.insert(std::make_pair(L"Custom", NewWindow));

	return 0;
}

KWindow* KWindowManager::window(const int& _Idx /*= 0*/)
{
	int Cnt = 0;

	std::map<std::wstring, KWindow*>::iterator SIter = MapWindow.begin();
	std::map<std::wstring, KWindow*>::iterator EIter = MapWindow.end();
	for (; SIter != EIter; SIter++)
	{
		if (Cnt == _Idx)
		{
			return SIter->second;
		}

		++Cnt;
	}

	return nullptr;
}

HDC& KWindowManager::back_hdc()
{
	return MapWindow.begin()->second->bhdc();
}
HDC& KWindowManager::main_hdc()
{
	return MapWindow.begin()->second->hdc();
}
HWND& KWindowManager::main_hwnd()
{
	return MapWindow.begin()->second->hwnd();
}
KSize2& KWindowManager::main_size()
{
	return MapWindow.begin()->second->MyWinSize;
}