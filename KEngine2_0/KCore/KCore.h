#pragma once
#include "KWindow.h"

#include "KVector.h"
#include "KDebugManager.h"
#include <KCommon.h>


class KUpdater;
class KCore : public KSingleton<KCore>
{
public:
	class KCoreUpdater
	{
	public:
		KCoreUpdater() {};
		~KCoreUpdater() {};

	public:
		virtual void update() {};
	};

public:
	bool dxmode = false;

private:
	KCore::KCoreUpdater* pUpdater = nullptr;
	bool looping = false;


private:
	void init(
		_In_ HINSTANCE _hInstance,
		_In_ LPWSTR    _lpCmdLine,
		_In_ int       _nCmdShow);
	void init();
	void init(KWindow* _Window);


private:
	void release() override;

public:
	// �ֿܼ� ���� 1ȸ ����
	template <typename INIT>
	void init(int argc, wchar_t* argv[])
	{
		KCore::init();

		INIT OneInit;
		OneInit.init();
	}

	// ������� ������
	template <typename INIT>
	void init(
		_In_ HINSTANCE _hInstance,
		_In_ LPWSTR    _lpCmdLine,
		_In_ int       _nCmdShow)
	{
		KCore::init(_hInstance, _lpCmdLine, _nCmdShow);
		
		INIT OneInit;
		OneInit.init();
	}

	// K������� ������
	template <typename INIT>
	void init(KWindow* _Window)
	{
		KCore::init(_Window);

		INIT OneInit;
		OneInit.init();
	}
	



	// ������� ������ - �̹� �ִ� �����쿡 ���� �뵵
	void init(HWND _hWnd, const KSize2& _Size = KSize2::Zero);


	// �ֽ�ȭ
	template <typename UP>
	void loop()
	{
		pUpdater = new UP;
		if (nullptr == pUpdater)
		{
			return;
		}

		loop_updater();
	}

	// �ֽ�ȭ �� �ʱ�ȭ
	template <typename UP, typename RELEASE>
	void loop()
	{
		pUpdater = new UP;
		if (nullptr == pUpdater)
		{
			return;
		}

		loop_updater();


		RELEASE OneRelease;
		OneRelease.release();
	}

	// �ھ� �ֽ�ȭ ������ �ִ� ��� �� �ƴѰ��...
	void loop();
	void loop_updater();
	inline void shut_down()
	{
		looping = false;
	}

	// �̰͵� ������ ����
	inline void shut_downedit()
	{
		looping = false;
		release();
	}


private:
	void progress_api();
	void progress_dx();
};



/******************** Console ********************/
// ���� �ܰ� ������
template<typename INIT>
int core_launch(int argc, wchar_t* argv[])
{
#if _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	new int;
#endif // _DEBUG

	KCore::instance()->init<INIT>(argc, argv);
	KCore::instance()->loop();
	return 0;
}

// ���� �ܰ� �ϳ� ���� �� �ֽ�ȭ
template<typename INIT,  typename UP>
int core_launch(int argc, wchar_t* argv[])
{
#if _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	new int;
#endif // _DEBUG

	KCore::instance()->init<INIT>(argc, argv);
	KCore::instance()->loop<UP>();
	return 0;
}


// ���� �ܰ� �ϳ� ���� �� �ֽ�ȭ
template<typename INIT, typename UP, typename RELEASE>
int core_launch(int argc, wchar_t* argv[])
{
#if _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	new int;
#endif // _DEBUG

	KCore::instance()->init<INIT>(argc, argv);
	KCore::instance()->loop<UP, RELEASE>();
	return 0;
}



/******************** Window ********************/
template<typename INIT>
int core_launch(
	_In_ HINSTANCE _hInstance,
	_In_ LPWSTR    _lpCmdLine,
	_In_ int       _nCmdShow)
{
#if _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	new int;
#endif // _DEBUG

	KCore::instance()->init<INIT>(_hInstance, _lpCmdLine, _nCmdShow);
	KCore::instance()->loop();
	return 0;
}

template<typename INIT, typename UP>
int core_launch(
	_In_ HINSTANCE _hInstance,
	_In_ LPWSTR    _lpCmdLine,
	_In_ int       _nCmdShow)
{
#if _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	// _CrtSetBreakAlloc(277);
	new int;
#endif // _DEBUG

	KCore::instance()->init<INIT>(_hInstance, _lpCmdLine, _nCmdShow);
	KCore::instance()->loop<UP>();
	return 0;
}


template<typename INIT, typename UP, typename RELEASE>
int core_launch(
	_In_ HINSTANCE _hInstance,
	_In_ LPWSTR    _lpCmdLine,
	_In_ int       _nCmdShow)
{

#if _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetBreakAlloc(277);
	new int;
#endif // _DEBUG

	KCore::instance()->init<INIT>(_hInstance, _lpCmdLine, _nCmdShow);
	KCore::instance()->loop<UP, RELEASE>();
	return 0;
}



/******************** KWindow ********************/
template<typename INIT>
int core_launch(KWindow* _Window)
{
#if _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	new int;
#endif // _DEBUG

	KCore::instance()->init<INIT>(_Window);
	KCore::instance()->loop();
	return 0;
}

template<typename INIT, typename UP, typename RELEASE>
int core_launch(KWindow* _Window)
{
#if _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	// _CrtSetBreakAlloc(1281);
	new int;
#endif // _DEBUG

	KCore::instance()->init<INIT>(_Window);
	KCore::instance()->loop<UP, RELEASE>();
	return 0;
}