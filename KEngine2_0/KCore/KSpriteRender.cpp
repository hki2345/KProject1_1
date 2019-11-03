#include "KSpriteRender.h"
#include <KResourceManager.h>

#include "KWindow.h"
#include "KTransform.h"
#include "KScene.h"
#include "KBitMap.h"

#pragma comment(lib, "msimg32.lib")


KSpriteRender::KSpriteRender() :
	MyBitMap(nullptr),
	SplitX(0),
	SplitY(0),
	idx(0)
{
}


KSpriteRender::~KSpriteRender()
{
}

void KSpriteRender::create()
{
	KRenderer::create();
	sName = L"KSpriteRender";
}

void KSpriteRender::set_bit(
	const wchar_t* _Name /*= L"NONE"*/,
	const int& _Key /*= 0*/)
{
	MyBitMap = KResourceManager<KBitMap>::instance()->find(_Name);
	kscene()->insert_krender(this, _Key);

}
void KSpriteRender::change_bit(
	const wchar_t* _Name /*= L"NONE"*/)
{
	MyBitMap = KResourceManager<KBitMap>::instance()->find(_Name);
}
void KSpriteRender::set_split(const int& _X, const int& _Y)
{
	SplitX = _X;
	SplitY = _Y;

	VectorMySplit.clear();
	int SplitSizeX = ((int)MyBitMap->size().x / SplitX);
	int SplitSizeY = ((int)MyBitMap->size().y / SplitY);

	for (int i = 0; i < SplitY; i++)
	{
		for (int j = 0; j < SplitX; j++)
		{
			VectorMySplit.push_back(
				{ KPos2(j * SplitSizeX, i * SplitSizeY), KPos2(SplitSizeX , SplitSizeY) });
		}
	}
}
void KSpriteRender::set_idx(const int& _X, const int& _Y)
{
	idx = _X + SplitX * _Y;
}

void KSpriteRender::set_idx(const int& _Idx)
{
	if (0 > _Idx)
	{
		idx = 0;
	}
	else if((int)VectorMySplit.size() <= _Idx)
	{
		idx = (int)VectorMySplit.size() - 1;
	}
	else
	{
		idx = _Idx;
	}
}



KSize2& KSpriteRender::set_bitsize()
{
	RenderSize = KSize2(MyBitMap->size() / KSize2(SplitX, SplitY));
	return RenderSize;
}



bool KSpriteRender::init()
{
	KRenderer::init();
	idx = 0;

	return true;
}

void KSpriteRender::render()
{
	TransparentBlt(
		kwindow()->bhdc(),
		(int)RenderPos.x,
		(int)RenderPos.y,
		(int)RenderSize.x,
		(int)RenderSize.y,
		MyBitMap->MyDC,
		(int)VectorMySplit[idx].Pos.x,
		(int)VectorMySplit[idx].Pos.y,
		(int)VectorMySplit[idx].Size.x,
		(int)VectorMySplit[idx].Size.y,
		RGB(255, 0, 255));
}
void KSpriteRender::render(HDC _Hdc)
{
	TransparentBlt(
		_Hdc,
		(int)RenderPos.x,
		(int)RenderPos.y,
		(int)RenderSize.x,
		(int)RenderSize.y,
		MyBitMap->MyDC,
		(int)VectorMySplit[idx].Pos.x,
		(int)VectorMySplit[idx].Pos.y,
		(int)VectorMySplit[idx].Size.x,
		(int)VectorMySplit[idx].Size.y,
		RGB(255, 0, 255));
}