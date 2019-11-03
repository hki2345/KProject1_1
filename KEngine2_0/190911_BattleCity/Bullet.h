#pragma once
#include <KComponent.h>
#include <KVector.h>


class Explosion_Effect;
class KSpriteRender;
class KRectCollision;
class K2DCollider;
class Bullet : public KComponent
{
public:
	Bullet();
	~Bullet();

private:
	Explosion_Effect* MyEffect;
	KSpriteRender* MyMoveSprite;
	KRectCollision* MyCollider;
	KPos2 vDir;
	float fSpeed;

	bool bExplosion;

public:
	void create() override;
	void set_tank(const int& _Layer);
	void set_bullet(const KPos2& _Pos, const KPos2& _Dir);
	void set_bomb();
	void update() override;

private:
	void update_outofgame();

	void stay(KOne* _Collider);
};

