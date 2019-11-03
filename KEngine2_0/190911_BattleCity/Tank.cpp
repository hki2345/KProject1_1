#include "Tank.h"
#include <KOne.h>
#include <KScene.h>

#include <KSpriteAnimator.h>
#include <KRectCollision.h>
#include <KTimeManager.h>
#include <KDebugManager.h>


#include "Explosion_Effect.h"
#include "Tile.h"
#include "Bullet.h"
#include "TileManager.h"
#include "BattleTile.h"

Tank::Tank()
{
}


Tank::~Tank()
{
}


void Tank::create()
{
	sName = L"Tank";
	kone()->size({ 39.0f, 39.0f });


	MyAnimator = kone()->add_component<KSpriteAnimator>();
	MyAnimator->init();
	MyAnimator->set_bit(L"BattleCity\\WhiteTank.bmp", 10);
	MyAnimator->set_split(8, 9);
	MyAnimator->insert_animation(L"UpIdle", 0, 0);
	MyAnimator->insert_animation(L"DownIdle", 4, 4);
	MyAnimator->insert_animation(L"LeftIdle", 2, 2);
	MyAnimator->insert_animation(L"RightIdle", 6, 6);
	MyAnimator->insert_animation(L"Up", 0, 1);
	MyAnimator->insert_animation(L"Left", 2, 3);
	MyAnimator->insert_animation(L"Down", 4, 5);
	MyAnimator->insert_animation(L"Right", 6, 7);
	MyAnimator->insert_animation(L"Respawn", 64, 70, .05f);
	MyAnimator->change_animation(L"UpIdle");


	fSpeed = 100.0f;

	MyCollider = kone()->add_component<KRectCollision>();
	// TankCollider->pivot(KPos2(STARTXPOS * -1.0f, STARTYPOS * -1.0f));


	for (size_t i = 0; i < 2; i++)
	{
		KOne* NewBullet = kscene()->create_kone(L"Bullet");
		VectorMyBullet.push_back(NewBullet->add_component<Bullet>());
	}

	MyEffect = kscene()->create_kone(L"Expolsion")->add_component<Explosion_Effect>();
}

bool Tank::init()
{
	vDir = KPos2::Up;
	vPrevDir = KPos2::Up;
	bTileCol = false;
	bMapCol = false;

	PrevColTile = nullptr;
	PrevColTank = nullptr;
	fRespawnCurTime = .0f;
	fRespawnTime = 1.5f;
	return true;
}


void Tank::set_tank(const KPos2& _StartPos)
{
	kone()->active_frame(true);
	kone()->pos(_StartPos);

	vDir = KPos2::Up;
	eCurState = TANK_STATUS::TS_RESPAWN;
}

void Tank::update() 
{
	switch (eCurState)
	{
	case Tank::TS_RESPAWN:
		update_respawn();
		break;
	case Tank::TS_PLAY:
		update_play();
		break;
	case Tank::TS_DIE:
		update_die();
		break;
	case Tank::TS_WAIT:
		update_wait();
		break;
	default:
		break;
	}
}

void Tank::update_respawn()
{
	MyCollider->active_frame(true);
	MyAnimator->change_animation(L"Respawn");
	fRespawnCurTime += KTimeManager::instance()->deltatime();
	if (fRespawnCurTime >= fRespawnTime)
	{
		// MyCollider->active_frame(true);
		fRespawnCurTime = .0f;
		eCurState = TANK_STATUS::TS_PLAY;
	}
}

void Tank::update_play()
{
	if (vDir == KPos2::Zero)
	{
		if (vPrevDir == KPos2::Down)
		{
			MyAnimator->change_animation(L"UpIdle");
		}
		else if (vPrevDir == KPos2::Up)
		{
			MyAnimator->change_animation(L"DownIdle");
		}
		else if (vPrevDir == KPos2::Left)
		{
			MyAnimator->change_animation(L"LeftIdle");
		}
		else if (vPrevDir == KPos2::Right)
		{
			MyAnimator->change_animation(L"RightIdle");
		}
	}
	else if (vPrevDir == KPos2::Left)
	{
		MyAnimator->change_animation(L"Left");
	}
	else if (vPrevDir == KPos2::Right)
	{
		MyAnimator->change_animation(L"Right");
	}
	else if (vPrevDir == KPos2::Down)
	{
		MyAnimator->change_animation(L"Up");
	}
	else if (vPrevDir == KPos2::Up)
	{
		MyAnimator->change_animation(L"Down");
	}

	update_checkingpos();
	update_coltile();
}
void Tank::update_die()
{
	kone()->active_frame(false);
	eCurState = TANK_STATUS::TS_WAIT;
}

void Tank::update_wait()
{

}

void Tank::shoot_bullet()
{
	KPos2 Dir = vPrevDir;
	VectorMyBullet[0]->set_bullet(
		kone()->pos() +
		kone()->size() * Dir * .25f +
		kone()->size() * Dir.reverse().abs() * .25f,
		vPrevDir);
}


void Tank::update_coltile()
{
	if (nullptr != PrevColTile && false == PrevColTile->kone()->active_frame())
	{
		PrevColTile = nullptr;
		bTileCol = false;
	}

	if (nullptr != PrevColTank && false == PrevColTank->kone()->active_frame())
	{
		PrevColTank = nullptr;
		bTankCol = false;
	}
}

void Tank::update_checkingpos()
{
	if (vDir != vPrevDir)
	{
		if ((vDir == KPos2::Right || vDir == KPos2::Left /*|| vDir == KPos2::Zero*/) &&
			(vPrevDir == KPos2::Up || vPrevDir == KPos2::Down))
		{
			KPos2 Tmp = kone()->pos();

			int Nam = (int)Tmp.y % TILEYSIZE;
			int Mok = (int)Tmp.y / TILEYSIZE;

			if (TILEYSIZE / 2 > Nam)
			{
				kone()->pos(KPos2(Tmp.x, Mok * TILEYSIZE));
			}
			else
			{
				kone()->pos(KPos2(Tmp.x, Mok * TILEYSIZE + (TILEYSIZE)));
			}
		}

		else if ((vDir == KPos2::Up || vDir == KPos2::Down /*|| vDir == KPos2::Zero*/) &&
			(vPrevDir == KPos2::Left || vPrevDir == KPos2::Right))
		{
			KPos2 Tmp = kone()->pos();

			int Nam = (int)Tmp.x % TILEXSIZE;
			int Mok = (int)Tmp.x / TILEXSIZE;

			if (TILEXSIZE / 2 > Nam)
			{
				kone()->pos(KPos2(Mok * TILEXSIZE, Tmp.y));
			}
			else
			{
				kone()->pos(KPos2(Mok * TILEXSIZE + (TILEXSIZE), Tmp.y));
			}
		}

		if (vDir != KPos2::Zero)
		{
			vPrevDir = vDir;
		}
	}
}

void Tank::update_move()
{
	vPrevChecPos = kone()->pos();
	KPos2 Tmp = kone()->pos() + vDir * fSpeed * KTimeManager::instance()->deltatime();
	if (Tmp.x >= TileManager::instance()->tilemap_size().Start.x &&
		Tmp.x <= TileManager::instance()->tilemap_size().End.x &&
		Tmp.y >= TileManager::instance()->tilemap_size().Start.y &&
		Tmp.y <= TileManager::instance()->tilemap_size().End.y)
	{
		kone()->moving_pos(Tmp);
		bMapCol = false;
	}

	bMapCol = true;
}


void Tank::stay_tile(KOne* _Other)
{
	Tile* CurTile = _Other->get_component<Tile>();
	if (nullptr != CurTile && 
		BATTLECITY_GAMETILE::BG_METAL_BLOCK != CurTile->tile_type())
	{
		bTileCol = true;
		PrevColTile = CurTile;
	}

	Bullet* CurBullet = _Other->get_component<Bullet>();
	if (nullptr != CurBullet && eCurState != TANK_STATUS::TS_RESPAWN)
	{
		CurBullet->set_bomb();
		MyEffect->set_tankexplosion(kone()->pos());
		eCurState = TANK_STATUS::TS_DIE;
	}
}


void Tank::exit_tile(KOne* _Other)
{
	Tile* CurTile = _Other->get_component<Tile>();
	if (nullptr != CurTile)
	{
		PrevColTile = nullptr;
		bTileCol = false;
	}	
}