#include "GMMakerInitiator.h"
#include <KResourceManager.h>
#include <KSound.h>
#include <KBitMap.h>
#include <KOne.h>
#include <KSoundPlayer.h>

#include <KSceneManager.h>
#include <KScene.h>


void GMMakerInitiator::init()
{
	// KResourceManager<KBitMap>::instance()->load_forder(L"res\\Music");
	KResourceManager<KSound>::instance()->load_forder(L"res\\Music");

	KScene* NewIntroScene = KSceneManager::instance()->create_scene(L"Test");
	KSceneManager::instance()->change_scene(L"Test");

	KOne* TOne = NewIntroScene->create_kone(L"asdf");
	KSoundPlayer* TSound = TOne->add_component<KSoundPlayer>();
	TSound->set_sound(L"res\\Music\\RedFlavor.mp3");
	TSound->play();

}
