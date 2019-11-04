#include "KSoundManager.h"
#include <KMacro.h>


void KSoundManager::init()
{
	FMOD_RESULT       result;

	unsigned int      version;
	void* extradriverdata = 0;

	result = FMOD::System_Create(&MySystem);
	result = MySystem->getVersion(&version);
	result = MySystem->init(32, FMOD_INIT_NORMAL, extradriverdata);
}
