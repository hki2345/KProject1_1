#include "OutroScene.h"
#include <KTextRender.h>
#include <KSpriteRender.h>
#include <KOne.h>

#include <KWindowManager.h>
#include <KSceneManager.h>
#include <KInputManager.h>
#include <KTimeManager.h>

#include "PlayerManager.h"


OutroScene::OutroScene()
{
}


OutroScene::~OutroScene()
{
}



void OutroScene::create()
{
	KScene::create();
	for (int i = 0; i < 15; i++)
	{
		VectorUI.push_back(create_kone(L"OutroUI"));
	}
	int FSize = 20;

	KTextRender* Text1 = VectorUI[0]->add_component< KTextRender>();
	Text1->set_font(L"최고 점수", FSize, 10, L"DungGeunMo", RGB(255, 94, 0));

	ActionText.push_back(VectorUI[1]->add_component< KTextRender>());
	ActionText[0]->set_font(L"점수", FSize, 10, L"DungGeunMo", RGB(255, 187, 0));

	ActionText.push_back(VectorUI[2]->add_component< KTextRender>());
	ActionText[1]->set_font(L"스테이지 ", FSize, 10, L"DungGeunMo", RGB(255, 255, 255));

	Text1 = VectorUI[3]->add_component< KTextRender>();
	Text1->set_font(L"플레이어1 ", FSize, 10, L"DungGeunMo", RGB(255, 94, 0), TA_RIGHT);

	ActionText.push_back(VectorUI[4]->add_component< KTextRender>());
	ActionText[2]->set_font(L"현재 점수", FSize, 10, L"DungGeunMo", RGB(255, 187, 0), TA_RIGHT);



	ActionText.push_back(VectorUI[5]->add_component< KTextRender>());
	ActionText[3]->set_font(L"1456 점", FSize, 10, L"DungGeunMo", RGB(255, 255, 255), TA_RIGHT);
	ActionText.push_back(VectorUI[6]->add_component< KTextRender>());
	ActionText[4]->set_font(L"14 킬", FSize, 10, L"DungGeunMo", RGB(255, 255, 255), TA_LEFT);


	Text1 = VectorUI[7]->add_component< KTextRender>();
	Text1->set_font(L"합계 ", FSize, 10, L"DungGeunMo", RGB(255, 255, 255), TA_RIGHT);

	ActionText.push_back(VectorUI[8]->add_component< KTextRender>());
	ActionText[5]->set_font(L"123455", FSize, 10, L"DungGeunMo", RGB(255, 255, 255), TA_LEFT);

	

	KSize2 UISize = { 40.0f, 40.0f };

	VectorUI[9]->size(UISize);
	KSpriteRender* Renderer = VectorUI[9]->add_component< KSpriteRender>();
	Renderer->set_bit(L"BattleCity\\WhiteTank.bmp");
	Renderer->render_size(UISize);
	Renderer->set_split(8, 9);
	Renderer->set_idx(0);
}
bool OutroScene::init()
{
	KScene::init();
	KWindowManager::instance()->backcolor(RGB(0, 0, 0));

	iBaseTankCnt = 0;


	VectorUI[0]->pos({ 300.0f, 50.0f });
	VectorUI[1]->pos({ 450.0f, 50.0f });
	VectorUI[2]->pos({ 400.0f, 100.0f });

	VectorUI[3]->pos({ 280.0f, 150.0f });
	VectorUI[4]->pos({ 280.0f, 200.0f });

	VectorUI[5]->pos({ 280.0f, 250.0f });
	VectorUI[6]->pos({ 350.0f, 250.0f });

	VectorUI[7]->pos({ 280.0f, 450.0f });
	VectorUI[8]->pos({ 300.0f, 450.0f });

	VectorUI[9]->pos({ 300.0f, 240.0f });

	fOutCurTime = .0f;
	fOutTime = 20.0f;


	fTankCalcCurTime = .0f;
	fTankCalcTime = .5f;

	iBaseTankScore = 100;

	ActionText[0]->set_text(std::to_wstring(PlayerManager::instance()->iHighScore).c_str());
	update_actiontext();

	eOState = OUTRO_STATE::CALC;


	return true;
}
void OutroScene::update()
{
	KScene::update();

	switch (eOState)
	{
	case OutroScene::CALC:
		update_calc();
		break;
	case OutroScene::WAIT:
		update_wait();
		break;
	default:
		break;
	}
}




void OutroScene::update_calc()
{
	if (iBaseTankCnt == PlayerManager::instance()->iKill)
	{
		eOState = OUTRO_STATE::WAIT;
		return;
	}

	fTankCalcCurTime += KTimeManager::instance()->deltatime();
	if (fTankCalcCurTime >= fTankCalcTime)
	{
		fTankCalcCurTime = .0f;
		iBaseTankCnt += 1;

		PlayerManager::instance()->iScore += iBaseTankScore;
	}

	update_actiontext();
}



void OutroScene::update_wait()
{
	fOutCurTime += KTimeManager::instance()->deltatime();
	if (
		fOutCurTime >= fOutTime ||
		true == KInputManager::instance()->is_down(VK_SPACE))
	{
		fOutCurTime = .0f;
		
		PlayerManager::instance()->set_highscore();

		if (-1 == PlayerManager::instance()->iWin)
		{
			PlayerManager::instance()->iScore = 0;
			KSceneManager::instance()->change_scene(L"Intro");
		}

		else
		{
			if (PlayerManager::instance()->iStage > 3)
			{
				PlayerManager::instance()->iStage = 1;
				KSceneManager::instance()->change_scene(L"Intro");
			}
			else
			{
				PlayerManager::instance()->iStage += 1;
				KSceneManager::instance()->change_scene(L"Game");
			}
		}		
	}
}


void OutroScene::update_actiontext()
{
	std::wstring Tmp = L"";

	Tmp = L"스테이지 ";
	Tmp += std::to_wstring(PlayerManager::instance()->iStage).c_str();
	ActionText[1]->set_text(Tmp.c_str());

	Tmp = std::to_wstring(PlayerManager::instance()->iScore).c_str();
	Tmp += L"";
	ActionText[2]->set_text(Tmp.c_str());


	Tmp = std::to_wstring(iBaseTankCnt * iBaseTankScore).c_str();
	Tmp += L" 점";
	ActionText[3]->set_text(Tmp.c_str());


	Tmp = std::to_wstring(iBaseTankCnt).c_str();
	Tmp += L" 킬";
	ActionText[4]->set_text(Tmp.c_str());


	Tmp = std::to_wstring(iBaseTankCnt).c_str();
	Tmp += L" 킬";
	ActionText[5]->set_text(Tmp.c_str());

}