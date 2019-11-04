#include "KSoundPlayer.h"
#include "KSound.h"
#include <KResourceManager.h>


void KSoundPlayer::set_sound(const wchar_t* _Name)
{
	MyKSound = KResourceManager<KSound>::instance()->find(_Name);
}

void KSoundPlayer::play()
{
	KSoundManager::instance()->system()->playSound(MyKSound->sound(), 0, false, &channel);
}
