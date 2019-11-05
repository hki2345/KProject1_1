#include "ComPlayer.h"
#include <KScene.h>
#include <KBitMapAnimator.h>
#include "GameManager.h"

#include <KTimeManager.h>
#include <KInputManager.h>
#include "KOne.h"

#include <math.h>
#include <Windows.h>



ComPlayer::ComPlayer()
{
}


ComPlayer::~ComPlayer()
{
}

void ComPlayer::create()
{
	pAnimator = kone()->add_component<KBitMapAnimator>();
	sScoreInfo.Life = 3;

	kone()->pos(KPos2::Zero);
	kone()->size(KPos2(80, 80));
	fJumpTime = .0f;

	std::vector<std::wstring> Tmp;
	Tmp.push_back(L"Circus\\player0.bmp");
	Tmp.push_back(L"Circus\\player1.bmp");
	Tmp.push_back(L"Circus\\player2.bmp");
	pAnimator->insert_animation(L"Run", Tmp, 10);

	Tmp.clear();
	Tmp.push_back(L"Circus\\player0.bmp");
	pAnimator->insert_animation(L"Idle", Tmp, 10);

	Tmp.clear();
	Tmp.push_back(L"Circus\\player2.bmp");
	pAnimator->insert_animation(L"Jump", Tmp, 10);


	Tmp.clear();
	Tmp.push_back(L"Circus\\die.bmp");
	pAnimator->insert_animation(L"Die", Tmp, 10);


	Tmp.clear();
	Tmp.push_back(L"Circus\\win.bmp");
	Tmp.push_back(L"Circus\\win2.bmp");
	pAnimator->insert_animation(L"Win", Tmp, 10);
}

bool ComPlayer::init()
{
	fDirWalk[0] = KPos2::Left;
	fDirWalk[1] = KPos2::Right;
	fDirWalk[2] = KPos2::Zero;


	fWalkSpeed = 150.0f;
	fwalk_distance = .0f;
	fmax_distance = 1500.0f;


	kone()->pos(KPos2(100, 440));
	kscene()->SceneCamPos = KPos2(kone()->pos().x - 100.0f, 0);
	fbottom = 440.0f;
	fJumpPower = 250.0f;

	ePlayerAct = ComPlayer::WAIT;
	
	if (0 > sScoreInfo.Life)
	{
		sScoreInfo.Life = 3;
	}
	

	sScoreInfo.Score = 0;

	return true;
}


void ComPlayer::update()
{
	update_input();
	switch (ePlayerAct)
	{
	case ComPlayer::WAIT:
		update_wait();
		break;

	case ComPlayer::IDLE:
		update_idle();
		break;
	case ComPlayer::RUN:
		update_run();
		break;
	case ComPlayer::JUMP:
		update_jump();
		break;
	case ComPlayer::WIN:
		update_win();
		break;
	case ComPlayer::DIE:
		update_die();
		break;
	default:
		break;
	}
}


KPos2 ComPlayer::scroll_dir()
{
	if (ACT_STATE::DIE == ePlayerAct ||
		ACT_STATE::WIN == ePlayerAct)
	{
		return KPos2::Zero;
	}

	if (fwalk_distance > fmax_distance - 100 &&
		fwalk_distance < fmax_distance + 100)
	{
		return KPos2::Zero;
	}

	return ePlayerDir;
}


void ComPlayer::update_input()
{
	if (false == check_acting())
	{
		return;
	}

	if (ACT_STATE::JUMP == ePlayerAct)
	{
		update_move();
		return;
	}

	if (true == KInputManager::instance()->is_press(VK_LEFT))
	{
		ePlayerDir = fDirWalk[0];
		ePlayerAct = ACT_STATE::RUN;
	}
	else if (true == KInputManager::instance()->is_press(VK_RIGHT) )
	{
		ePlayerDir = fDirWalk[1];
		ePlayerAct = ACT_STATE::RUN;
	}
	else
	{
		ePlayerDir = fDirWalk[2];
		ePlayerAct = ACT_STATE::IDLE;
	}	
}


void ComPlayer::set_play()
{
	ePlayerAct = ACT_STATE::IDLE;
}

void ComPlayer::set_win()
{
	ePlayerAct = ACT_STATE::WIN;
	kone()->pos(KPos2(kone()->pos().x, 400));
	if (true == KInputManager::instance()->is_down(VK_SPACE))
	{
		GameManager::instance()->reset_game();
	}
}
void ComPlayer::set_failed()
{
	ePlayerAct = ACT_STATE::DIE;

}

void ComPlayer::set_item()
{
	sScoreInfo.Score += 500;
}
void ComPlayer::plus_score()
{
	sScoreInfo.Score += 50;
}


bool ComPlayer::check_win()
{
	if (ePlayerAct == ACT_STATE::WIN)
	{
		return true;
	}

	return false;
}

bool ComPlayer::check_acting()
{
	if (ePlayerAct == ACT_STATE::WIN ||
		ePlayerAct == ACT_STATE::DIE ||
		ePlayerAct == ACT_STATE::WAIT)
	{
		return false;
	}

	return true;
}


void ComPlayer::update_wait()
{
	pAnimator->change_animation(L"Idle");
}
void ComPlayer::update_idle()
{
	pAnimator->change_animation(L"Idle");
}

void ComPlayer::update_run()
{
	pAnimator->change_animation(L"Run");
	update_move();
	if (true == KInputManager::instance()->is_down(VK_SPACE))
	{
		ePlayerAct = ACT_STATE::JUMP;
	}
}

void ComPlayer::update_jump()
{
	pAnimator->change_animation(L"Jump");
	fJumpTime += KTimeManager::instance()->deltatime();
	float T = cosf(fJumpTime * 2.0f);

	kone()->moving_delta({ .0f, (T * fJumpPower) * -1.0f });

	if (fbottom <= kone()->pos().y)
	{
		ePlayerAct = ACT_STATE::IDLE;
		kone()->pos({ kone()->pos().x + 0, fbottom });
		fJumpTime = .0f;
	}
}


void ComPlayer::update_win()
{
	pAnimator->change_animation(L"Win");
	if (true == KInputManager::instance()->is_press(VK_SPACE))
	{
		sScoreInfo.Life = 3;
		GameManager::instance()->end_game();
	}

}
void ComPlayer::update_die()
{
	pAnimator->change_animation(L"Die");
	if (true == KInputManager::instance()->is_press(VK_SPACE))
	{
		sScoreInfo.Life -= 1;
		if (sScoreInfo.Life < 0)
		{
			GameManager::instance()->end_game();
		}
		else
		{
			GameManager::instance()->reset_game();
		}
	}
}

void ComPlayer::update_move()
{
	if (fwalk_distance < fmax_distance)
	{
		fwalk_distance += fWalkSpeed * ePlayerDir.x * KTimeManager::instance()->deltatime();
	}

	else
	{
		fwalk_distance = fmax_distance;
	}
	   	
	kone()->moving_delta({ fWalkSpeed * ePlayerDir.x, 0 });

	if (kone()->pos().x - 100 > 0 && kone()->pos().x < fmax_distance)
	{
		kscene()->SceneCamPos = KPos2(kone()->pos().x - 100.0f, 0);
	}
}