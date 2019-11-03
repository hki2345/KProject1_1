#pragma once
#include <vector>


class KScene;
class KOne;
class KTextRender;
class ComPlayer;
class UIManager
{
public:
	UIManager();
	~UIManager();

private:
	ComPlayer* pPlayer;

	std::vector<KOne*> VecWait;
	std::vector<KOne*> VecGame;
	std::vector<KOne*> LifeImage;

	KTextRender* pScore;
	KTextRender* pBonus;

	int BonusScore;
	bool bSetGame;


	float MinusBonus;
	float MinusBonusScoreDelta;

public:
	void create(KScene* _Scene, ComPlayer* _Player);

	void set_wait();
	void set_game();
	

	void update_gameUI();

private:
	void create_wait(KScene* _Scene);
	void create_game(KScene* _Scene);
	void create_life(KScene* _Scene);
};

