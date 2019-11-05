#pragma once
#include <map>
#include "KVector.h"



class KRenderer;
class KAPIRenderManager
{
public:
	friend class KScene;

private:
	KAPIRenderManager() {};
	KAPIRenderManager(const KAPIRenderManager& _Core) = delete;
	KAPIRenderManager(const KAPIRenderManager&& _Core) = delete;
	void operator=(const KAPIRenderManager& _Core) = delete;
	~KAPIRenderManager() {};

private:
	void init();
	void update_trans(const KPos2& _CameraPos);
	void render();
	void release();

	void delete_renderer(KRenderer* _Renderer);

	// 같은 레이어별 Z소팅
	void sort_toz(const int& _Key);

private:
	std::multimap<int, KRenderer*> MapKRenderer;

private:
	bool insert_krenderer(KRenderer* _Other, const int& _Key = 0);
};

