#include "Obstcle.h"
#include "ComPlayer.h"

#include <KWindow.h>
#include <KScene.h>
#include <KOne.h>



Obstcle::Obstcle()
{
}


Obstcle::~Obstcle()
{
}


void Obstcle::set_prop(const OBSTACLE_TYPE& _Type, const bool& _Fast)
{
	eObType = _Type;
	bFast = _Fast;	
}

bool Obstcle::init()
{
	CircusObject::init();
	if (eObType != OBSTACLE_TYPE::OT_FIRE &&
		eObType != OBSTACLE_TYPE::OT_ITEMFIRE)
	{
		fObsSpeed = .0f;
	}

	else if (true == bFast)
	{
		fObsSpeed = 120.0f;
	}
	else
	{
		fObsSpeed = 80.0f;
	}

	bCollider = false;
	return true;
}

void Obstcle::update()
{
	if (false == pPlayer->check_acting())
	{
		return;
	}


	switch (eObType)
	{
	case Obstcle::OT_FIRE:
	case Obstcle::OT_ITEMFIRE:
		update_fire();
		break;
	case Obstcle::OT_POT:
		update_pot();
		break;
	case Obstcle::OT_WINPAN:
		// update_winpan();
		break;
	default:
		break;
	}
	update_colide();
}



void Obstcle::update_fire()
{
	if (KPos2::Left == kscene()->outof_screen(kone()))
	{
		kone()->active_frame(false);
	}

	kone()->moving_delta(KPos2::Left * (fObsSpeed));


}
void Obstcle::update_pot()
{
	if (KPos2::Left == kscene()->outof_screen(kone()) || 2000.0f < kone()->pos().x)
	{
		kone()->active_frame(false);
	}
}

void Obstcle::update_colide()
{
	float colsize = 30.0f;

	switch (eObType)
	{
	case Obstcle::OT_ITEMFIRE:
		pPlayer->set_item();
		break;
	case Obstcle::OT_FIRE:
		if (true == collide_sub(kwindow()->size().y, 370.0f))
		{
			pPlayer->set_failed();
		}
		else if(false == bCollider && true == collide_sub(370.0f, 170.0f))
		{
			pPlayer->plus_score();
			bCollider = true;
		}


	case Obstcle::OT_POT:
		if (true == collide_sub(kwindow()->size().y, 370.0f))
		{
			pPlayer->set_failed();
		}
		else if (false == bCollider && true == collide_sub(370.0f, 170.0f))
		{
			pPlayer->plus_score();
			bCollider = true;
		}

		break;
	case Obstcle::OT_WINPAN:
		if (true == collide_sub(kwindow()->size().y, 370.0f))
		{
			pPlayer->set_win();
		}
		break;
	default:
		break;
	}
}

bool Obstcle::collide_sub(const float& _YPos1, const float& _YPos2)
{
	float YPos = pPlayer->kone()->pos().y;
	float colsize = 30.0f;
	if (YPos < _YPos1 &&
		YPos > _YPos2 &&
		kone()->pos().x - colsize < pPlayer->kone()->pos().x &&
		kone()->pos().x + colsize > pPlayer->kone()->pos().x)
	{
		return true;
	}

	return false;
}