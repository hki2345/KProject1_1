#pragma once
#include <KScene.h>


class KAlphaRender;
class Test1Scene : public KScene
{
public:
	Test1Scene();
	~Test1Scene();


private:
	KAlphaRender* TRender;

public:
	void create() override;
	bool init() override;
	void update() override;
};

