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

#include "KBitMap.h"


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


void KCore::init()
{
	looping = true;
	KResourceManager<KBitMap>::instance()->init();

	KSceneManager::instance()->init();
	KPathManager::instance()->init();
	KTimeManager::instance()->init();
	KDebugManager::instance()->init();
}

void KCore::init(
	_In_ HINSTANCE _hInstance,
	_In_ LPWSTR    _lpCmdLine,
	_In_ int       _nCmdShow)
{
	looping = true;
	KResourceManager<KBitMap>::instance()->init();
	KFileStream::instance();

	KWindowManager::instance()->init(_hInstance, _lpCmdLine, _nCmdShow);

	KPathManager::instance()->init();
	KTimeManager::instance()->init();
	KWindowManager::instance()->create_window(L"Main");
	KWindowManager::instance()->init();
	KDebugManager::instance()->init();
}

void KCore::init(KWindow* _Window)
{
	looping = true;
	KResourceManager<KBitMap>::instance()->init();
	KFileStream::instance();

	KWindowManager::instance()->init(_Window);

	KPathManager::instance()->init();
	KTimeManager::instance()->init();
	KWindowManager::instance()->init();
	KDebugManager::instance()->init();
}


void KCore::init(HWND _hWnd, const KSize2& _Size /*= KSize2::Zero*/)
{
	looping = true;
	KResourceManager<KBitMap>::instance()->init();
	KFileStream::instance();

	KPathManager::instance()->init();
	KTimeManager::instance()->init();
	KWindowManager::instance()->create_window(_hWnd, _Size);
	KWindowManager::instance()->init();
	KDebugManager::instance()->init();
}

void KCore::loop()
{
	while (looping)
	{
		progress();
	}

	release();
}

void KCore::loop_updater()
{
	while (looping)
	{
		progress();
		pUpdater->update();
	}

	RELEASE_PTR(pUpdater);
	release();
}







void KCore::progress()
{
	KWindowManager::instance()->update();
}

void KCore::release()
{
	KResourceManager<KBitMap>::instance()->release();

	KDebugManager::instance()->release();
	KPathManager::instance()->release();
	KTimeManager::instance()->release();
	KInputManager::instance()->release();
	KWindowManager::instance()->release();
	KFileStream::instance()->release();
	RELEASE_PTR(KSingleton::instance()->MyPtr);
}