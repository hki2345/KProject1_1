#include "Test1Scene.h"

#include <KOne.h>
#include <KAlphaRender.h>



Test1Scene::Test1Scene()
{
}


Test1Scene::~Test1Scene()
{
}

void Test1Scene::create()
{
	KScene::create();
	KOne* NewOne = create_kone();
	NewOne->size({ 300, 300 });
	TRender = NewOne->add_component<KAlphaRender>();
	TRender->set_bit(L"res\\TestImg.bmp");
	TRender->set_split(1, 1);
	TRender->set_idx(0);
}
bool Test1Scene::init()
{
	KScene::init();
	return true;
}
void Test1Scene::update()
{

	KScene::update();
}