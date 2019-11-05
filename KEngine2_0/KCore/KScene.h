#pragma once
#include "PtrOfKWindow.h"
#include "KName.h"
#include "KActor.h"
#include "KVector.h"
#include <map>

#include <mutex>


class KOne;
class KAPIRenderManager;
class K2DColliderManager;
class KRenderer;
class K2DCollider;
class KScene : 
	public PtrOfKWindow,
	public KName,
	public KActor
{
public:
	friend class KSceneManager;

protected:
	KScene();
	KScene(const KScene& _Core) = delete;
	KScene(const KScene&& _Core) = delete;
	void operator=(const KScene& _Core) = delete;
	virtual ~KScene() {}/* = 0*/;

public:
	KPos2 SceneCamPos;
	KPos2 outof_screen(KOne* _Target);


protected:
	KAPIRenderManager* curAPIKRenderMgr;
	K2DColliderManager* curK2DColliderMgr;

	std::multimap<std::wstring, KOne*> MapKOne;
	std::mutex MyMutex;
	
public:
	bool insert_krender(KRenderer* _Render, const int& _Key = 0);
	bool insert_k2dCollider(K2DCollider* _Collider, const int& _Key = 0);


	void link_k2dCollider(const int& _Key1, const int& _Key2);
	void passlink_k2dCollider(const int& _Key1, const int& _Key2);

	void clearpasslink();

protected:
	virtual void create();
	virtual bool init() ;
	virtual void update() ;
	virtual void out();
	virtual void release();
	virtual void render_api();
	virtual void render_dx();
	virtual bool process_packet(char* szBuf, int len) { return true; };

	void render_debug();

public:

	KOne* create_kone(const wchar_t* _Name = L"KOne");
	KOne* create_kone(KOne* _Other, const wchar_t* _Name = L"KOne");


	KOne* find_kone(const wchar_t* _Name);
	bool delete_kone(const wchar_t* _Name);
	bool delete_kone(KOne* _Other);

	bool delete_krenderer(KRenderer* _Renderer);
	bool delete_k2dcollider(K2DCollider* _Collider);

	void sort_toz(const int& _Key);
};

