#include "TestInitiator.h"

#include <KWindowManager.h>
#include <KSceneManager.h>
#include <KResourceManager.h>
#include <KBitMap.h>

#include "Test1Scene.h"



TestInitiator::TestInitiator()
{
}


TestInitiator::~TestInitiator()
{
}


void TestInitiator::init()
{
	KResourceManager<KBitMap>::instance()->load_forder(L"res");
	KResourceManager<TestInitiator>::instance()->add_font(L"res\\FontPackgeWindow\\12롯데마트행복Bold.ttf");
	KWindowManager::instance()->backcolor(RGB(247, 165, 40));


	Test1Scene* NewLogin = new Test1Scene();
	KSceneManager::instance()->create_scene(NewLogin, L"Test1");

	KSceneManager::instance()->change_scene(L"Test1");
}