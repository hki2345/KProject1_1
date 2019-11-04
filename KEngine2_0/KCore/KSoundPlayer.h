#pragma once
#include "KComponent.h"
#include "KSoundManager.h"


class KSound;
class KSoundPlayer :
	public KComponent
{
public:
	KSoundPlayer() {};
	virtual ~KSoundPlayer() {};

private:
	KSound* MyKSound;
	FMOD::Channel* channel = 0;

public:
	void set_sound(const wchar_t* _Name);
	void play();
};

