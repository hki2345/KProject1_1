#include "KBitMapAnimator.h"
#include <KResourceManager.h>
#include "KTimeManager.h"
#include "KWindow.h"
#include "KTransform.h"

#include "KBitMap.h"
#include "KScene.h"



KBitMapAnimator::KBitMapAnimator() :
	bBitRender(false),
	fAniTime(.0f),
	fSpeed(.0f),
	iAniIdx(0)
{
}


KBitMapAnimator::~KBitMapAnimator()
{
}


void KBitMapAnimator::create()
{
	KRenderer::create();
	sName = L"KBitMapAnimator";

	iAniIdx = 0;
	fAniTime = .0f;
}

void KBitMapAnimator::insert_animation(
	const wchar_t* _AniName,
	const std::vector<std::wstring>& _Source,
	const int& _Layer /*= 0*/,
	const float& _Speed /*= 0.02f*/,
	const int& _Start /*= 0*/,
	const bool& _BitRender /*= false*/
	)
{
	bBitRender = _BitRender;
	fSpeed = _Speed;
	iAniIdx = _Start;

	std::vector<KBitMap*> TmpVec;


	for (size_t i = 0; i < _Source.size(); i++)
	{
		KBitMap* Tmp = KResourceManager<KBitMap>::instance()->find(_Source[i].c_str());

		assert(Tmp);
		TmpVec.push_back(Tmp);
	}

	MapVecBit.insert(std::make_pair(_AniName, TmpVec));
	CurAniIter = MapVecBit.begin();
	kscene()->insert_krender(this, _Layer);
}

void KBitMapAnimator::change_animation(const wchar_t* _AniName)
{
	std::map<std::wstring, std::vector< KBitMap*>>::iterator FIter = MapVecBit.find(_AniName);

	if (MapVecBit.end() == FIter)
	{
		KASSERT;
	}

	if (CurAniIter != FIter)
	{
		iAniIdx = 0;
		CurAniIter = MapVecBit.find(_AniName);
	}
}



bool KBitMapAnimator::init()
{
	KRenderer::init();
	
	if (iAniIdx >= (int)CurAniIter->second.size())
	{
		iAniIdx = 0;
		fAniTime = .0f;
	}

	return true;
}

void KBitMapAnimator::update()
{
	fAniTime += KTimeManager::instance()->deltatime();

	if (fAniTime > fSpeed)
	{
		iAniIdx += 1;
		fAniTime = .0f;
	}

	if ((int)CurAniIter->second.size() <= iAniIdx)
	{
		iAniIdx = 0;
	}
}
void KBitMapAnimator::render()
{
	if (false == bRender)
	{
		return;
	}

	if ((int)CurAniIter->second.size() <= iAniIdx)
	{
		iAniIdx = 0;
	}


	if (true == bBitRender)
	{
		BitBlt(
			kwindow()->bhdc(),
			(int)RenderPos.x,
			(int)RenderPos.y,
			(int)MyTrans->Size.x,
			(int)MyTrans->Size.y,
			CurAniIter->second[iAniIdx]->MyDC,
			0,
			0,
			SRCCOPY);
	}

	if (false == bBitRender)
	{
		TransparentBlt(
			kwindow()->bhdc(),
			(int)RenderPos.x,
			(int)RenderPos.y,
			(int)MyTrans->Size.x,
			(int)MyTrans->Size.y,
			CurAniIter->second[iAniIdx]->MyDC,
			0,
			0,
			(int)CurAniIter->second[iAniIdx]->size().x,
			(int)CurAniIter->second[iAniIdx]->size().y,
			RGB(255, 0, 255));
	}	
}
void KBitMapAnimator::release()
{
	MapVecBit.clear();
}