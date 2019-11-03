#pragma once
#include "Tank.h"

class Score_Effect;
class EnemyTank : public Tank
{
public:
	EnemyTank();
	~EnemyTank();


private:
	Score_Effect* MyScoreEffect;

	float fDirChangeCurTime;
	float fDirChangeTime;

	float fShootCurTime;
	float fShootTime;

	float fDirectionCurTime;
	float fDirectionTime;

public:
	void create() override;
	bool init() override;
	void update() override;

private:
	void update_AI();
	void update_move();
	void update_collisiontile();
	void update_direction();

	void stay_tile(KOne* _Tile) override;
	void exit_tile(KOne* _Tile) override;
};

