#pragma once
#include "PtrOfKWindow.h"
#include "PtrOfKScene.h"
#include "KTransform.h"
#include "KName.h"
#include "KActor.h"


#include <map>
#include <KPathManager.h>


class KState;
class KComponent;
class KOne : 
	public PtrOfKWindow,
	public PtrOfKScene,
	public KName,
	public KActor
{
public:
	friend class KScene;

private:
	KOne();
	KOne(const KOne& _Core) = delete;
	KOne(const KOne&& _Core) = delete;
	void operator=(const KOne& _Core) = delete;
	~KOne()  {};


private:
	std::multimap<std::wstring, KComponent*> MapComponent;
	KTransform* MyTrans;

protected:
	virtual void create();
	virtual bool init();
	virtual void update();
	virtual void render_debug();
	virtual void out();
	virtual void release();


public:
	template <typename T>
	T* get_component()
	{
		std::multimap<std::wstring, KComponent*>::iterator SIter = MapComponent.begin();
		std::multimap<std::wstring, KComponent*>::iterator EIter = MapComponent.end();

		for (; SIter != EIter; ++SIter)
		{
			if (true == SIter->second->is_equal<T>())
			{
				return dynamic_cast<T*>(SIter->second);
			}
		}

		return nullptr;
	}
	
	template <typename Com>
	Com* add_component()
	{
		Com* NewCom = new Com();
		NewCom->kwindow(kwindow());
		NewCom->kscene(kscene());
		NewCom->kone(this);
		NewCom->create();
		NewCom->set_ktypeinfo<Com>();

		MapComponent.insert(std::make_pair(NewCom->sName, NewCom));
		return NewCom;
	}


	void moving_pluspos(const KPos2& _Value);
	void moving_pos(const KPos2& _Value);
	void moving_delta(const KPos2& _Value);


	void pos(const KVec2& _Pos);
	void size(const KSize2& _Size);
	KPos2& pos();
	KPos2& size();
};

