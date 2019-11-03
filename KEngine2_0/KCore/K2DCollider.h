#pragma once
#include "KComponent.h"
#include "KVector.h"

#include <string>
#include <list>

#include <functional>



class KTransform;
class KOne;
class K2DCollider : public KComponent
{
public:
	friend class K2DColliderManager;

public:
	K2DCollider();
	~K2DCollider();

protected:
	enum COL_FIGURE
	{
		COL2D_RECT = 0,
		COL2D_CIRCLE,
		COL2D_POINT,
	};


protected:
	COL_FIGURE MyFigure;

	KTransform* MyTrans;
	KPos2 MyPivot;
	KRect MyColliderRect;

	KPos2 PrevPos;
	KPos2 DeltaDistance;
	KRect DeltaBox;


private:
	std::list<K2DCollider*> ListCollision;

	std::list<std::function<void(KOne*)>> ListEnterFunc;
	std::list<std::function<void(KOne*)>> ListStayFunc;
	std::list<std::function<void(KOne*)>> ListExitFunc;

protected:
	void create() override;
	bool init() override { return true; };
	void update() override;
	void release() override;

private:
	void checking_deltabox();
	void update_collision(K2DCollider* _Other);

	void update_enterorstay(K2DCollider* _Other);
	void update_exit(K2DCollider* _Other);

	void update_enterfunc(KOne* _Other);
	void update_stayfunc(KOne* _Other);
	void update_exitfunc(KOne* _Other);

	void udpate_list(std::list<std::function<void(KOne*)>>& _List, KOne* _Other);

	std::list<K2DCollider*>::iterator find_listcol(K2DCollider* _Other);

public:

	// 아오 써글...
	// 일당 ㅍ어셔널 사용법
	// https://en.cppreference.com/w/cpp/utility/functional/function
	template<typename T>
	void insert_enterfunc(T* _This, void(T::*_Func)(KOne*))
	{
		// 함수 포인터, 객체 -이게 사실 멤버라 디스 객체를 넣어줌
		// 마지막으로 인자 수
		ListEnterFunc.push_back(std::bind(_Func, _This, std::placeholders::_1));

		// 호출은 this, &클래스 명::함수이름 식으로 호출
		// 실상은 직접 클래스 호출하는 형태
	}

	template<typename T>
	void insert_stayfunc(T* _This, void(T::*_Func)(KOne*))
	{
		ListStayFunc.push_back(std::bind(_Func, _This, std::placeholders::_1));
	}
	template<typename T>
	void insert_exitfunc(T* _This, void(T::*_Func)(KOne*))
	{
		ListExitFunc.push_back(std::bind(_Func, _This, std::placeholders::_1));
	}

public:
	inline KRect& rect_collision()
	{
		return MyColliderRect;
	}

	inline void pivot(const KPos2& _Pivot)
	{
		MyPivot = _Pivot;
	}
};