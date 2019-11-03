#include "KUIClicker.h"
#include "KOne.h"
#include "KTransform.h"
#include "KInputManager.h"




KUIClicker::KUIClicker() :
	MyTrans(nullptr),
	Id(0),
	bIsClicked(false)
{
}


KUIClicker::~KUIClicker()
{
}

void KUIClicker::create()
{
	sName = L"KUIClicker";
	if (nullptr == MyTrans)
	{
		MyTrans = kone()->get_component<KTransform>();
	}

	Id = 0;
	bIsClicked = false;
}

void KUIClicker::update()
{
	RECT rc = {
	   (LONG)MyTrans->Pos.x,
	   (LONG)MyTrans->Pos.y,
	   (LONG)MyTrans->Pos.x + (LONG)MyTrans->Size.x,
	   (LONG)MyTrans->Pos.y + (LONG)MyTrans->Size.y };


	KPos2 Pos = KInputManager::instance()->pos_mouse();
	POINT pt = { (LONG)Pos.x, (LONG)Pos.y };

	if (TRUE == PtInRect(&rc, pt) && true == KInputManager::instance()->is_down(VK_LBUTTON))
	{
		bIsClicked = true;
	}
	else
	{
		bIsClicked = false;
	}
}