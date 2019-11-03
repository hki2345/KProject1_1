#pragma once
#include <vector>
#include <KVector.h>


class KScene;
class ComPlayer;
class KOne;
class MapManager
{
public:
	MapManager();
	~MapManager();
	
private:
	KScene* pScene;
	ComPlayer* pPlayer;
	std::vector<KOne*> VecDeco;

public:
	void create(KScene* _Scene, ComPlayer* _Player);
	void update();

private:
	void update_deco();
	KPos2 check_mindeco();
	KPos2 check_maxdeco();
};

