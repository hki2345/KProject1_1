#pragma once
#include <KScene.h>
#include <vector>

class KOne;
class KTextRender;
class BattleScene : public KScene
{
public:
	BattleScene();
	~BattleScene();

private:
	enum GAMESCENE_STATE
	{
		GSS_START,
		GSS_WAIT,
		GSS_PLAY,
		GSS_OVER,
	};

private:
	std::vector<KOne*> CoverUI;
	std::vector<KOne*> EnemyUI;
	std::vector<KOne*> GameUI;
	std::vector<KOne*> GameTextUI;
	std::vector<KOne*> OverTextUI;
	GAMESCENE_STATE eGSState;

	KTextRender* pLifeUI;
	KTextRender* pStageUI;

	float fStartUICurTime;
	float fStartUITime;

	float fOverUICurTime;
	float fOverUITime;


public:
	void create() override;
	void stage_start();
	bool init() override;
	void render() override;
	void update() override;
	void release() override;

	void update_playUI();

private:
	void create_startUI();
	void create_gameUI();
	void create_overUI();

	void update_start();
	void update_wait();
	void update_play();
	void update_over();

	void active_vector(const std::vector<KOne*>& _Vector, const bool& _Value);
	void change_scene();
};

