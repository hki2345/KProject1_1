#pragma once

#include <map>
#include <vector>
#include <KMacro.h>
#include <KCommon.h>
#include <string>
#include "PtrOfKWindow.h"

class KScene;
class KSceneManager :
	public PtrOfKWindow,
	public KSingleton<KSceneManager>
{
public:
	friend class KCore;
	friend class KWindow;

private:
	bool bCurInit;	int retval;

	std::multimap<std::wstring, KScene*> MapScene;
	KScene* CurScene = nullptr;


private:
	void create();

	void init();
	void update();
	void render();
	void release() override;

public:
	void create_iocpsocket();

	void recv_iocpsocket();
	KScene* create_scene(KScene* _Other, const wchar_t* _Name = L"KScene");
	KScene* create_scene(const wchar_t* _Name = L"KScene");
	KScene* find_scene(const wchar_t* _Name);
	bool delete_scene(const wchar_t* _Name);
	bool change_scene(const wchar_t* _Name);
	inline KScene* cur_scene()
	{
		return CurScene;
	}
};

