#include "KOne.h"
#include "KMacro.h"
#include "KComponent.h"
#include "KTransform.h"



KOne::KOne() : MyTrans(nullptr)
{
}

void KOne::create()
{
	sName = L"KOne";
	if (nullptr == MyTrans)
	{
		MyTrans = add_component<KTransform>();
	}
}

bool KOne::init() 
{
	std::multimap<std::wstring, KComponent*>::iterator SIter = MapComponent.begin();
	std::multimap<std::wstring, KComponent*>::iterator EIter = MapComponent.end();

	for (; SIter != EIter; ++SIter)
	{
		SIter->second->init();
	}
	return true;
}

void KOne::update()
{
	std::multimap<std::wstring, KComponent*>::iterator SIter = MapComponent.begin();
	std::multimap<std::wstring, KComponent*>::iterator EIter = MapComponent.end();

	for (; SIter != EIter; ++SIter)
	{
		if (SIter->second->bActing != SIter->second->bNextActing)
		{
			SIter->second->bActing = SIter->second->bNextActing;
		}

		SIter->second->update();
	}
}


void KOne::render_debug()
{
	std::multimap<std::wstring, KComponent*>::iterator SIter = MapComponent.begin();
	std::multimap<std::wstring, KComponent*>::iterator EIter = MapComponent.end();

	for (; SIter != EIter; ++SIter)
	{
		SIter->second->render_debug();
	}
}

void KOne::out()
{
	std::multimap<std::wstring, KComponent*>::iterator SIter = MapComponent.begin();
	std::multimap<std::wstring, KComponent*>::iterator EIter = MapComponent.end();

	for (; SIter != EIter; ++SIter)
	{
		SIter->second->out();
	}
}
void KOne::release()
{
	std::multimap<std::wstring, KComponent*>::iterator SIter = MapComponent.begin();
	std::multimap<std::wstring, KComponent*>::iterator EIter = MapComponent.end();

	for (; SIter != EIter; ++SIter)
	{
		SIter->second->release();
		RELEASE_PTR(SIter->second);
	}

	MapComponent.clear();
}



void KOne::pos(const KVec2& _Pos)
{
	MyTrans->Pos =_Pos;
}
void KOne::size(const KSize2& _Size)
{
	MyTrans->Size = _Size;
}


void KOne::moving_pluspos(const KPos2& _Value)
{
	MyTrans->moving_pluspos(_Value);
}

void KOne::moving_pos(const KPos2& _Value)
{
	MyTrans->moving_pos(_Value);
}

void KOne::moving_delta(const KPos2& _Value)
{
	MyTrans->moving_delta(_Value);
}



KPos2& KOne::pos()
{
	return MyTrans->Pos;
}
KPos2& KOne::size()
{
	return MyTrans->Size;
}