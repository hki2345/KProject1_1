#include "EnemyManager.h"
#include "PlayerManager.h"

#include <KTimeManager.h>
#include <KScene.h>
#include <KOne.h>

#include "TileManager.h"
#include "EnemyTank.h"

EnemyManager* EnemyManager::pKEnemyManager = nullptr;

void EnemyManager::create(KScene* _Scene)
{
	MomScene = _Scene;

	VectorEnemy.reserve(50);

	for (int i = 0; i < 50; i++)
	{
		KOne* CurSorEnemy = MomScene->create_kone(L"EnemyTank");
		EnemyTank* Enemy = CurSorEnemy->add_component<EnemyTank>();

		VectorEnemy.push_back(Enemy);
		Enemy->kone()->active_frame(false);
	}
}


bool EnemyManager::init(const int& _EnemyNum)
{
	fRespawnCurTime = .0f;
	fRespawnTime = 5.0f;
	EnemyMaxCnt = _EnemyNum;
	EnemyRespawnCnt = 0;
	EnemyActiveCurCnt = 0;
	EnemyActiveMaxCnt = 4;

	VectorRespawnPos = *TileManager::instance()->vector_respawnpos();
	shutdown_enemy();
	set_enemy();

	return true;
}

void EnemyManager::update()
{
	update_respawn();
	update_resetpos();
	update_playerwin();
}


void EnemyManager::update_respawn()
{
	if (EnemyRespawnCnt == EnemyMaxCnt)
	{
		return;
	}

	fRespawnCurTime += KTimeManager::instance()->deltatime();
	if (fRespawnCurTime >= fRespawnTime)
	{
		fRespawnCurTime = .0f;
		set_enemy();
	}
}

void EnemyManager::update_resetpos()
{
	for (int i = 0; i < EnemyRespawnCnt; i++)
	{
		if (10.0f >= VectorEnemy[i]->kone()->pos().x)
		{
			set_enemy(VectorEnemy[i], false);
		}
	}
}

void EnemyManager::update_playerwin()
{
	if (PlayerManager::instance()->iKill == EnemyMaxCnt)
	{
		PlayerManager::instance()->iWin = 1;
	}
}

int EnemyManager::calculate_remain()
{
	return EnemyMaxCnt - EnemyRespawnCnt;
}



bool EnemyManager::check_respawn(const KPos2& _Pos)
{
	EnemyActiveCurCnt = 0;

	for (int i = 0; i < EnemyRespawnCnt; i++)
	{
		if (true == VectorEnemy[i]->kone()->active_frame())
		{
			EnemyActiveCurCnt += 1;
		}
		else
		{
			continue;
		}

		KPos2 Tmp = VectorEnemy[i]->kone()->pos() - _Pos;
		if (Tmp.distance() < TILEXSIZE)
		{
			return false;
		}
	}

	if (EnemyActiveMaxCnt <= EnemyActiveCurCnt)
	{
		return false;
	}

	return true;
}


void EnemyManager::set_enemy(EnemyTank* _Tank /*= nullptr*/, const bool& _Set /*= true*/)
{
	int XXX = 0;

	int cnt = 0;
	do
	{
		XXX = rand() % VectorRespawnPos.size();
		cnt += 1;

		if (3 < cnt)
		{
			return;
		}
	} 
	while (false == check_respawn(VectorRespawnPos[XXX]));

	if (true == _Set)
	{
		VectorEnemy[EnemyRespawnCnt]->set_tank(VectorRespawnPos[XXX]);
		EnemyRespawnCnt += 1;
	}
	else if (false == _Set && nullptr != _Tank)
	{
		_Tank->kone()->pos(VectorRespawnPos[XXX]);
	}
}

void EnemyManager::shutdown_enemy()
{
	for (int i = 0; i < 50; i++)
	{
		VectorEnemy[i]->kone()->active_frame(false);
	}
}