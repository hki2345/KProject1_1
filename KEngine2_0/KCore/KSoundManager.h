#pragma once
#include <KCommon.h>
#include <string>

#include <Fmod/fmod.hpp>
#include <Fmod/common.h>
#include <map>



class KSoundPlayer;
class KSoundManager :
	public KSingleton<KSoundManager>
{
private:
	FMOD::System* MySystem;
	std::map<std::wstring, KSoundPlayer*> MapSoundPlay;


public:
	void init();
	
	FMOD::System* system()
	{
		return MySystem;
	}
};

