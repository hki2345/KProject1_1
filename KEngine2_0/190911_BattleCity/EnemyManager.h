#pragma once

#include <vector>
#include <KVector.h>
#include <KMacro.h>


class KScene;
class KBitMap;
class EnemyTank;
class EnemyManager
{
private:
	// 본체에서는 해야하니까
	EnemyManager() {} /* = delete*/;
	EnemyManager(const EnemyManager& _Other) = delete;
	EnemyManager(const EnemyManager&& _Other) = delete;
	void operator=(const EnemyManager& _Other) = delete;
	~EnemyManager() {};
	static EnemyManager* pKEnemyManager;

public:
	static EnemyManager* instance()
	{
		if (nullptr == pKEnemyManager)
		{
			pKEnemyManager = new EnemyManager();
		}

		return pKEnemyManager;
	}
	void release() { RELEASE_PTR(pKEnemyManager); }

private:
	std::vector<EnemyTank*> VectorEnemy;
	std::vector<KPos2> VectorRespawnPos;
	KScene* MomScene;
	int EnemyRespawnCnt;
	int EnemyMaxCnt;
	int EnemyActiveCurCnt;
	int EnemyActiveMaxCnt;

	float fRespawnCurTime;
	float fRespawnTime;

public:
	void create(KScene* _Scene);
	bool init(const int& _EnemyNum);
	void update();

	int calculate_remain();
	void shutdown_enemy();

private:
	void update_respawn();
	void update_resetpos();
	void update_playerwin();


	bool check_respawn(const KPos2& _Pos);

	void set_enemy(EnemyTank* Tank = nullptr, const bool& _Set = true);
};

