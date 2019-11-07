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
#include <KSoundPlayer.h>

namespace KCoreClr {

	template<typename T>
	public ref class KResourceMgr
	{
		// TODO: 여기에 이 클래스에 대한 메서드를 추가합니다.
	public:
		KResourceMgr() {};
		~KResourceMgr() {};

	public:
		void load_all(const wchar_t* _Forder)
		{
			KResourceManager<T>::instance()->load_forder(_Forder);
		}
	};
}