#include "KBitMapRender.h"
#include <KResourceManager.h>

#include "KScene.h"
#include "KWindow.h"
#include "KTransform.h"
#include "KBitMap.h"
#include "KOne.h"


#pragma comment(lib, "msimg32.lib")


KBitMapRender::KBitMapRender() :
	MyBitMap(nullptr),
	MyBitState(false)
{
}


KBitMapRender::~KBitMapRender()
{
}

void KBitMapRender::create()
{
	KRenderer::create();
	sName = L"KBitMapRender";
}

void KBitMapRender::set_bit(
	const wchar_t* _Name /*= L"NONE"*/,
	const int& _Key /*= 0*/, 
	const bool& _bBitRender)
{
	MyBitState = _bBitRender;
	MyBitMap = KResourceManager<KBitMap>::instance()->find(_Name);
	kscene()->insert_krender(this, _Key);
}

KSize2& KBitMapRender::set_bitsize()
{
	RenderSize = MyBitMap->size();
	return RenderSize;
}

void KBitMapRender::change_bit(
	const wchar_t* _Name /*= L"NONE"*/, 
	const bool& _bBitRender /*= false*/)
{
	MyBitState = _bBitRender;
	MyBitMap = KResourceManager<KBitMap>::instance()->find(_Name);
}


void KBitMapRender::set_trans(const bool& _Type)
{
	MyBitState = _Type;
}

bool KBitMapRender::init()
{
	KRenderer::init();
		
	return true;
}
void KBitMapRender::render()
{
	if (false == bRender)
	{
		return;
	}

	if (true == MyBitState)
	{
		BitBlt(
			kwindow()->bhdc(),
			(int)RenderPos.x,
			(int)RenderPos.y,
			(int)MyTrans->Size.x,
			(int)MyTrans->Size.y,
			MyBitMap->MyDC,
			0,
			0,
			SRCCOPY);
	}
	else if(false == MyBitState)
	{
		TransparentBlt(
			kwindow()->bhdc(),
			(int)RenderPos.x,
			(int)RenderPos.y,
			(int)RenderSize.x,
			(int)RenderSize.y,
			MyBitMap->MyDC,
			0,
			0,
			(int)MyBitMap->size().x,
			(int)MyBitMap->size().y,
			RGB(255, 0, 255));
	}
}

void KBitMapRender::render(HDC _Hdc)
{
	if (true == MyBitState)
	{
		BitBlt(
			kwindow()->bhdc(),
			(int)RenderPos.x,
			(int)RenderPos.y,
			(int)MyTrans->Size.x,
			(int)MyTrans->Size.y,
			MyBitMap->MyDC,
			0,
			0,
			SRCCOPY);
	}
	else if (false == MyBitState)
	{
		TransparentBlt(
			kwindow()->bhdc(),
			(int)RenderPos.x,
			(int)RenderPos.y,
			(int)MyTrans->Size.x,
			(int)MyTrans->Size.y,
			MyBitMap->MyDC,
			0,
			0,
			(int)MyBitMap->size().x,
			(int)MyBitMap->size().y,
			RGB(255, 0, 255));
	}
}