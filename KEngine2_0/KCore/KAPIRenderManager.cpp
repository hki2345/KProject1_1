#include "KAPIRenderManager.h"
#include "KRenderer.h"
#include "KOne.h"
#include "KMacro.h"

#include <algorithm>



void KAPIRenderManager::init()
{
	std::multimap<int, KRenderer*>::iterator SIter = MapKRenderer.begin();
	std::multimap<int, KRenderer*>::iterator EIter = MapKRenderer.end();

	for (; SIter != EIter; ++SIter)
	{
		SIter->second->init();
	}
}

void KAPIRenderManager::update_trans(const KPos2& _CameraPos)
{
	std::multimap<int, KRenderer*>::iterator SIter = MapKRenderer.begin();
	std::multimap<int, KRenderer*>::iterator EIter = MapKRenderer.end();

	for (; SIter != EIter; ++SIter)
	{
		if (true == SIter->second->active_frame() && true == SIter->second->kone()->active_frame())
		{
			SIter->second->update_trans(_CameraPos);
		}
	}
}

void KAPIRenderManager::render()
{
	std::multimap<int, KRenderer*>::iterator SIter = MapKRenderer.begin();
	std::multimap<int, KRenderer*>::iterator EIter = MapKRenderer.end();

	for (; SIter != EIter; ++SIter)
	{
		if (true == SIter->second->active_frame() && true == SIter->second->kone()->active_frame())
		{
			SIter->second->render();
		}
	}
}

void KAPIRenderManager::release()
{
	MapKRenderer.clear();
}



bool KAPIRenderManager::insert_krenderer( KRenderer* _Other, const int& _Key/* = 0*/)
{
	MapKRenderer.insert(std::make_pair(_Key, _Other));

	return true;
}

void KAPIRenderManager::delete_renderer(KRenderer* _Renderer)
{
	std::multimap<int, KRenderer*>::iterator SIter = MapKRenderer.begin();
	std::multimap<int, KRenderer*>::iterator EIter = MapKRenderer.end();

	for (; SIter != EIter; ++SIter)
	{
		if (_Renderer == SIter->second)
		{
			MapKRenderer.erase(SIter);
			return;
		}
	}
}

void KAPIRenderManager::sort_toz(const int& _Layer)
{
	std::multimap<int, KRenderer*>::iterator SIter = MapKRenderer.find(_Layer);
	if (SIter == MapKRenderer.end())
	{
		return;
	}


	std::multimap<int, KRenderer*> PrevMap;
	std::multimap<int, KRenderer*>::iterator PrevSIter = MapKRenderer.begin();
	for (; PrevSIter != SIter; PrevSIter++)
	{
		PrevMap.insert(std::make_pair(PrevSIter->first, PrevSIter->second));
	}


	std::multimap<int, KRenderer*>::iterator EIter = SIter;
	std::multimap<int, KRenderer*>::iterator VSIter = SIter;
	for (; SIter != MapKRenderer.end(); SIter++)
	{
		EIter++;
		if (EIter == MapKRenderer.end())
		{
			break;
		}
		if (SIter->first != EIter->first)
		{
			break;
		}
	}




	std::multimap<int, KRenderer*> NextMap;
	std::multimap<int, KRenderer*>::iterator NextSIter = EIter;
	for (; NextSIter != MapKRenderer.end(); NextSIter++)
	{
		NextMap.insert(std::make_pair(NextSIter->first, NextSIter->second));
	}



	std::vector<KRenderer*> SortVector;
	for (; VSIter != EIter; VSIter++)
	{
		SortVector.push_back(VSIter->second);
	}

	std::sort(SortVector.begin(), SortVector.end(), [&SortVector](
		KRenderer* _Right,
		KRenderer* _Left)->bool
	{ 
		return _Right->ZSort < _Left->ZSort; 
	});


	MapKRenderer.clear();


	PrevSIter = PrevMap.begin();
	for (; PrevSIter != PrevMap.end(); PrevSIter++)
	{
		MapKRenderer.insert(std::make_pair(PrevSIter->first, PrevSIter->second));
	}

	for (size_t i = 0; i < SortVector.size(); i++)
	{
		MapKRenderer.insert(std::make_pair(_Layer, SortVector[i]));
	}

	NextSIter = NextMap.begin();
	for (; NextSIter != NextMap.end(); NextSIter++)
	{
		MapKRenderer.insert(std::make_pair(NextSIter->first, NextSIter->second));
	}
}