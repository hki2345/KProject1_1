#include "CircusScene.h"
#include "ComPlayer.h"


#include "MapManager.h"
#include "ObstacleManager.h"
#include "UIManager.h"

#include <KTimeManager.h>
#include <KOne.h>
#include <KMacro.h>


CircusScene::CircusScene()
{
}


CircusScene::~CircusScene()
{
}

void CircusScene::create()
{
	KScene::create();

	KOne* OnePlayer = create_kone(L"Player");
	pPlayer = OnePlayer->add_component<ComPlayer>();

	pMapManager = new MapManager();
	pMapManager->create(this, pPlayer);

	pObsManager = new ObstacleManager();
	pObsManager->create(this, pPlayer);

	pUIManager = new UIManager();
	pUIManager->create(this, pPlayer);
}


bool CircusScene::init()
{
	KScene::init();

	bStart = false;
	fWaitTime = .0f;
	fStartTime = 3.0f;

	fFireTime = .0f; 
	fFireSpawnTime = 3.0f;


	fFastFireTime = .0f;
	fFastFireSpawnTime = 6.0f;


	fItemFireTime = .0f;
	fItemFireSpawnTime = 10.0f;


	iPotMiter = 400.0f;
	fPotDistance = .0f;
	fPotSpawnDistance = 200.0f;


	pUIManager->set_wait();
	pObsManager->init_fire();
	return true;
}


void CircusScene::update()
{
	KScene::update();
	
	if (false == bStart)
	{
		pUIManager->set_wait();
		update_wait();
		return;
	}


	pMapManager->update();
	pUIManager->update_gameUI();

	spwan_fire();
	spwan_pot();
	// spwan_itemfire();
	spwan_fastfire();
}

void CircusScene::update_wait()
{
	fWaitTime += KTimeManager::instance()->deltatime();
	if (fWaitTime >= fStartTime)
	{
		bStart = true;
		pPlayer->set_play();
		pUIManager->set_game();
	}
}



void CircusScene::spwan_fire()
{
	fFireTime += KTimeManager::instance()->deltatime();
	if (fFireTime >= fFireSpawnTime)
	{
		pObsManager->init_fire();
		fFireTime = .0f;
	}
}

void CircusScene::spwan_fastfire()
{
	fItemFireTime += KTimeManager::instance()->deltatime();
	if (fItemFireTime >= fItemFireSpawnTime)
	{
		pObsManager->init_fastfire();
		fItemFireTime = .0f;
	}
}


void CircusScene::spwan_itemfire()
{
	fFastFireTime += KTimeManager::instance()->deltatime();
	if (fFastFireTime >= fFastFireSpawnTime)
	{
		pObsManager->init_itemfire();
		fFastFireTime = .0f;
	}
}

void CircusScene::spwan_pot()
{
	fPotDistance = pPlayer->kone()->pos().x;

	if (fPotDistance >= fPotSpawnDistance)
	{
		pObsManager->init_pot();
		fPotSpawnDistance += iPotMiter;
	}
}



void CircusScene::release()
{
	RELEASE_PTR(pMapManager);
	RELEASE_PTR(pUIManager);
	RELEASE_PTR(pObsManager);
	KScene::release();
}