#pragma once
#include <KScene.h>


class IntroScene : public KScene
{
public:
	IntroScene();
	~IntroScene();

public:
	void update() override;
	void create() override;

private:
	void create_backboard();
	void create_star();
	void create_circuschaley();
};

