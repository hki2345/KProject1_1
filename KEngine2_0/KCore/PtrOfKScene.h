#pragma once


class KScene;
class PtrOfKScene
{
protected:
	PtrOfKScene() : pKScene(nullptr) {};
	PtrOfKScene(const PtrOfKScene& _Core) = delete;
	PtrOfKScene(const PtrOfKScene&& _Core) = delete;
	void operator=(const PtrOfKScene& _Core) = delete;
	~PtrOfKScene() {};



private:
	KScene* pKScene;

public:
	inline KScene* kscene()
	{
		return pKScene;
	}

	inline void kscene(KScene* _One)
	{
		pKScene = _One;
	}

};

