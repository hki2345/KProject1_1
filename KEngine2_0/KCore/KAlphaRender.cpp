#include "KAlphaRender.h"
#include <KResourceManager.h>

#include "KWindow.h"
#include "KTransform.h"
#include "KScene.h"
#include "KBitMap.h"

#pragma comment(lib, "msimg32.lib")


KAlphaRender::KAlphaRender() :
	MyBitMap(nullptr),
	MyBlendFunc(BLENDFUNCTION()),
	SplitX(0),
	SplitY(0),
	idx(0)
{
}


KAlphaRender::~KAlphaRender()
{
}

void KAlphaRender::create()
{
	KRenderer::create();
	sName = L"KAlphaRender";
}

void KAlphaRender::set_bit(
	const wchar_t* _Name /*= L"NONE"*/,
	const int& _Key /*= 0*/)
{
	MyBitMap = KResourceManager<KBitMap>::instance()->find(_Name);
	kscene()->insert_krender(this, _Key);
	MyBlendFunc.AlphaFormat = 0;
	MyBlendFunc.BlendFlags = 0;
	MyBlendFunc.BlendOp = AC_SRC_OVER;
	MyBlendFunc.SourceConstantAlpha = 255 / 2;
}
void KAlphaRender::change_bit(
	const wchar_t* _Name /*= L"NONE"*/)
{
	MyBitMap = KResourceManager<KBitMap>::instance()->find(_Name);
}
void KAlphaRender::set_split(const int& _X, const int& _Y)
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
void KAlphaRender::set_idx(const int& _X, const int& _Y)
{
	idx = _X + SplitX * _Y;
}

void KAlphaRender::set_idx(const int& _Idx)
{
	if (0 > _Idx)
	{
		idx = 0;
	}
	else if ((int)VectorMySplit.size() <= _Idx)
	{
		idx = (int)VectorMySplit.size() - 1;
	}
	else
	{
		idx = _Idx;
	}
}

void KAlphaRender::set_alpha(const BYTE& _Value)
{
	MyBlendFunc.SourceConstantAlpha = _Value;
}

bool KAlphaRender::init()
{
	KRenderer::init();
	idx = 0;

	return true;
}

void KAlphaRender::render()
{
	AlphaBlend(
		kwindow()->bhdc(),
		(int)RenderPos.x,
		(int)RenderPos.y,
		(int)MyTrans->Size.x,
		(int)MyTrans->Size.y,
		MyBitMap->MyDC,
		(int)VectorMySplit[idx].Pos.x,
		(int)VectorMySplit[idx].Pos.y,
		(int)VectorMySplit[idx].Size.x,
		(int)VectorMySplit[idx].Size.y,
		MyBlendFunc);
}
void KAlphaRender::render(HDC _Hdc)
{
	AlphaBlend(
		kwindow()->bhdc(),
		(int)RenderPos.x,
		(int)RenderPos.y,
		(int)MyTrans->Size.x,
		(int)MyTrans->Size.y,
		MyBitMap->MyDC,
		(int)VectorMySplit[idx].Pos.x,
		(int)VectorMySplit[idx].Pos.y,
		(int)VectorMySplit[idx].Size.x,
		(int)VectorMySplit[idx].Size.y,
		MyBlendFunc);
}