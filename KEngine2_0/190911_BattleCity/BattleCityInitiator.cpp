#include "BattleCityInitiator.h"

#include <KOne.h>
#include <KWindowManager.h>
#include <KSceneManager.h>
#include <KResourceManager.h>
#include <KTimeManager.h>
#include <KDebugManager.h>
#include <KBitMap.h>
#include <KSound.h>
#include <KSoundPlayer.h>


#include "BattleScene.h"
#include "IntroScene.h"
#include "OutroScene.h"




BattleCityInitiator::BattleCityInitiator()
{
}


BattleCityInitiator::~BattleCityInitiator()
{
}


bool BattleCityInitiator::init()
{
	srand(GetTickCount64());

	KResourceManager<KBitMap>::instance()->load_forder(L"BattleCity");
	KResourceManager<KSound>::instance()->load_forder(L"BattleCity");
	KResourceManager<KBitMap>::instance()->add_font(L"BattleCity\\DungGeunMo.ttf");


	IntroScene*  NewIntroScene = new IntroScene();
	BattleScene*  NewGameScene = new BattleScene();
	OutroScene* NewOutroScene = new OutroScene();

	KSceneManager::instance()->create_scene(NewIntroScene, L"Intro");
	KSceneManager::instance()->create_scene(NewGameScene, L"Game");
	KSceneManager::instance()->create_scene(NewOutroScene, L"Outro");
	KSceneManager::instance()->change_scene(L"Intro");


	KOne* TOne = NewIntroScene->create_kone(L"asdf");
	KSoundPlayer* TSound = TOne->add_component<KSoundPlayer>();
	TSound->set_sound(L"BattleCity\\drumloop.wav");
	TSound->play();

	return true;
}