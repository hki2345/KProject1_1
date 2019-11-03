#include "IntroScene.h"
#include "GameManager.h"

#include <KWindow.h>
#include <KTextRender.h>
#include <KBitMapRender.h>
#include <KBitMapAnimator.h>

#include <KInputManager.h>

#include <KOne.h>



IntroScene::IntroScene()
{
}


IntroScene::~IntroScene()
{
}

void IntroScene::create()
{
	KScene::create();

	// create_backboard();
	create_star();
	create_circuschaley();
}

void IntroScene::update() 
{
	KScene::update();
	if (true == KInputManager::instance()->is_down(VK_SPACE))
	{
		GameManager::instance()->reset_game();
	}
}

void IntroScene::create_backboard()
{
	KOne* TOne = create_kone(L"BackBoard");
	TOne->size(kwindow()->size());

	KBitMapRender* BITREN = TOne->add_component<KBitMapRender>();
	BITREN->set_bit(L"Circus\\BackBoard.bmp", 0);
}

void IntroScene::create_star()
{
	float TSize = 20.0f;
	int Cnt = 0;

	for (int y = 0; y < 8; y++)
	{
		for (int x = 0; x < 16; x++)
		{
			if ((0 == x && 0 == y) || (15 == x && 0 == y) || 
				(0 == x && 7 == y) || (15 == x && 7 == y) ||
				((0 < x && 15 > x) && (0 < y && 7 > y)))
			{
				continue;
			}

			KOne* TOne = create_kone(L"Star");
			TOne->pos(KPos2(200.0f + x * (TSize + 5), 100.0f + y * TSize));
			TOne->size(KPos2(TSize, TSize));

			KBitMapAnimator* TRE = TOne->add_component<KBitMapAnimator>();

			std::vector<std::wstring> Tmp;
			Tmp.push_back(L"Circus\\star.bmp");
			Tmp.push_back(L"Circus\\star1.bmp");
			Tmp.push_back(L"Circus\\star2.bmp");
			TRE->insert_animation(L"Run", Tmp, 10, 0.1f, Cnt % 3);
			++Cnt;
		}
	}

}

void IntroScene::create_circuschaley()
{
	KOne* TOne = create_kone(L"Circus Chaley");
	TOne->pos(KPos2(400, 160));

	KTextRender* TREN = TOne->add_component<KTextRender>();
	TREN->set_font(L"서커스 찰리", 40, 10, L"DungGeunMo", RGB(97, 198, 233));



	TOne = create_kone(L"Game Start");
	TOne->pos(KPos2(400, 450));

	TREN = TOne->add_component<KTextRender>();
	TREN->set_font(L"게임 시작 - SPACE BAR", 40, 10, L"DungGeunMo");
}