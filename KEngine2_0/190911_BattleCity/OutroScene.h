#pragma once
#include <KScene.h>
#include <KVector.h>
#include <vector>


class KOne;
class KTextRender;
class OutroScene : public KScene
{
public:
	OutroScene();
	~OutroScene();

private:
	enum OUTRO_STATE
	{
		CALC,
		WAIT
	};

private:
	std::vector<KOne*> VectorUI;
	std::vector< KTextRender*> ActionText;

	OUTRO_STATE eOState;

	float fOutCurTime;
	float fOutTime;


	float fTankCalcCurTime;
	float fTankCalcTime;


	int iBaseTankScore;
	int iBaseTankCnt;

public:
	void create() override;
	bool init() override;
	void update() override;

private:
	void update_calc();
	void update_wait();
	void update_actiontext();
};

