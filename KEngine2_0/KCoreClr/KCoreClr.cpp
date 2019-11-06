#include "pch.h"

#include "KCoreClr.h"



KCoreClr::KPlayer::KPlayer()
{
	m_Player = new KSoundPlayer();
}
KCoreClr::KPlayer::~KPlayer()
{
	RELEASE_PTR(m_Player);
}


void KCoreClr::KPlayer::set_sound(const wchar_t* _Name)
{
	m_Player->set_sound(_Name);
}

void KCoreClr::KPlayer::play()
{
	m_Player->play();
}