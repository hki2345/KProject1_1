#pragma once
#include <KComponent.h>
#include <KVector.h>


class ComPlayer;
class CircusObject : public KComponent
{
public:
	CircusObject();
	~CircusObject();

protected:
	KPos2 MyOriginPos;
	ComPlayer* pPlayer;
	float fBaseSpeed;
	float fObsSpeed;
	float fColHeight;


public:
	inline void set_player(ComPlayer* _Other)
	{
		pPlayer = _Other;
	}

	virtual void create() override;
	virtual bool init() override;
};

