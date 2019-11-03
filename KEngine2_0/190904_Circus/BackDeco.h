#pragma once
#include "CircusObject.h"


class ComPlayer;
class KBitMapAnimator;
class BackDeco : public CircusObject
{
public:
	BackDeco();
	~BackDeco();

private:
	bool bActiveDeco;
	KBitMapAnimator* pDecoAnimator;

public:
	bool init() override;
	void update() override;

	inline void set_activedeco()
	{
		bActiveDeco = true;
	}
};

