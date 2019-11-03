#pragma once
#include <KCore.h>

class BattleCityUpdater : public KCore::KCoreUpdater
{
public:
	BattleCityUpdater();
	~BattleCityUpdater();

public:
	void update();
};

