#pragma once
#include "Tank.h"


class Shield_Effect;
class PlayerTank : public Tank
{
public:
	PlayerTank();
	~PlayerTank();

private:
	Shield_Effect* MyShieldEffect;

	float fShieldCurTime;
	float fShieldTime;

public:
	void create() override;
	bool init() override;
	void update() override;

private:
	void update_respawn() override;
	void update_shield();
	void update_input();
	void update_move();
	void update_collisiontile();


	void stay_tile(KOne* _Tile) override;
	void exit_tile(KOne* _Tile) override;
};

