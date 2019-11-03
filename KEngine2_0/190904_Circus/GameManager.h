#pragma once
#include <KCommon.h>


class BnBScene;
class IntroScene;
class GameManager : public KSingleton<GameManager>
{

private:
	BnBScene* GameScene;
	IntroScene* InScene;

public:
	void init();
	void update();

	void reset_game();
	void end_game();
};

