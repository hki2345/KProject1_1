#pragma once
#include <KCore.h>

class KEngineUpdater   : public KCore::KCoreUpdater
{
public:
	KEngineUpdater();
	~KEngineUpdater();

public:
	void update() override;
};

 