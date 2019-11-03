#pragma once
#include <KCommon.h>


class CircusScene;
class IntroScene;
class GameManager : public KSingleton<GameManager>
{

private:
	CircusScene* GameScene;
	IntroScene* InScene;

public:
	void init();
	void update();

	void reset_game();
	void end_game();
};

