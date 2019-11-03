#include "KTransform.h"
#include "KTimeManager.h"




KTransform::KTransform()
{
}


KTransform::~KTransform()
{
}


void KTransform::create()
{
	sName = L"KTransform";
}

bool KTransform::init()
{
	return true;
}
void KTransform::update()
{

}
void KTransform::release()
{

}

void KTransform::moving_pluspos(const KVec2& _Speed)
{
	Pos += _Speed;
}

void KTransform::moving_pos(const KVec2& _Pos)
{
	Pos = _Pos;
}

void KTransform::moving_delta(const KVec2& _Speed)
{
	Pos += _Speed * KTimeManager::instance()->deltatime();
}