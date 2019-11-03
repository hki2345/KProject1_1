#include "BackDeco.h"
#include "ComPlayer.h"
#include <KBitMapAnimator.h>


#include "KInputManager.h"
#include "KOne.h"
#include <Windows.h>




BackDeco::BackDeco() : bActiveDeco(false)
{
}


BackDeco::~BackDeco()
{
}


bool BackDeco::init()
{
	CircusObject::init();
	pDecoAnimator = kone()->get_component<KBitMapAnimator>();

	if (nullptr != pDecoAnimator)
	{
		pDecoAnimator->change_animation(L"Idle");
	}

	return true;
}

void BackDeco::update()
{
	if (true == pPlayer->check_win() && true == bActiveDeco)
	{
		pDecoAnimator->change_animation(L"Win");
	}
}