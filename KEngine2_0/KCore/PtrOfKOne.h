#pragma once


class KOne;
class PtrOfKOne
{
protected:
	PtrOfKOne() : pKOne(nullptr) {};
	PtrOfKOne(const PtrOfKOne& _Core) = delete;
	PtrOfKOne(const PtrOfKOne&& _Core) = delete;
	void operator=(const PtrOfKOne& _Core) = delete;
	~PtrOfKOne() {};

public:
	KOne* pKOne;

public:
	inline KOne* kone()
	{
		return pKOne;
	}

	inline void kone(KOne* _One)
	{
		pKOne = _One;
	}
};

