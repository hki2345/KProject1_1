#include "PlayerManager.h"

#include <KTimeManager.h>
#include <KFileStream.h>
#include <KOne.h>
#include <KScene.h>
#include "PlayerTank.h"


PlayerManager* PlayerManager::pPlayerManager = nullptr;

void PlayerManager::create(KScene* _GameScene)
{
	KOne* CurSorOne = _GameScene->create_kone(L"PlayerTank");
	pUserTank = CurSorOne->add_component<PlayerTank>();

	iStage = 1;
	iLife = 3;
	iScore = 0;

	fRespawnCurDelay = 500.0f;
	fRespawnDelay = 3.0f;

	load_highscore();
}

void PlayerManager::init()
{
	iStage = 1;
	iLife = 3;
	iScore = 0;

	iWin = 0;
	iKill = 0;
	pUserTank->set_tank({ 220.0f, 500.0f });
}

void PlayerManager::update()
{
	if (fRespawnCurDelay <= fRespawnDelay)
	{
		fRespawnCurDelay += KTimeManager::instance()->deltatime();
		if (fRespawnCurDelay >= fRespawnDelay && iLife > 0)
		{
			pUserTank->set_tank({ 220.0f, 500.0f });
		}
	}
}

void PlayerManager::update_playerdie()
{
	iLife -= 1;

	if (0 >= iLife)
	{
		iWin = -1;
	}
	fRespawnCurDelay = .0f;
}



void PlayerManager::load_highscore()
{
	KFileStream::instance()->read_file(L"BattleCity\\highscore.btscore", iHighScore);
}

void PlayerManager::save_highscore()
{
	KFileStream::instance()->write_file(L"BattleCity\\highscore.btscore", iHighScore);
}

void PlayerManager::set_highscore()
{
	if (iScore > iHighScore)
	{
		iHighScore = iScore;
		save_highscore();
	}
}