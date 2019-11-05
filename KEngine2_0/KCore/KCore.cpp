#include "KMacro.h"
#include "KCore.h"

#include <KResourceManager.h>
#include <KFileStream.h>

#include <KPathManager.h>


#include "KWindowManager.h"
#include "KInputManager.h"
#include "KSceneManager.h"
#include "KTimeManager.h"
#include "KDebugManager.h"
#include "KSoundManager.h"

#include "KBitMap.h"
#include "KSound.h"


#if _DEBUG
#if Win32
#pragma comment(lib, "KContainer_Debug32")
#elif x64
#pragma comment(lib, "KContainer_Debug64")
#endif // WIN32

#else
#if Win32
#pragma comment(lib, "KContainer_Release32")
#elif x64
#pragma comment(lib, "KContainer_Release64")
#endif
#endif


#if Win32
#pragma comment(lib, "fmod_vc_x86")
#elif x64
#pragma comment(lib, "fmod_vc_x64")
#endif



void KCore::init()
{
	looping = true;
	KResourceManager<KBitMap>::instance()->init();
	KResourceManager<KSound>::instance()->init();

	KSceneManager::instance()->init();
	KPathManager::instance()->init();
	KTimeManager::instance()->init();
	KDebugManager::instance()->init();
	KSoundManager::instance()->init();
}

void KCore::init(
	_In_ HINSTANCE _hInstance,
	_In_ LPWSTR    _lpCmdLine,
	_In_ int       _nCmdShow)
{
	looping = true;
	KResourceManager<KBitMap>::instance()->init();
	KResourceManager<KSound>::instance()->init();
	KFileStream::instance();

	KWindowManager::instance()->init(_hInstance, _lpCmdLine, _nCmdShow);

	KPathManager::instance()->init();
	KTimeManager::instance()->init();
	KWindowManager::instance()->create_window(L"Main");
	KWindowManager::instance()->init();
	KDebugManager::instance()->init();
	KSoundManager::instance()->init();
}

void KCore::init(KWindow* _Window)
{
	looping = true;
	KResourceManager<KBitMap>::instance()->init();
	KResourceManager<KSound>::instance()->init();
	KFileStream::instance();

	KWindowManager::instance()->init(_Window);

	KPathManager::instance()->init();
	KTimeManager::instance()->init();
	KWindowManager::instance()->init();
	KDebugManager::instance()->init();
	KSoundManager::instance()->init();
}


void KCore::init(HWND _hWnd, const KSize2& _Size /*= KSize2::Zero*/)
{
	looping = true;
	KResourceManager<KBitMap>::instance()->init();
	KResourceManager<KSound>::instance()->init();
	KFileStream::instance();

	KPathManager::instance()->init();
	KTimeManager::instance()->init();
	KWindowManager::instance()->create_window(_hWnd, _Size);
	KWindowManager::instance()->init();
	KDebugManager::instance()->init();
	KSoundManager::instance()->init();
}

void KCore::loop()
{
	if (false == dxmode)
	{
		while (looping)
		{
			progress_api();
		}
	}

	else
	{
		while (looping)
		{
			progress_dx();
		}
	}

	release();
}

void KCore::loop_updater()
{
	if (false == dxmode)
	{
		while (looping)
		{
			progress_api();
			pUpdater->update();
		}
	}

	else
	{
		while (looping)
		{
			progress_dx();
		}
	}

	RELEASE_PTR(pUpdater);
	release();
}







void KCore::progress_api()
{
	KWindowManager::instance()->update_api();
}

void KCore::progress_dx()
{
	KWindowManager::instance()->update_api();
}

void KCore::release()
{
	KResourceManager<KBitMap>::instance()->release();
	KResourceManager<KSound>::instance()->release();

	KDebugManager::instance()->release();
	KPathManager::instance()->release();
	KTimeManager::instance()->release();
	KInputManager::instance()->release();
	KWindowManager::instance()->release();
	KFileStream::instance()->release();
	KSoundManager::instance()->release();
	RELEASE_PTR(KSingleton::instance()->MyPtr);
}