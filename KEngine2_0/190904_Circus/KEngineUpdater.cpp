#include "KEngineUpdater.h"
#include "GameManager.h"

#include "KInputManager.h"
#include "KCore.h"


KEngineUpdater::KEngineUpdater()
{
}


KEngineUpdater::~KEngineUpdater()
{
}


void KEngineUpdater::update()
{
	GameManager::instance()->update();
}