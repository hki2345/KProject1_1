#include "IntroScene.h"

#include <KWindowManager.h>
#include <KInputManager.h>	
#include <KSceneManager.h>
#include <KTimeManager.h>

#include <KBitMapRender.h>
#include <KTextRender.h>
#include <KOne.h>

#include "PlayerManager.h"

IntroScene::IntroScene()
{
}


IntroScene::~IntroScene()
{
}


void IntroScene::create()
{
	KScene::create();
	VectorUISize = 9;
	VectorUI.reserve(VectorUISize);
	
	for (int i = 0; i < VectorUISize; i++)
	{
		VectorUI.push_back(KScene::create_kone(L"IntroUI"));
	}

	KSize2 UISize = KSize2(600.0f, 300.0f);
	KBitMapRender* BattleSprite = VectorUI[0]->add_component<KBitMapRender>();
	BattleSprite->set_bit(L"BattleCity\\BattleLogo.bmp", 10);
	BattleSprite->render_size(UISize);

	KTextRender* Text1 = VectorUI[1]->add_component<KTextRender>();
	Text1->set_font(L"점수판...", 20, 10, L"DungGeunMo", RGB(255, 255, 255));
	KTextRender* Text2 = VectorUI[2]->add_component<KTextRender>();
	Text2->set_font(L"1 플레이어", 20, 10, L"DungGeunMo", RGB(255, 255, 255), TA_LEFT);
	KTextRender* Text3 = VectorUI[3]->add_component<KTextRender>();
	Text3->set_font(L"2 플레이어", 20, 10, L"DungGeunMo", RGB(255, 255, 255), TA_LEFT);
	KTextRender* Text4 = VectorUI[4]->add_component<KTextRender>();
	Text4->set_font(L"제작하기", 20, 10, L"DungGeunMo", RGB(255, 255, 255), TA_LEFT);
	KTextRender* Text5 = VectorUI[5]->add_component<KTextRender>();
	Text5->set_font(L"NAMCOT", 15, 10, L"휴먼둥근헤드라인", RGB(255, 0, 0));
	KTextRender* Text6 = VectorUI[6]->add_component<KTextRender>();
	Text6->set_font(L"ⓒ 1980 1985 NAMCO LTD.", 15, 10, L"DungGeunMo", RGB(255, 255, 255));
	KTextRender* Text7 = VectorUI[7]->add_component<KTextRender>();
	Text7->set_font(L"ALL RIGHTS RESERVED", 15, 10, L"DungGeunMo", RGB(255, 255, 255));

	UISize = KSize2(20.0f, 20.0f);
	KBitMapRender* BattleSelect = VectorUI[8]->add_component<KBitMapRender>();
	BattleSelect->set_bit(L"BattleCity\\PlayerSelect.bmp", 10);
	BattleSelect->render_size(UISize);

	
	
	UISize = KSize2(800.0f, 300.0f);
	for (int i = 0; i < 2; i++)
	{
		GrayBackBoard[i] = KScene::create_kone(L"BackBoard");
		KBitMapRender* Renderer = GrayBackBoard[i]->add_component<KBitMapRender>();
		Renderer->render_size(UISize);
		Renderer->set_bit(L"BattleCity\\GrayBackBoard.bmp", 10);
	}


}


bool IntroScene::init()
{
	KScene::init();
	KWindowManager::instance()->backcolor(RGB(0, 0, 0));
	vSize = KWindowManager::instance()->main_size();
	MaxYPos = 40.0f;



	for (size_t i = 0; i < VectorUI.size(); i++)
	{
		VectorUI[i]->active_frame(true);
	}

	for (int i = 0; i < 2; i++)
	{
		GrayBackBoard[i]->active_frame(false);
	}


	VectorUI[0]->pos({ 100.0f, 60.0f });

	VectorUI[1]->pos({ vSize.x / 2, MaxYPos });
	VectorUI[2]->pos({ 350.0f, 375.0f });
	VectorUI[3]->pos({ 350.0f, 400.0f });
	VectorUI[4]->pos({ 350.0f, 425.0f });
	
	VectorUI[3]->active_frame(false);
	VectorUI[4]->active_frame(false);
	
	VectorUI[5]->pos({ vSize.x / 2, 475.0f });
	VectorUI[6]->pos({ vSize.x / 2, 500.0f });
	VectorUI[7]->pos({ vSize.x / 2, 525.0f });

	VectorUI[8]->active_frame(false);


	GrayBackBoard[0]->pos({ .0f, 300.0f * -1.0f });
	GrayBackBoard[1]->pos({ .0f, vSize.y });


	std::wstring Tmp = L"현재 점수 - ";
	Tmp += std::to_wstring(PlayerManager::instance()->iScore);
	Tmp += L" 최고 점수 - ";
	Tmp += std::to_wstring(PlayerManager::instance()->iHighScore);

	KTextRender* Text1 = VectorUI[1]->get_component<KTextRender>();
	Text1->set_text(Tmp.c_str());


	for (size_t i = 0; i < VectorUI.size(); i++)
	{
		VectorUI[i]->moving_pluspos(KPos2::Up * 800.0f);
	}

	eIntroState = INTRO_STATE::IS_WAIT;
	fOutCurTime = .0f;
	fOutTime = 3.0f;

	return true;
}
void IntroScene::update()
{
	KScene::update();

	switch (eIntroState)
	{
	case IntroScene::IS_WAIT:
		update_wait();
		break;
	case IntroScene::IS_PLAY:
		update_play();
		break;
	case IntroScene::IS_OUT:
		update_out();
		break;
	default:
		break;
	}
}



void IntroScene::update_wait()
{
	for (size_t i = 0; i < VectorUI.size(); i++)
	{
		VectorUI[i]->moving_delta(KPos2::Down * 100.0f);
	}

	if (VectorUI[1]->pos().y <= MaxYPos || true == KInputManager::instance()->is_down(VK_SPACE))
	{
		VectorUI[8]->active_frame(true);
		VectorUI[8]->pos({ 300.0f, 375.0f });
		eIntroState = INTRO_STATE::IS_PLAY;
	}
}
void IntroScene::update_play()
{
	float X = KWindowManager::instance()->main_size().x / 2;
	VectorUI[0]->pos({ 100.0f, 60.0f });
	VectorUI[1]->pos({ X, MaxYPos });
	VectorUI[2]->pos({ 350.0f, 375.0f });
	VectorUI[3]->pos({ 350.0f, 400.0f });
	VectorUI[4]->pos({ 350.0f, 425.0f });
	VectorUI[5]->pos({ X, 475.0f });
	VectorUI[6]->pos({ X, 500.0f });
	VectorUI[7]->pos({ X, 525.0f });

	if (true == KInputManager::instance()->is_down(VK_SPACE))
	{
		eIntroState = INTRO_STATE::IS_OUT;

		for (size_t i = 0; i < VectorUI.size(); i++)
		{
			VectorUI[i]->active_frame(false);
		}
		for (int i = 0; i < 2; i++)
		{
			GrayBackBoard[i]->active_frame(true);
		}

	}
}
void IntroScene::update_out()
{
	GrayBackBoard[0]->moving_delta(KPos2::Up * 500.0f);
	GrayBackBoard[1]->moving_delta(KPos2::Down * 500.0f);

	if (GrayBackBoard[0]->pos().y >= .0f || true == KInputManager::instance()->is_down(VK_SPACE))
	{
		KSceneManager::instance()->change_scene(L"Game");
	}

}