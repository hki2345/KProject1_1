#include "KTimeManager.h"
#include "KMacro.h"

KTimeManager::KTimer::KTimer() :
	DeltaTime(.0f),
	AccumulateTime(.0f),
	AccCal_Time(.0f),
	Fps(.0f),
	FPSCount(0)
{

}
KTimeManager::KTimer::~KTimer()
{

}



void KTimeManager::KTimer::start()
{
	m_LastTime = std::chrono::system_clock::now();

	AccumulateTime = .0f;
	AccCal_Time = .0f;
	FPSCount = 0;
}

void KTimeManager::KTimer::accumulate()
{
	m_CurTime = std::chrono::system_clock::now();

	// 델타타임을 구한다.
	// 받는 형이 정해져야 하드라 ㅋㅋㅋ 걍 받으면 더블로 처리됌여
	std::chrono::duration<float> sec = m_CurTime - m_LastTime;
	DeltaTime = sec.count();
	
	
	m_LastTime = m_CurTime;
	
	// FPS 계산 1초당 프레임 수...
	AccCal_Time += DeltaTime;
	AccumulateTime += DeltaTime;



	++FPSCount;

	if (1.0f <= AccCal_Time)
	{
		Fps = ((float)FPSCount / AccCal_Time);
		AccCal_Time = 0.0f;
		FPSCount = 0;
	}
}




void KTimeManager::init()
{
	MainTimer = new KTimeManager::KTimer;
	MainTimer->start();
}

void KTimeManager::update()
{
	MainTimer->accumulate();


	mSTimer = MapActingTimer.begin();
	mETimer = MapActingTimer.end();

	for (; mSTimer != mETimer; ++mSTimer)
	{
		mSTimer->second->accumulate();
	}
}

void KTimeManager::release()
{

	mSTimer = MapActingTimer.begin();
	mETimer = MapActingTimer.end();

	for (; mSTimer != mETimer; ++mSTimer)
	{
		delete mSTimer->second;
	}



	mSTimer = MapPauseTimer.begin();
	mETimer = MapPauseTimer.end();

	for (; mSTimer != mETimer; ++mSTimer)
	{
		delete mSTimer->second;
	}

	MapActingTimer.clear();
	MapPauseTimer.clear();

	RELEASE_PTR(MainTimer);
	RELEASE_PTR(KSingleton::MyPtr);
}


float& KTimeManager::fps(const wchar_t* _Name)
{
	return  find_timer(_Name)->Fps;
}

float& KTimeManager::deltatime(const wchar_t* _Name)
{
	return  find_timer(_Name)->DeltaTime;
}



KTimeManager::KTimer* KTimeManager::create_timer(const wchar_t* _Name)
{
	KTimeManager::KTimer* Tmp = find_timer(_Name);

	if (nullptr == Tmp)
	{
		Tmp = new KTimeManager::KTimer();
		Tmp->start();
		MapActingTimer.insert(std::make_pair(_Name, Tmp));
	}

	return nullptr;
}


KTimeManager::KTimer* KTimeManager::find_timer(const wchar_t* _Name)
{
	KTimeManager::KTimer* Tmp = find_ActingTimer(_Name);

	if (nullptr == Tmp)
	{
		Tmp = find_PauseTimer(_Name);
	}

	if (nullptr== Tmp)
	{
		return nullptr;
	}

	return Tmp;
}


KTimeManager::KTimer* KTimeManager::find_ActingTimer(const wchar_t* _Name)
{
	mFTimer = MapActingTimer.find(_Name);

	if (MapActingTimer.end() == mFTimer)
	{
		return nullptr;
	}

	return mFTimer->second;
}

KTimeManager::KTimer* KTimeManager::find_PauseTimer(const wchar_t* _Name)
{
	mFTimer = MapPauseTimer.find(_Name);

	if (MapPauseTimer.end() == mFTimer)
	{
		return nullptr;
	}

	return mFTimer->second;
}




bool KTimeManager::start_timer(const wchar_t* _Name)
{
	KTimeManager::KTimer* Tmp = find_PauseTimer(_Name);

	if (nullptr != Tmp)
	{
		return false;
	}

	MapPauseTimer.erase(_Name);
	MapActingTimer.insert(std::make_pair(_Name, Tmp));

	return true;
}

bool KTimeManager::stop_timer(const wchar_t* _Name)
{
	KTimeManager::KTimer* Tmp = find_ActingTimer(_Name);

	if (nullptr != Tmp)
	{
		return false;
	}

	MapActingTimer.erase(_Name);
	MapPauseTimer.insert(std::make_pair(_Name, Tmp));

	return true;
}
bool KTimeManager::erase_timer(const wchar_t* _Name)
{
	KTimeManager::KTimer* Tmp = find_ActingTimer(_Name);

	if (nullptr != Tmp)
	{
		delete Tmp;
		MapActingTimer.erase(_Name);
	}

	Tmp = find_PauseTimer(_Name);

	if (nullptr != Tmp)
	{
		delete Tmp;
		MapPauseTimer.erase(_Name);
	}
	else
	{
		return false;
	}

	return true;
}