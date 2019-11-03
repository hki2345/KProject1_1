#include "Bullet.h"
#include <BattleTile.h>

#include <KSpriteRender.h>
#include <KRectCollision.h>
#include <K2DCollider.h>
#include <KScene.h>
#include <KOne.h>

#include "Explosion_Effect.h"

#include "TileManager.h"
#include "Tile.h"


Bullet::Bullet()
{
}


Bullet::~Bullet()
{
}



void Bullet::create()
{
	KComponent::create();

	kone()->size({ 20.0f, 20.0f });
	sName = L"Bullet";

	MyMoveSprite = kone()->add_component<KSpriteRender>();
	MyMoveSprite->set_bit(L"BattleCity\\Bullet.bmp", 5);
	MyMoveSprite->set_split(4, 1);
	fSpeed = 300.0f;

	MyCollider = kone()->add_component<KRectCollision>();
	MyCollider->insert_stayfunc<Bullet>(this, &Bullet::stay);

	MyEffect = kscene()->create_kone(L"Expolsion")->add_component<Explosion_Effect>();

	kone()->active_frame(false);
}

void Bullet::set_tank(const int& _Layer)
{
	MyCollider->set_rect(_Layer);
}



void Bullet::set_bullet(const KPos2& _Pos, const KPos2& _Dir)
{
	kone()->active_frame(true);
	kone()->pos(_Pos);
	vDir = _Dir;

	if (vDir == KPos2::Left)
	{
		MyMoveSprite->set_idx(1);
	}
	else if (vDir == KPos2::Right)
	{
		MyMoveSprite->set_idx(3);
	}
	else if (vDir == KPos2::Up)
	{
		MyMoveSprite->set_idx(2);
	}
	else if (vDir == KPos2::Down)
	{
		MyMoveSprite->set_idx(0);
	}

	bExplosion = false;
}


void Bullet::set_bomb()
{
	kone()->active_frame(false);
}

void Bullet::update()
{
	KComponent::update();

	kone()->moving_delta(vDir * fSpeed);
	update_outofgame();
}



void Bullet::update_outofgame()
{
	if (true == bExplosion)
	{
		set_bomb();
		MyEffect->set_bulletexplosion(kone()->pos());

		return;
	}

	KPos2 Tmp = kone()->pos();
	if (Tmp.x <= TileManager::instance()->tilemap_size().Start.x - kone()->size().x ||
		Tmp.x >= TileManager::instance()->tilemap_size().End.x + kone()->size().x ||
		Tmp.y <= TileManager::instance()->tilemap_size().Start.y - kone()->size().x ||
		Tmp.y >= TileManager::instance()->tilemap_size().End.y + kone()->size().x)
	{
		set_bomb();
		MyEffect->set_bulletexplosion(kone()->pos());
	}
}

void Bullet::stay(KOne* _Collider)
{
	Bullet* CurBullet = _Collider->get_component<Bullet>();
	if (nullptr != CurBullet)
	{
		kone()->active_frame(false);
	}

	Tile* CurTile = _Collider->get_component<Tile>();
	if (nullptr != CurTile && true == CurTile->collision_bullet(vDir, kone()->pos()))
	{
		bExplosion = true;
	}
}