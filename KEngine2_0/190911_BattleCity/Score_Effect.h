#pragma once
#include <KComponent.h>
#include <KVector.h>


class KTextRender;
class Score_Effect : public KComponent
{
public:
	Score_Effect();
	~Score_Effect();




private:
	KOne* MyTarget;
	KTextRender* MyRender;

	float fFloatingCurTime;
	float fFloatingTime;

public:
	void create() override;
	void set_score(const KPos2& _Pos, const int& _Score);

	void update() override;
};

