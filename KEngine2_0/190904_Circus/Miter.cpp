#include "Miter.h"
#include "ComPlayer.h"

#include <KScene.h>
#include <KOne.h>


#include <KBitMapRender.h>




Miter::Miter()
{
}


Miter::~Miter()
{
}

bool Miter::init()
{
	CircusObject::init();
	pBitRender = kone()->get_component< KBitMapRender>();
	return true;
}