#pragma once
#include <KMacro.h>


class PlayerTank;
class KScene;
class PlayerManager
{
private:
	// 본체에서는 해야하니까
	PlayerManager() {} /* = delete*/;
	PlayerManager(const PlayerManager& _Other) = delete;
	PlayerManager(const PlayerManager&& _Other) = delete;
	void operator=(const PlayerManager& _Other) = delete;
	~PlayerManager() {};
	static PlayerManager* pPlayerManager;

public:
	static PlayerManager* instance()
	{
		if (nullptr == pPlayerManager)
		{
			pPlayerManager = new PlayerManager();
		}

		return pPlayerManager;
	}
	void release() { RELEASE_PTR(pPlayerManager); }

public:
	PlayerTank* pUserTank;
	int iLife;
	int iScore;
	int iHighScore;
	int iStage;
	int iKill;
	int iWin;

	float fRespawnCurDelay;
	float fRespawnDelay;

	void create(KScene* _GameScene);
	void init();
	void update();
	void update_playerdie();

	void load_highscore();
	void save_highscore();
	void set_highscore();
};

