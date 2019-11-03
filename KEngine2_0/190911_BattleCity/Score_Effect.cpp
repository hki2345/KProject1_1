#include "Score_Effect.h"
#include <KTextRender.h>

#include <KTimeManager.h>
#include <BattleTile.h>
#include <KScene.h>
#include <KOne.h>

Score_Effect::Score_Effect()
{
}


Score_Effect::~Score_Effect()
{
}

void Score_Effect::create()
{
	kone()->active_frame(false);
	MyRender = kone()->add_component<KTextRender>();
	MyRender->set_font(L"1", 15
		
		
		, 100, L"DungGeunMo", RGB(255, 255, 255));


	fFloatingCurTime = .0f;
	fFloatingTime = 1.0f;
}
void Score_Effect::set_score(const KPos2& _Pos, const int& _Score)
{
	kone()->active_frame(true);
	kone()->pos(_Pos + KPos2(TILEXSIZE, TILEYSIZE));

	std::wstring Tmp;
	Tmp = std::to_wstring(_Score);
	MyRender->set_text(Tmp.c_str());

	fFloatingCurTime = .0f;
}


void Score_Effect::update()
{
	KComponent::update();

	fFloatingCurTime += KTimeManager::instance()->deltatime();
	if (fFloatingCurTime >= fFloatingTime)
	{
		kone()->active_frame(false);
	}

	kone()->moving_delta(KPos2::Down * 50.0f);
}