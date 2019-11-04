#include "KSound.h"
#include <KPathManager.h>


KSound::~KSound() 
{
	if (nullptr != MySound)
	{
		MySound->release();
	}
}

bool KSound::load()
{
	FMOD_RESULT result;
	result = KSoundManager::instance()->system()->
		createSound(KPathManager::instance()->wchar_tochar(
			KResource::sPath.c_str()).c_str(), FMOD_DEFAULT, nullptr, &MySound);

	return false;
}
