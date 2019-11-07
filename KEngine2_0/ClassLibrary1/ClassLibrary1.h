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

#include <KSceneManager.h>
#include <KPathManager.h>

using namespace System;

namespace ClassLibrary1 {
	public ref class Class1
	{
		// TODO: 여기에 이 클래스에 대한 메서드를 추가합니다.
	};



	public ref class KSceneClr
	{
	private: 
		KScene* MyScene;

	public:
		KSceneClr() {};
		void operator=(KSceneClr _Other)
		{
			MyScene = _Other.MyScene;
		};
		~KSceneClr() {};

	public:
		void set_scene(KScene* _OtherScebne)
		{
			MyScene = _OtherScebne;
		}
	};
	public ref class KSceneMgrClr
	{
	public:
		KSceneMgrClr() {};
		~KSceneMgrClr() {};
		// TODO: 여기에 이 클래스에 대한 메서드를 추가합니다.


	public:
		void Create()
		{
			KSceneClr ClrScene;
			KScene* TmpScene = KSceneManager::instance()->create_scene();

			ClrScene.set_scene(TmpScene);
		}
	};
}
