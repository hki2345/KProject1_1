#pragma once
#include "CircusObject.h"

class KBitMapRender;
class Miter : public CircusObject
{
public:
	Miter();
	~Miter();

private:
	KBitMapRender* pBitRender;

public:
	bool init() override;
	void update() override {};
};

