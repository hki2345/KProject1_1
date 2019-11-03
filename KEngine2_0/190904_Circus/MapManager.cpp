#include "MapManager.h"

#include "ComPlayer.h"
#include "BackDeco.h"
#include "Miter.h"

#include <KScene.h>
#include <KOne.h>
#include <KScene.h>
#include <KWindow.h>

#include <KTextRender.h>
#include <KBitMapRender.h>
#include <KBitMapAnimator.h>


MapManager::MapManager()
{
}


MapManager::~MapManager()
{
}

void MapManager::create(KScene* _Scene, ComPlayer* _Player)
{
	int DecoSize = 14;
	int BackSize = 8;

	std::vector<KOne*> VecBackGround;
	pScene = _Scene;
	pPlayer = _Player;

	for (int i = 0; i < BackSize; i++)
	{
		VecBackGround.push_back(_Scene->create_kone(L"BackGround"));
		VecBackGround[i]->pos(KPos2((float)i * 100.0f, 270.0f));
		VecBackGround[i]->size({ 100.0f, 300.0f });

		KBitMapRender* BRE = VecBackGround[i]->add_component<KBitMapRender>();
		BRE->set_bit(L"Circus\\back.bmp", 5, true);
		BRE->set_hold();
	}




	for (int i = 0; i < DecoSize; i++)
	{
		VecDeco.push_back(_Scene->create_kone(L"BackDeco"));
		VecDeco[i]->pos(KPos2((float)i * 75.0f, 195.0f));
		VecDeco[i]->size({ 80.0f, 80.0f });
	}

	for (int i = 0; i < DecoSize; i++)
	{
		BackDeco* TDeco = VecDeco[i]->add_component<BackDeco>();
		TDeco->set_player(_Player);

		if (i == 5)
		{
			KBitMapRender* DRE = VecDeco[i]->add_component<KBitMapRender>();
			DRE->set_bit(L"Circus\\back_deco.bmp", 6, true);
		}
		else
		{
			TDeco->set_activedeco();
			KBitMapAnimator* DRE = VecDeco[i]->add_component<KBitMapAnimator>();
			std::vector<std::wstring> Tmp;
			Tmp.push_back(L"Circus\\back_normal.bmp");
			DRE->insert_animation(L"Idle", Tmp, 6, .1f, 0, true);

			Tmp.clear();
			Tmp.push_back(L"Circus\\back_normal.bmp");
			Tmp.push_back(L"Circus\\back_normal2.bmp");
			DRE->insert_animation(L"Win", Tmp, 6, .1f, 0, true);
		}
	}



	for (size_t i = 0; i < 14; i++)
	{
		KOne* TOne = _Scene->create_kone(L"Miter");
		TOne->size({ 100.0f, 30.0f });
		TOne->pos({ 400.0f + i * 400.0f, 520.0f });


		Miter* ComTmp = TOne->add_component<Miter>();
		ComTmp->set_player(_Player);

		KBitMapRender* BRE = TOne->add_component<KBitMapRender>();
		BRE->set_bit(L"Circus\\miter.bmp", 6, true);

		KTextRender* TRE = TOne->add_component<KTextRender>();
		TRE->set_font(std::to_wstring(500 - (i + 1) * 100).c_str(), 15, 7, L"DungGeunMo");
		TRE->pivot(KPos2(45.0f, 7.0f));
	}
}


void MapManager::update()
{
	update_deco();
}

void MapManager::update_deco()
{
	for (size_t i = 0; i < VecDeco.size(); i++)
	{
		if (KPos2::Right == pPlayer->scroll_dir() &&
			KPos2::Left == pScene->outof_screen(VecDeco[i]))
		{
			VecDeco[i]->pos(check_maxdeco());
		}
		else if (
			KPos2::Left == pPlayer->scroll_dir() &&
			KPos2::Right == pScene->outof_screen(VecDeco[i]))
		{
			VecDeco[i]->pos(check_mindeco());
		}
	}
}

KPos2 MapManager::check_mindeco()
{
	float MinX = pScene->kwindow()->size().x + VecDeco[0]->kscene()->SceneCamPos.x;
	KOne* MinOne = nullptr;

	for (size_t i = 0; i < VecDeco.size(); i++)
	{
		float Tmp = VecDeco[i]->pos().x;

		if (MinX >= Tmp)
		{
			MinX = Tmp;
			MinOne = VecDeco[i];
		}
	}

	if (nullptr == MinOne)
	{
		return KPos2::Zero;
	}

	return MinOne->pos() - KPos2(MinOne->size().x, .0f);
}

KPos2 MapManager::check_maxdeco()
{
	float MaxX = .0f;
	KOne* MaxOne = nullptr;

	for (size_t i = 0; i < VecDeco.size(); i++)
	{
		float Tmp = VecDeco[i]->pos().x;

		if (MaxX < Tmp)
		{
			MaxX = Tmp;
			MaxOne = VecDeco[i];
		}
	}

	if (nullptr == MaxOne)
	{
		return KPos2::Zero;
	}

	return MaxOne->pos() + KPos2(MaxOne->size().x, .0f);
}