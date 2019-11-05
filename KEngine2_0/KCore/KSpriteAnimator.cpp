#include "KSpriteAnimator.h"
#include "KSpriteRender.h"
#include "KTimeManager.h"
#include "KOne.h"

#include <KMacro.h>


KSpriteAnimator::KSpriteAnimator() :
	pSprite(nullptr)
{
}


KSpriteAnimator::~KSpriteAnimator()
{
}

void KSpriteAnimator::insert_animation(
	const wchar_t* _AniName,
	const int& _Start,
	const int& _End,
	const float& _Speed /*= 0.1f*/ // 초당 약 10장
)
{
	Clip NewClip;
	NewClip.fSpeed = _Speed;
	NewClip.Start = _Start;
	NewClip.End = _End;
	NewClip.fAniTime = .0f;
	NewClip.iAniIdx = 0;

	MapClip.insert(std::make_pair(_AniName, NewClip));
	CurClip = MapClip.begin();
}
void KSpriteAnimator::change_animation(const wchar_t* _AniName)
{
	std::map<std::wstring, Clip>::iterator FIter = MapClip.find(_AniName);

	if (MapClip.end() != FIter && CurClip != FIter)
	{
		CurClip = FIter;
		CurClip->second.iAniIdx = CurClip->second.Start;
	}
}

void KSpriteAnimator::set_bit(const wchar_t* _Name /*= L"NONE"*/, const int& _Key /*= 0*/)
{
	pSprite->set_bit(_Name, _Key);
}
void KSpriteAnimator::change_bit(const wchar_t* _Name /*= L"NONE"*/)
{
	pSprite->change_bit(_Name);
}
void KSpriteAnimator::set_split(const int& _X, const int& _Y)
{
	pSprite->set_split(_X, _Y);
}

void KSpriteAnimator::reset_animate()
{
	CurClip->second.iAniIdx = CurClip->second.Start;
}

void KSpriteAnimator::create()
{
	KRenderer::create();

	sName = L"KSpriteAnimator";
	pSprite = kone()->add_component<KSpriteRender>();
}

bool KSpriteAnimator::init()
{
	KRenderer::init();
	// idx = 0;

	pSprite->init();
	
	return true;
}
void KSpriteAnimator::update()
{
	CurClip->second.fAniTime += KTimeManager::instance()->deltatime();

	if (CurClip->second.fAniTime > CurClip->second.fSpeed)
	{
		CurClip->second.iAniIdx += 1;
		CurClip->second.fAniTime = .0f;
	}

	if (CurClip->second.End + 1 <= CurClip->second.iAniIdx)
	{
		CurClip->second.iAniIdx = CurClip->second.Start;
	}

	pSprite->set_idx(CurClip->second.iAniIdx);
}
void KSpriteAnimator::render()
{
	// pSprite->render_api();
}

void KSpriteAnimator::render(HDC _Hdc)
{
	pSprite->render(_Hdc);
}

bool KSpriteAnimator::isover_animate()
{
	if (CurClip->second.End <= CurClip->second.iAniIdx)
	{
		return true;
	}

	return false;
}

void KSpriteAnimator::render_size(const KSize2& _RenderSize)
{
	pSprite->render_size(_RenderSize);
	RenderSize = _RenderSize;
}


void KSpriteAnimator::active_frame(const bool& _Value)
{
	KActor::active_frame(_Value);
	pSprite->active_frame(_Value);
}


void KSpriteAnimator::pivot(const KSize2& _RenderSize) 
{
	MyPivot = _RenderSize;
	pSprite->pivot(_RenderSize);
}

void KSpriteAnimator::z_sort(const float& _Value)
{
	ZSort = _Value;
	pSprite->ZSort = _Value;
}