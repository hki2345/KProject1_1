#include "CircusObject.h"
#include "ComPlayer.h"
#include <KScene.h>
#include <KOne.h>




CircusObject::CircusObject()
{
}


CircusObject::~CircusObject()
{
}

void CircusObject::create()
{
	MyOriginPos = kone()->pos();
}

bool CircusObject::init()
{
	kone()->pos(MyOriginPos);
	fColHeight = 300.0f;
	fBaseSpeed = 150.0f;
	fObsSpeed = .0f;


	return true;
}