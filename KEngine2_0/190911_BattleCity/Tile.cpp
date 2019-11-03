#include "Tile.h"
#include "TileManager.h"
#include "PlayerManager.h"

#include <KSpriteRender.h>
#include <KRectCollision.h>
#include <KScene.h>
#include <KOne.h>


Tile::Tile()
{
}


Tile::~Tile()
{
}



void Tile::create()
{
	sName = L"Tile";

	kone()->size({ TILEXSIZE, TILEYSIZE });
	MyRenderer = kone()->add_component<KSpriteRender>();
	MyRenderer->init();
	MyRenderer->active_frame(false);
}


void Tile::update()
{
	KComponent::update();
	if (eTileType != ePrevTileType)
	{
		eTileType = ePrevTileType;
	}
}

void Tile::set_tile(const BATTLECITY_GAMETILE& _Info)
{
	MyRenderer->set_idx((int)_Info);
	ePrevTileType = _Info;
}

void Tile::set_tile(const KPos2& _Pos, const BATTLECITY_GAMETILE& _Info)
{
	kone()->pos(_Pos);

	if (BATTLECITY_GAMETILE::BG_WOOD_BLOCK == _Info)
	{
		MyRenderer->pivot(KPos2(STARTXPOS * 1.0f, STARTYPOS * 1.0f));
		MyRenderer->active_frame(true);
		MyRenderer->set_bit(L"BattleCity\\TileSpriteSub.bmp", 11);
	}
	else
	{
		MyRenderer->set_bit(L"BattleCity\\TileSpriteSub.bmp", 9);
	}

	// 있을거만 있어야함 -> 탱크 통과하는 건 총알도 통과함
	if (BATTLECITY_GAMETILE::BG_BROWN_BLOCK == _Info ||
		BATTLECITY_GAMETILE::BG_STONE_BLOCK == _Info ||
		BATTLECITY_GAMETILE::BG_WATER_BLOCK01 == _Info ||
		BATTLECITY_GAMETILE::BG_PHOENIX01 == _Info|| 
		BATTLECITY_GAMETILE::BG_PHOENIX02 == _Info||
		BATTLECITY_GAMETILE::BG_PHOENIX03 == _Info||
		BATTLECITY_GAMETILE::BG_PHOENIX04 == _Info)
	{
		TankCollider = kone()->add_component<KRectCollision>();
		TankCollider->pivot(KPos2(STARTXPOS * 1.0f, STARTYPOS * 1.0f));
		TankCollider->set_rect(0);
	}

	MyRenderer->set_split(3, 8);
	MyRenderer->set_idx((int)_Info);
	ePrevTileType = _Info;
}

void Tile::update_trans()
{
	MyRenderer->update_trans(MyRenderer->kscene()->SceneCamPos);
}

void Tile::render(HDC _Hdc)
{
	MyRenderer->render(_Hdc);
}


bool Tile::collision_bullet(const KPos2& _BulletDir, const KPos2& _BulletPos)
{
	KRect Tmp = TankCollider->rect_collision();
	switch (eTileType)
	{
	case BG_STONE_BLOCK:
		return true;

	case BG_BROWN_BLOCK:
	{
		if (KPos2::Down == _BulletDir)
		{
			set_tile(BG_RECTBROWN01);
		}
		else if (KPos2::Right == _BulletDir)
		{
			set_tile(BG_RECTBROWN02);
		}
		else if (KPos2::Left == _BulletDir)
		{
			set_tile(BG_RECTBROWN03);
		}
		else if (KPos2::Up == _BulletDir)
		{
			set_tile(BG_RECTBROWN04);
		}
		TileManager::instance()->update_tile(this);
		return true;
	}
	case BG_RECTBROWN01:
	case BG_RECTBROWN02:
	case BG_RECTBROWN03:
	case BG_RECTBROWN04:
	case BG_SMALLBROWN01:
	case BG_SMALLBROWN02:
	case BG_SMALLBROWN03:
	case BG_SMALLBROWN04:
	{
		TileManager::instance()->update_rectbrowntile(this, _BulletDir, _BulletPos);
		return true;
	}
	case BG_PHOENIX01:
	case BG_PHOENIX02:
	case BG_PHOENIX03:
	case BG_PHOENIX04:
		PlayerManager::instance()->iWin = -1;
		TileManager::instance()->update_broken();		
		return true;

	default:
		break;
	}

	return false;
}