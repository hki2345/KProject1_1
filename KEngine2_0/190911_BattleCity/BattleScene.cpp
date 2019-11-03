#include "BattleScene.h"


#include <KOne.h>
#include <KSpriteAnimator.h>
#include <KBitMapRender.h>
#include <KSpriteRender.h>
#include <KTextRender.h>
#include <KPathManager.h>

#include <KTimeManager.h>
#include <KSceneManager.h>	
#include <KWindowManager.h>
#include <KWindow.h>
#include <KMacro.h>

#include "EnemyTank.h"
#include "PlayerManager.h"
#include "TileManager.h"
#include "EnemyManager.h"



BattleScene::BattleScene()
{
}


BattleScene::~BattleScene()
{
}



void BattleScene::create()
{
	KScene::create();

	TileManager::instance()->create(this);
	EnemyManager::instance()->create(this);
	PlayerManager::instance()->create(this);

	// 0 타일
	// 1 플레이어 탱크
	// 2 적 탱크
	// 3 플레이어 총
	// 4 적 총
	link_k2dCollider(1, 0);
	link_k2dCollider(1, 2);
	link_k2dCollider(1, 4);
	
	link_k2dCollider(2, 0);
	link_k2dCollider(2, 2);

	link_k2dCollider(3, 0);
	link_k2dCollider(3, 2);
	link_k2dCollider(3, 4);
	
	link_k2dCollider(4, 0);
	
	create_startUI();
	create_gameUI();
	create_overUI();	
}


void BattleScene::create_startUI()
{
	for (int i = 0; i < 3; i++)
	{
		CoverUI.push_back(create_kone(L"Cover"));
	}

	CoverUI[0]->size({ 800.0f, 300.0f });
	KBitMapRender* Cover = CoverUI[0]->add_component<KBitMapRender>();
	Cover->set_bit(L"BattleCity\\GrayBackBoard.bmp", 100);
	CoverUI[1]->size({ 800.0f, 300.0f });

	Cover = CoverUI[1]->add_component<KBitMapRender>();
	Cover->set_bit(L"BattleCity\\GrayBackBoard.bmp", 100);
	 
	 KTextRender* CoverTExt = CoverUI[2]->add_component<KTextRender>();
	CoverTExt->set_font(L"Stage", 40, 101, L"DungGeunMo", RGB(0, 0, 0));
}
void BattleScene::create_gameUI()
{
	KSize2 UISize = { 20.0f, 20.0f };

	float XUI = 650.0f;
	for (int i = 0; i < 40; i++)
	{
		EnemyUI.push_back(create_kone(L"Enemy"));
		KBitMapRender* EnemyTile = EnemyUI[i]->add_component<KBitMapRender>();
		EnemyTile->set_bit(L"BattleCity\\EnemyUI.bmp");
		EnemyTile->render_size(UISize);
		EnemyUI[i]->size(UISize);
		EnemyUI[i]->pos( KPos2(XUI - 50.0f, 50.0f) + KPos2( 25 * (i / 5) , 25 * (i % 5) ));
	}


	for (int i = 0; i < 2; i++)
	{
		GameUI.push_back(create_kone(L"UserInfo"));		
	}

	KBitMapRender* UserInfo = GameUI[0]->add_component<KBitMapRender>();
	UserInfo->set_bit(L"BattleCity\\LifeInfoUI.bmp", 100);
	UserInfo->render_size(UISize);
	GameUI[0]->size(UISize);
	GameUI[0]->pos({ XUI - 50.0f, 300.0f });


	UISize = KSize2(40.0f, 40.0f );
	UserInfo = GameUI[1]->add_component<KBitMapRender>();
	UserInfo->set_bit(L"BattleCity\\StageInfoUI.bmp", 100);
	UserInfo->render_size(UISize);
	GameUI[1]->size(UISize);
	GameUI[1]->pos({ XUI, 450.0f });


	for (int i = 0; i < 3; i++)
	{
		GameTextUI.push_back(create_kone(L"UserInfo"));
	}
	KTextRender* TextInfo = GameTextUI[0]->add_component<KTextRender>();
	TextInfo->set_font(L"플레이어 1", 20, 100, L"DungGeunMo", RGB(0, 0, 0), TA_RIGHT);
	GameTextUI[0]->pos({ XUI + 50.0f, 280.0f });

	pLifeUI = GameTextUI[1]->add_component<KTextRender>();
	pLifeUI->set_font(L"1", 20, 100, L"DungGeunMo", RGB(0, 0, 0), TA_RIGHT);
	GameTextUI[1]->pos({ XUI - 10.0f, 300.0f });

	pStageUI = GameTextUI[2]->add_component<KTextRender>();
	pStageUI->set_font(L"1", 20, 100, L"DungGeunMo", RGB(0, 0, 0));
	GameTextUI[2]->pos({ XUI + 50.0f, 475.0f });
}
void BattleScene::create_overUI()
{
	for (int i = 0; i < 1; i++)
	{
		OverTextUI.push_back(create_kone(L"Over"));
	}
	KTextRender* TextInfo = OverTextUI[0]->add_component<KTextRender>();
	TextInfo->set_font(L"GAME OVER", 40, 150, L"DungGeunMo", RGB(255, 0, 0));
}


bool BattleScene::init()
{
	KScene::init();
	eGSState = BattleScene::GSS_START;

	fStartUICurTime = .0f;
	fStartUITime = 5.0f;

	fOverUICurTime = .0f;
	fOverUITime = 5.0f;

	KPos2 WSize = kwindow()->size();

	active_vector(CoverUI, true);

	CoverUI[0]->pos(KPos2::Zero);
	CoverUI[1]->pos(WSize * KPos2::Up * .5f);

	active_vector(EnemyUI, false);
	active_vector(GameUI, false);
	active_vector(GameTextUI, false);
	active_vector(OverTextUI, false);



	std::wstring Tmp = L"BattleCity\\Stage";
	Tmp += std::to_wstring(PlayerManager::instance()->iStage);
	Tmp += L".btd";

	TileManager::instance()->init(Tmp.c_str());
	return true;
}


void BattleScene::update()
{
	KScene::update();

	switch (eGSState)
	{
	case BattleScene::GSS_START:
		update_start();
		break;
	case BattleScene::GSS_WAIT:
		update_wait();
		break;
	case BattleScene::GSS_PLAY:
		update_play();
		break;
	case BattleScene::GSS_OVER:
		update_over();
		break;
	default:
		break;
	}
}

void BattleScene::render()
{
	TileManager::instance()->render();
	KScene::render();
}

void BattleScene::release()
{
	KScene::release();
	TileManager::instance()->release();
	EnemyManager::instance()->release();
	PlayerManager::instance()->release();
}



void BattleScene::update_start()
{
	fStartUICurTime += KTimeManager::instance()->deltatime();
	int Stage = PlayerManager::instance()->iStage;

	if (fStartUICurTime >= fStartUITime)
	{
		eGSState = GAMESCENE_STATE::GSS_WAIT;
		CoverUI[2]->active_frame(false);

		KWindowManager::instance()->backcolor(RGB(128, 128, 128));
	}
	else
	{
		KPos2 WSize = kwindow()->size();

		CoverUI[0]->pos(KPos2::Zero);
		CoverUI[1]->pos(WSize * KPos2::Up * .5f);

		std::wstring Tmp = L"스테이지 ";
		Tmp += std::to_wstring(Stage);
		CoverUI[2]->get_component<KTextRender>()->set_text(Tmp.c_str());
		CoverUI[2]->pos( WSize * .5f );

		TileManager::instance()->update_alltile();
	}
}

void BattleScene::update_wait()
{
	CoverUI[0]->moving_delta(KPos2::Down * 500.0f);
	CoverUI[1]->moving_delta(KPos2::Up * 500.0f);
	if (CoverUI[1]->pos().y > kwindow()->size().y)
	{
		eGSState = GAMESCENE_STATE::GSS_PLAY;
		active_vector(CoverUI, false);
		active_vector(CoverUI, false);
		active_vector(EnemyUI, true);
		active_vector(GameUI, true);
		active_vector(GameTextUI, true);

		stage_start();
	}
}


void BattleScene::stage_start()
{
	PlayerManager::instance()->init();
	EnemyManager::instance()->init(5 + PlayerManager::instance()->iStage * 3);
}

void BattleScene::update_play()
{
	EnemyManager::instance()->update();
	PlayerManager::instance()->update();
	update_playUI();
}
void BattleScene::update_over()
{
	fOverUICurTime += KTimeManager::instance()->deltatime();
	if (fOverUICurTime >= fOverUITime)
	{
		change_scene();
	}

	if (OverTextUI[0]->pos().y > kwindow()->size().y * .5f)
	{
		OverTextUI[0]->moving_delta(KPos2::Down * 200.0f);
	}
}

void BattleScene::update_playUI()
{
	pLifeUI->set_text(std::to_wstring(PlayerManager::instance()->iLife).c_str());
	pStageUI->set_text(std::to_wstring(PlayerManager::instance()->iStage).c_str());

	active_vector(EnemyUI, false);
	for (int i = 0; i < EnemyManager::instance()->calculate_remain(); i++)
	{
		EnemyUI[i]->active_frame(true);
	}

	if (1 == PlayerManager::instance()->iWin)
	{
		change_scene();
	}
	else if (
		-1 == PlayerManager::instance()->iWin ||
		0 >= PlayerManager::instance()->iLife)
	{
		eGSState = GAMESCENE_STATE::GSS_OVER;

		active_vector(OverTextUI, true);
		OverTextUI[0]->pos(kwindow()->size() * .5f + KPos2::Up * 300);
	}
}


void BattleScene::active_vector(const std::vector<KOne*>& _Vector, const bool& _Value)
{
	for (size_t i = 0; i < _Vector.size(); i++)
	{
		_Vector[i]->active_frame(_Value);
	}
}


void BattleScene::change_scene()
{
	EnemyManager::instance()->shutdown_enemy();
	KSceneManager::instance()->change_scene(L"Outro");
}