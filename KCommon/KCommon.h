#pragma once
#include "KMacro.h"


#define CPUCOUNT 4


template<class PTR>
class KSingleton
{
protected:
	KSingleton() {}
	KSingleton(const KSingleton& _Other) = delete;
	KSingleton(const KSingleton&& _Other) = delete;
	void operator=(const KSingleton& _Other) = delete;
	virtual ~KSingleton() {}

protected:
	static PTR* MyPtr;


public:
	static PTR* instance()
	{
		if (nullptr == MyPtr)
		{
			MyPtr = new PTR;
		}

		return MyPtr;
	}

	virtual void release()
	{
		RELEASE_PTR(MyPtr);
	}
};

template <class PTR>
PTR* KSingleton<PTR>::MyPtr = nullptr;