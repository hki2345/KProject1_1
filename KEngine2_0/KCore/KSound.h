#pragma once
#include <KResource.h>
#include "KSoundManager.h"


class KSound final : public KResource
{
public:
	KSound() {};
	~KSound() override;


private:
	FMOD::Sound* MySound = nullptr;

public:
	bool load() override;
	bool save() override { return false;  };
	FMOD::Sound* sound()
	{
		return MySound;
	}
};

