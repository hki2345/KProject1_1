#include "EnemyTank.h"
#include <KTimeManager.h>

#include <KSpriteAnimator.h>
#include <KRectCollision.h>
#include <KScene.h>
#include <KOne.h>

#include "Score_Effect.h"
#include "Bullet.h"
#include "PlayerManager.h"
#include "PlayerTank.h"


EnemyTank::EnemyTank()
{
}


EnemyTank::~EnemyTank()
{
}

void EnemyTank::create()
{
	Tank::create();

	MyCollider->set_rect(2);
	MyAnimator->set_bit(L"BattleCity\\WhiteTank.bmp", 10);

	MyCollider->insert_stayfunc<EnemyTank>(this, &EnemyTank::stay_tile);
	MyCollider->insert_exitfunc<EnemyTank>(this, &EnemyTank::exit_tile);

	for (size_t i = 0; i < VectorMyBullet.size(); i++)
	{
		VectorMyBullet[i]->set_tank(4);
	}

	KOne* NewScore = kscene()->create_kone(L"Score Effect");
	MyScoreEffect = NewScore->add_component<Score_Effect>();
}

bool EnemyTank::init()
{
	Tank::init();

	fDirChangeCurTime = .0f;
	fDirChangeTime = 1.0f;

	fShootCurTime = .0f;
	fShootTime = 1.0f;

	fDirectionCurTime = .0f;
	fDirectionTime = .3f;

	return true;
}

void EnemyTank::update()
{
	if (Tank::TS_PLAY == eCurState)
	{
		update_collisiontile();
		update_AI();
		Tank::update();
		update_move();
	}
	else if (Tank::TS_DIE == eCurState)
	{
		PlayerManager::instance()->iKill += 1;
		PlayerManager::instance()->iScore += 500;
		MyScoreEffect->set_score(kone()->pos(), 500);
		Tank::update();
	}

	else
	{
		Tank::update();
	}
}


void EnemyTank::update_AI()
{
	if (fDirChangeCurTime <= fDirChangeTime)
	{
		fDirChangeCurTime += KTimeManager::instance()->deltatime();
	}
	else
	{
		update_direction();
	}


	if (fShootCurTime <= fShootTime)
	{
		fShootCurTime += KTimeManager::instance()->deltatime();
	}
	else
	{
		int XXX = 0;

		fShootCurTime = .0f;
		XXX = rand() % 10;

		// if (3 < XXX)
		{
			if (true == VectorMyBullet[0]->kone()->active_frame())
			{
				return;
			}
			shoot_bullet();
		}
	}	
}

void EnemyTank::update_move()
{
	Tank::update_move();

}

void EnemyTank::update_collisiontile()
{
	if (true == bTileCol || true == bTankCol)
	{
		kone()->pos(vPrevChecPos);

		if (true == bTankCol)
		{
			fDirectionCurTime += KTimeManager::instance()->deltatime();
			if (fDirectionCurTime >= fDirectionTime)
			{
				update_direction();
			}
		}
	}
	else
	{
		fDirectionCurTime = .0f;
	}
}

void EnemyTank::update_direction()
{
	int XXX = 0;
	fDirChangeCurTime = .0f;
	XXX = rand() % 4;

	if (0 == XXX)
	{
		vDir = KPos2::Down;
	}
	else if (1 == XXX)
	{
		vDir = KPos2::Up;
	}
	else if (2 == XXX)
	{
		vDir = KPos2::Left;
	}
	else if (3 == XXX)
	{
		vDir = KPos2::Right;
	}
}


void EnemyTank::stay_tile(KOne* _Other)
{
	Tank::stay_tile(_Other);

	PlayerTank* PTank = _Other->get_component<PlayerTank>();
	if (nullptr != PTank)
	{
		bTankCol = true;
		PrevColTank = PTank;
	}

	EnemyTank* ETank = _Other->get_component<EnemyTank>();
	if (nullptr != ETank)
	{
		bTankCol = true;
		PrevColTank = ETank;
	}
}

void EnemyTank::exit_tile(KOne* _Other)
{
	Tank::exit_tile(_Other);

	PlayerTank* PTank = _Other->get_component<PlayerTank>();
	if (nullptr != PTank)
	{
		PrevColTank = nullptr;
		bTankCol = false;
	}

	EnemyTank* ETank = _Other->get_component<EnemyTank>();
	if (nullptr != ETank)
	{
		PrevColTank = nullptr;
		bTankCol = false;
	}
}