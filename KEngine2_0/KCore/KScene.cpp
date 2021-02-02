#include "KScene.h"
#include "KWindow.h"

#include "KOne.h"
#include "KMacro.h"
#include "KAPIRenderManager.h"
#include "K2DColliderManager.h"

#include <KMacro.h>

#include "KCore.h"



KScene::KScene() : curAPIKRenderMgr(nullptr), curK2DColliderMgr(nullptr)
{
}

void KScene::create()
{
	if (nullptr == curAPIKRenderMgr)
	{
		curAPIKRenderMgr = new KAPIRenderManager();
		curAPIKRenderMgr->init();

		SceneCamPos = KPos2::Zero;
	}

	if (nullptr == curK2DColliderMgr)
	{
		curK2DColliderMgr = new K2DColliderManager();
		curK2DColliderMgr->init();
	}

	std::multimap<std::wstring, KOne*>::iterator SIter = MapKOne.begin();
	std::multimap<std::wstring, KOne*>::iterator EIter = MapKOne.end();

	for (; SIter != EIter; ++SIter)
	{
		SIter->second->create();
	}
}

bool KScene::init()
{
	std::multimap<std::wstring, KOne*>::iterator SIter = MapKOne.begin();
	std::multimap<std::wstring, KOne*>::iterator EIter = MapKOne.end();

	for (; SIter != EIter; ++SIter)
	{
		SIter->second->init();
	}

	return true;
}

void KScene::update()
{
	std::multimap<std::wstring, KOne*>::iterator SIter = MapKOne.begin();
	std::multimap<std::wstring, KOne*>::iterator EIter = MapKOne.end();

	for (; SIter != EIter; ++SIter)
	{
		if (SIter->second->bActing != SIter->second->bNextActing)
		{
			SIter->second->bActing = SIter->second->bNextActing;
		}

		if (true == SIter->second->bActing)
		{
			SIter->second->update();
		}
	}

	KDebugManager::instance()->update();
	curK2DColliderMgr->update();
}

void KScene::out() 
{
	std::multimap<std::wstring, KOne*>::iterator SIter = MapKOne.begin();
	std::multimap<std::wstring, KOne*>::iterator EIter = MapKOne.end();

	for (; SIter != EIter; ++SIter)
	{
		SIter->second->out();
	}
}

void KScene::release()
{
	std::multimap<std::wstring, KOne*>::iterator SIter = MapKOne.begin();
	std::multimap<std::wstring, KOne*>::iterator EIter = MapKOne.end();

	for (; SIter != EIter; ++SIter)
	{
		SIter->second->release();
		RELEASE_PTR(SIter->second);
	}

	MapKOne.clear();


	if (nullptr != curAPIKRenderMgr)
	{
		curAPIKRenderMgr->release();
	}
	RELEASE_PTR(curAPIKRenderMgr);

	if (nullptr != curK2DColliderMgr)
	{
		curK2DColliderMgr->release();
	}
	RELEASE_PTR(curK2DColliderMgr);
}


void KScene::render_api() 
{
	curAPIKRenderMgr->update_trans(SceneCamPos);
	curAPIKRenderMgr->render();

#if _DEBUG
	render_debug();
	KDebugManager::instance()->render();
#endif
}

void KScene::render_dx()
{
	curAPIKRenderMgr->update_trans(SceneCamPos);
	curAPIKRenderMgr->render();

#if _DEBUG
	render_debug();
	KDebugManager::instance()->render();
#endif
}


void KScene::render_debug()
{
	if (false == KDebugManager::instance()->bDebugAll || false == KDebugManager::instance()->bDebugFigure)
	{
		return;
	}

	std::multimap<std::wstring, KOne*>::iterator SIter = MapKOne.begin();
	std::multimap<std::wstring, KOne*>::iterator EIter = MapKOne.end();

	for (; SIter != EIter; ++SIter)
	{
		if (true == SIter->second->bActing)
		{
			SIter->second->render_debug();
		}
	}
}


KOne* KScene::create_kone(KOne* _Other, const wchar_t* _Name /*= "KOne"*/)
{
	if (nullptr == _Other)
	{
		return nullptr;
	}

	_Other->sName = _Name;
	_Other->kscene(this);
	_Other->create();

	MapKOne.insert(std::make_pair(_Name, _Other));
	return _Other;
}

KOne* KScene::create_kone(const wchar_t* _Name/*= "KOne"*/)
{
	KOne* Tmp =  new KOne();

	Tmp->sName = _Name;
	Tmp->kwindow(kwindow());
	Tmp->kscene(this);
	Tmp->create();


	MapKOne.insert(std::make_pair(_Name, Tmp));
	return Tmp;
}

KOne* KScene::find_kone(const wchar_t* _Name)
{
	std::multimap<std::wstring, KOne*>::iterator FIter = MapKOne.find(_Name);
	if (MapKOne.end() != FIter)
	{
		return FIter->second;
	}

	return nullptr;
}

bool KScene::delete_kone(const wchar_t* _Name)
{
	std::multimap<std::wstring, KOne*>::iterator FIter = MapKOne.find(_Name);
	if (MapKOne.end() == FIter)
	{
		return false;
	}

	FIter->second->release();
	delete FIter->second;
	MapKOne.erase(FIter);
	return true;
}


bool KScene::delete_kone(KOne* _Other)
{
	std::multimap<std::wstring, KOne*>::iterator FIter = MapKOne.begin();
	std::multimap<std::wstring, KOne*>::iterator EIter = MapKOne.end();


	for (; FIter != EIter; FIter++)
	{
		if (_Other == FIter->second)
		{
			FIter->second->release();
			RELEASE_PTR(FIter->second);		
			MapKOne.erase(FIter);
			return true;
		}
	}

	return false;
}



bool KScene::insert_krender(KRenderer* _Render, const int& _Key /*= 0*/)
{
	return curAPIKRenderMgr->insert_krenderer(_Render, _Key);
}


bool KScene::insert_k2dCollider(K2DCollider* _Collider, const int& _Key /*= 0*/)
{
	return  curK2DColliderMgr->insert_kcollider(_Collider, _Key);
}


void KScene::link_k2dCollider(const int& _Key1, const int& _Key2)
{
	curK2DColliderMgr->link(_Key1, _Key2);
}

void KScene::passlink_k2dCollider(const int& _Key1, const int& _Key2)
{
	curK2DColliderMgr->set_passlink(_Key1, _Key2);
}

void KScene::clearpasslink()
{
	curK2DColliderMgr->clear_passlink();
}

KPos2 KScene::outof_screen(KOne* _Target)
{
	float TmpSize = 200.0f;

	if (SceneCamPos.x > _Target->pos().x + TmpSize + _Target->size().x )
	{
		return KPos2::Left;
	}
	else if (SceneCamPos.x + kwindow()->size().x < (_Target->pos().x + TmpSize * -1.0f) + (_Target->size().x))
	{
		return KPos2::Right;
	}

	return KPos2::Zero;
}



bool KScene::delete_krenderer(KRenderer* _Renderer)
{
	curAPIKRenderMgr->delete_renderer(_Renderer);
	return true;
}
bool KScene::delete_k2dcollider(K2DCollider* _Collider)
{
	curK2DColliderMgr->delete_k2dcollider(_Collider);
	return true;
}

void KScene::sort_toz(const int& _Key)
{
	curAPIKRenderMgr->sort_toz(_Key);
}