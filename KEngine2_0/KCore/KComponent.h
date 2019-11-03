#pragma once
#include "PtrOfKWindow.h"
#include "PtrOfKOne.h"
#include "PtrOfKScene.h"

#include "KName.h"
#include "KActor.h"
#include <KType.h>


class KComponent : 
	public PtrOfKWindow,
	public PtrOfKScene,
	public PtrOfKOne,
	public KName,
	public KActor,
	public KType
{
public:
	friend class KOne;


protected:
	KComponent();
	KComponent(const KComponent& _Core) = delete;
	KComponent(const KComponent&& _Core) = delete;
	void operator=(const KComponent& _Core) = delete;
	virtual ~KComponent() {}/* = 0*/;


protected:
	virtual void create() {}
	virtual bool init(){ return false; } /*= 0*/
	virtual void update(){}/*= 0*/
	virtual void out() {}/*= 0*/
	virtual void render_debug () {}
	virtual void release() {}/*= 0*/
};

