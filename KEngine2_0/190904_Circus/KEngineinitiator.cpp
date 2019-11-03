#include "KEngineinitiator.h"
#include "KSceneManager.h"
#include "GameManager.h"

KEngineinitiator::KEngineinitiator()
{
}


KEngineinitiator::~KEngineinitiator()
{
	int a = 0;
}


bool KEngineinitiator::init()
{
	GameManager::instance()->init();

	return true;
}

