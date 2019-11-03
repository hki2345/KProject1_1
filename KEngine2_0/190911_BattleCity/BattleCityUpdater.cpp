#include "BattleCityUpdater.h"
#include <KDebugManager.h>
#include <KTimeManager.h>


BattleCityUpdater::BattleCityUpdater()
{
}


BattleCityUpdater::~BattleCityUpdater()
{
}



void BattleCityUpdater::update()
{
	KDebugManager::instance()->insert_log(L"Delta Time: %f", KTimeManager::instance()->deltatime());
	KDebugManager::instance()->insert_log(L"FPS: %f", KTimeManager::instance()->fps());
}