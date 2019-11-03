#include "KMacro.h"
#include "KSceneManager.h"
#include "KWindowManager.h"
#include "KScene.h"
#include <KCommon.h>



void KSceneManager::create()
{
	CurScene = nullptr;
}


void KSceneManager::init()
{
	if (nullptr == CurScene)
	{
		return;
	}

	if (false == bCurInit)
	{
		CurScene->init();
		bCurInit = true;
	}
}
void KSceneManager::update()
{
	if (nullptr == CurScene)
	{
		return;
	}
	CurScene->update();
}
void KSceneManager::render()
{
	if (nullptr == CurScene)
	{
		return;
	}

	CurScene->render();
}


void KSceneManager::release()
{
	std::multimap<std::wstring, KScene*>::iterator SIter = MapScene.begin();
	std::multimap<std::wstring, KScene*>::iterator EIter = MapScene.end();

	for (; SIter != EIter; ++SIter)
	{
		SIter->second->release();
		RELEASE_PTR(SIter->second);
	}

	MapScene.clear();

	RELEASE_PTR(KSingleton::instance()->MyPtr);
}

KScene* KSceneManager::create_scene(KScene* _Other, const wchar_t* _Name /*= "KScene"*/)
{
	if (nullptr == _Other)
	{
		return nullptr;
	}

	_Other->sName = _Name;
	_Other->kwindow(kwindow());
	_Other->create();
	MapScene.insert(std::make_pair(_Name, _Other));
	return _Other;
}


KScene* KSceneManager::create_scene(const wchar_t* _Name/*= "KScene"*/)
{
	KScene* Tmp = new KScene();
	Tmp->sName = _Name;
	Tmp->kwindow(kwindow());
	Tmp->create();
	MapScene.insert(std::make_pair(_Name, Tmp));
	return Tmp;
}



KScene* KSceneManager::find_scene(const wchar_t* _Name)
{
	std::multimap<std::wstring, KScene*>::iterator FIter = MapScene.find(_Name);

	if (MapScene.end() != FIter)
	{
		return FIter->second;
	}

	return nullptr;
}

bool KSceneManager::delete_scene(const wchar_t* _Name)
{
	std::multimap<std::wstring, KScene*>::iterator FIter = MapScene.find(_Name);


	if (MapScene.end() == FIter)
	{
		return false;
	}

	FIter->second->release();
	delete FIter->second;
	MapScene.erase(FIter);
	return true;
}

bool KSceneManager::change_scene(const wchar_t* _Name)
{
	if (nullptr != CurScene)
	{
		CurScene->out();
	}

	bCurInit = false;
	KScene* Tmp = find_scene(_Name);
	if (nullptr == Tmp)
	{
		KASSERT;
		return false;
	}

	CurScene = Tmp;

	init();
	return true;
}