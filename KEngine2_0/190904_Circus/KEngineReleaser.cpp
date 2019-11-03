#include "KEngineReleaser.h"
#include "GameManager.h"



KEngineReleaser::KEngineReleaser()
{
}


KEngineReleaser::~KEngineReleaser()
{
}

void KEngineReleaser::release()
{
	GameManager::instance()->release();
}