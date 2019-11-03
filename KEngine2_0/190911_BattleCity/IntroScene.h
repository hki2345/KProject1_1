#pragma once
#include <KScene.h>
#include <KVector.h>
#include <vector>


class KOne;
class IntroScene : public KScene
{
public:
	IntroScene();
	~IntroScene();

private:
	enum INTRO_STATE
	{
		IS_WAIT,
		IS_PLAY,
		IS_OUT,
	};

private:
	std::vector<KOne*> VectorUI;
	KOne* GrayBackBoard[2];


	KSize2 vSize;
	INTRO_STATE eIntroState;
	int VectorUISize;
	float MaxYPos;

	float fOutCurTime;
	float fOutTime;

public:
	void create() override;
	bool init() override;
	void update() override;

private:
	void update_wait();
	void update_play();
	void update_out();
};

