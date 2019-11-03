#pragma once
#include <KComponent.h>
#include <KVector.h>

struct SCORE_INFO
{
	int Life;
	int Score;
};

class KBitMapAnimator;
class ComPlayer : public KComponent
{
public:
	ComPlayer();
	~ComPlayer();

private:
	enum ACT_STATE
	{
		WAIT = 0,
		IDLE,
		RUN,
		JUMP,
		WIN,
		DIE,
	};

private:
	KBitMapAnimator* pAnimator;
	KPos2 ePlayerDir;
	ACT_STATE ePlayerAct;

	KPos2 fDirWalk[3];
	float fWalkSpeed;
	float fwalk_distance;
	float fmax_distance;

	float fJumpTime;
	float fJumpPower;
	float fbottom;

	SCORE_INFO sScoreInfo;

public:
	void create() override;
	bool init() override;
	void update() override;

	// -1 왼쪽 0 정지 1 오른쪽
	KPos2 scroll_dir();

	void set_play();
	void set_win();
	void set_failed();
	void set_item();
	void plus_score();
	bool check_win();
	bool check_acting();

	inline SCORE_INFO& score_info()
	{
		return sScoreInfo;
	}

private:
	void update_input();

	void update_wait();
	void update_idle();
	void update_run();
	void update_jump();
	void update_win();
	void update_die();

	void update_move();
};

