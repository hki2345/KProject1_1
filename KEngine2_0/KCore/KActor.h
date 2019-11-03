#pragma once
#include "KName.h"


class KActor
{
public:
	friend class KScene;
	friend class KOne;

protected:
	KActor();
	KActor(const KActor& _Core) = delete;
	KActor(const KActor&& _Core) = delete;
	void operator=(const KActor& _Core) = delete;
	virtual ~KActor() = 0;

private:
	bool bActing;
	bool bDeath;
	bool bNextActing;

public:	
	inline bool active_frame()
	{
		return bActing & bNextActing;
	}

	inline virtual void active_frame(const bool& _Value)
	{
		bNextActing = _Value;
	}

	inline bool& death()
	{
		return bDeath;
	}
	inline void death(const bool& _Value)
	{
		bDeath = _Value;
	}
};

