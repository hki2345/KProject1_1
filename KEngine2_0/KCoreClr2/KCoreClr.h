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

#include <msclr\marshal.h>
#include <KResourceManager.h>
#include <KSceneManager.h>
#include <KScene.h>

using namespace msclr::interop;

namespace KCoreClr {

	public ref class KWin
	{
	public:
		KWin() {};
		~KWin() {};
		// TODO: 여기에 이 클래스에 대한 메서드를 추가합니다.


	public:
		void Create(const System::String^ _Name)
		{
			return;// KSceneManager::instance()->create_scene((KPathManager::instance()->char_towchar(_Name).c_str()));
		}
	};

	public ref class XScene
	{
	public:
		XScene() {};
		~XScene() {};

	private:
		KScene* myScene;

	public:
		XScene^ Create(const System::String^ _Name)
		{
			std::wstring tmpStr = marshal_as <std::wstring>(_Name);
			myScene = KSceneManager::instance()->create_scene(tmpStr.c_str());
			
			return this;
		}
	};
}