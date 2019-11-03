#pragma once
#include "CircusObject.h"


class Obstcle : public CircusObject
{
public:
	Obstcle();
	~Obstcle();

public:
	enum OBSTACLE_TYPE
	{
		OT_FIRE = 0,
		OT_ITEMFIRE,
		OT_POT,
		OT_WINPAN,
	};

private:
	KPos2 MyOriginPos;
	OBSTACLE_TYPE eObType;
	bool bFast;
	bool bCollider;

public:
	void set_prop(const OBSTACLE_TYPE& _Type, const bool& _Fast);

	bool init() override;
	void update() override;

private:
	void update_fire();
	void update_pot();

	void update_colide();

	bool collide_sub(const float& _YPos1, const float& _YPos2);
};

