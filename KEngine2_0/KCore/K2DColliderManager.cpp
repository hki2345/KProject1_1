#include "K2DColliderManager.h"
#include "K2DCollider.h"
#include "KOne.h"



void K2DColliderManager::init()
{
	std::multimap<int, K2DCollider*>::iterator SIter = MapK2DCollider.begin();
	std::multimap<int, K2DCollider*>::iterator EIter = MapK2DCollider.end();

	for (; SIter != EIter; ++SIter)
	{
		SIter->second->init();
	}
}


void K2DColliderManager::update()
{
	std::list <Link>::iterator SLI = ListLink.begin();
	std::list <Link>::iterator ELI = ListLink.end();

	for (; SLI != ELI; ++SLI)
	{
		update_passlink((*SLI).Key1, (*SLI).Key2);
	}
}


void K2DColliderManager::update_passlink(const int& _Key1, const int& _Key2)
{
	if (0 == ListPassLink.size())
	{
		update_link(_Key1, _Key2);
		return;
	}


	std::list <Link>::iterator SPLI = ListPassLink.begin();
	std::list <Link>::iterator EPLI = ListPassLink.end();

	for (; SPLI != EPLI; SPLI++)
	{
		if ((*SPLI).Key1 == _Key1 && (*SPLI).Key2 == _Key2)
		{
			return;
		}
	}

	update_link(_Key1, _Key2);
}


void K2DColliderManager::update_link(const int& _Key1, const int& _Key2)
{
	if (_Key1 == _Key2)
	{
		update_evenlink(_Key1, _Key2);
	}
	else if(_Key1 != _Key2)
	{
		update_differlink(_Key1, _Key2);
	}
}



void K2DColliderManager::update_evenlink(const int& _Key1, const int& _Key2)
{
	std::multimap<int, K2DCollider*>::iterator SCI1 = MapK2DCollider.find(_Key1);
	for (; SCI1 != MapK2DCollider.end();)
	{
		if (_Key1 != SCI1->first)
		{
			break;
		}
		if (false == SCI1->second->kone()->active_frame() ||
			false == SCI1->second->active_frame())
		{
			++SCI1;
			continue;
		}



		SCI1->second->checking_deltabox();
		std::multimap<int, K2DCollider*>::iterator SCI2 = SCI1;

		++SCI2;
		for (; SCI2 != MapK2DCollider.end();)
		{
			if (_Key2 != SCI2->first)
			{
				break;
			}

			if (false == SCI2->second->kone()->active_frame() ||
				false == SCI2->second->active_frame() ||
				SCI1->second == SCI2->second)
			{
				++SCI2;
				continue;
			}

			SCI1->second->update_collision(SCI2->second);
			++SCI2;
		}
		++SCI1;
	}
}




void K2DColliderManager::update_differlink(const int& _Key1, const int& _Key2)
{
	std::multimap<int, K2DCollider*>::iterator SCI1 = MapK2DCollider.find(_Key1);
	for (; SCI1 != MapK2DCollider.end();)
	{
		if (_Key1 != SCI1->first)
		{
			break;
		} 
		if(	false == SCI1->second->kone()->active_frame() ||
			false == SCI1->second->active_frame())
		{
			++SCI1;
			continue;
		}

		SCI1->second->checking_deltabox();
		std::multimap<int, K2DCollider*>::iterator SCI2 = MapK2DCollider.find(_Key2);
		for (; SCI2 != MapK2DCollider.end();)
		{
			if (_Key2 != SCI2->first)
			{
				break;
			}

			if (false == SCI2->second->kone()->active_frame() ||
				false == SCI2->second->active_frame() ||
				SCI1->second == SCI2->second)
			{
				++SCI2;
				continue;
			}

			SCI1->second->update_collision(SCI2->second); 
			++SCI2;
		}
		++SCI1;
	}
}


void K2DColliderManager::release()
{
	MapK2DCollider.clear();
	ListLink.clear();
}


void K2DColliderManager::link(const int& _Key1, const int& _Key2)
{
	ListLink.push_back({ _Key1, _Key2 });
}

bool K2DColliderManager::insert_kcollider(K2DCollider* _Other, const int& _Key/* = 0*/)
{
	MapK2DCollider.insert(std::make_pair(_Key, _Other));
	return true;
}

bool K2DColliderManager::delete_k2dcollider(K2DCollider* _Other)
{
	std::multimap<int, K2DCollider*>::iterator SIter = MapK2DCollider.begin();
	std::multimap<int, K2DCollider*>::iterator EIter = MapK2DCollider.end();
	
	for (; SIter != EIter; SIter++)
	{
		if (_Other == SIter->second)
		{
			MapK2DCollider.erase(SIter);
			return true;
		}
	}

	return false;
}

void K2DColliderManager::set_passlink(const int& _Key1, const int& _Key2)
{
	ListPassLink.push_back({ _Key1, _Key2 });
}
void K2DColliderManager::clear_passlink()
{
	ListPassLink.clear();
}