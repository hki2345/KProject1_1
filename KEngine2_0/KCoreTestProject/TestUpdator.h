#pragma once
#include <KCore.h>

class TestUpdator : public KCore::KCoreUpdater
{
public:
	TestUpdator();
	~TestUpdator();

public:
	void update() override;
};

