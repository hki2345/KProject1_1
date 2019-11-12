#pragma once

#if _DEBUG
#if Win32
#pragma comment(lib, "KCore_Debug32")
#elif x64
#pragma comment(lib, "KCore_Debug64")
#endif // WIN32

#else
#if Win32
#pragma comment(lib, "KCore_Release32")
#elif x64
#pragma comment(lib, "KCore_Release64")
#endif
#endif

#include <KResourceManager.h>
#include <KWindow.h>

namespace KCoreClr {

	public ref class Class1 
	{
		// TODO: 여기에 이 클래스에 대한 메서드를 추가합니다.
	};

	public ref class KWin
	{
	public:
		KWin() {};
		~KWin() {};
		// TODO: 여기에 이 클래스에 대한 메서드를 추가합니다.


	public:
		KWindow* Create(const System::String^ _Name)
		{
			return nullptr;// KSceneManager::instance()->create_scene((KPathManager::instance()->char_towchar(_Name).c_str()));
		}
	};
}