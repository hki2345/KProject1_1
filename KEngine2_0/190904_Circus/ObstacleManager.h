#pragma once
#include <vector>


class KScene;
class ComPlayer;
class KOne;
class ObstacleManager
{
public:
	ObstacleManager();
	~ObstacleManager();


private:
	std::vector<KOne*> VecFire;
	std::vector<KOne*> VecFastFire;
	std::vector<KOne*> VecItemFire;
	std::vector<KOne*> VecPot;

	KScene* ThisScene;

public:
	void create(KScene* _Scene, ComPlayer* _Player);
	void init_fire();
	void init_fastfire();
	void init_itemfire();
	void init_pot();

private:
	void create_obstacle(KScene* _Scene, ComPlayer* _Player);
	void create_winpan(KScene* _Scene, ComPlayer* _Player);

	KOne* create_fire(KScene* _Scene, ComPlayer* _Player, const bool& _Item, const bool& _Fast = false);
	KOne* create_pot(KScene* _Scene, ComPlayer* _Player);
};

