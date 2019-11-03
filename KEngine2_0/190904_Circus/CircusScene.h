#pragma once
#include <KScene.h>
#include <vector>


class MapManager;
class ObstacleManager;
class UIManager;
class ComPlayer;
class CircusScene : public KScene
{
public:
	CircusScene();
	~CircusScene();


private:
	ComPlayer* pPlayer;
	MapManager* pMapManager;
	ObstacleManager* pObsManager;
	UIManager* pUIManager;


	bool bStart;
	float fWaitTime;
	float fStartTime;

	float fFireTime;
	float fFireSpawnTime;

	float fFastFireTime;
	float fFastFireSpawnTime;

	float fItemFireTime;
	float fItemFireSpawnTime;


	float fPotDistance;
	float fPotSpawnDistance;
	float iPotMiter;

public:
	void create() override;
	bool init() override;
	void update() override;
	void release() override;

private:
	void update_wait();

	void spwan_itemfire();
	void spwan_fastfire();
	void spwan_fire();
	void spwan_pot();
};

