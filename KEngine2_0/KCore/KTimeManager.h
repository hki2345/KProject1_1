#pragma once
#include <map>
#include <chrono>
#include <KCommon.h>

#include "KName.h"


class KTimeManager : public KSingleton<KTimeManager>
{
public:
	friend class KCore;
	friend class KWindow;

private:
	class KTimer : public KName
	{
	public:
		friend class KTimeManager;

	private:
		KTimer();
		KTimer(const KTimer& _Core) = delete;
		KTimer(const KTimer&& _Core) = delete;
		void operator=(const KTimer& _Core) = delete;
		~KTimer();

	private:
		void start();
		void accumulate();

	private:
		std::chrono::system_clock::time_point m_LastTime;
		std::chrono::system_clock::time_point m_CurTime;

		float DeltaTime;
		float AccumulateTime;
		float AccCal_Time;
		float Fps;
		int FPSCount;
	};

private:
	KTimer* MainTimer;
	std::map<std::wstring, KTimer*> MapActingTimer;
	std::map<std::wstring, KTimer*> MapPauseTimer;



	std::map<std::wstring, KTimer*>::iterator mSTimer;
	std::map<std::wstring, KTimer*>::iterator mETimer;
	std::map<std::wstring, KTimer*>::iterator mFTimer;

private:
	void init();
	void update();
	void release() override;	
	
	KTimeManager::KTimer* find_ActingTimer(const wchar_t* _Name);
	KTimeManager::KTimer* find_PauseTimer(const wchar_t* _Name);


public:
	std::wstring fps_string()
	{
		return std::to_wstring(MainTimer->Fps);
	}

	float& fps()
	{
		return MainTimer->Fps;
	}
	
	float& deltatime()
	{
		return MainTimer->DeltaTime;
	}

	float& accumulate()
	{
		return MainTimer->AccumulateTime;
	}
	
	// 타이머의...
	float& fps(const wchar_t* _Name);
	float& deltatime(const wchar_t* _Name);
	

	KTimeManager::KTimer* create_timer(const wchar_t* _Name);
	KTimeManager::KTimer* find_timer(const wchar_t* _Name);

	bool start_timer(const wchar_t* _Name);
	bool stop_timer(const wchar_t* _Name);
	bool erase_timer(const wchar_t* _Name);
};

