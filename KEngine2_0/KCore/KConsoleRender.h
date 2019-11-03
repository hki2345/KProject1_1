#pragma once
#include "KRenderer.h"
#include "KComponent.h"



class KConsoleRender :  public KRenderer
{
public:
	KConsoleRender();
	~KConsoleRender() override;

public:
	void create() override;
	bool init() override;
	void render() override;
};