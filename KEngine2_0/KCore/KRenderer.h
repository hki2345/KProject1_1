#pragma once
#include "KComponent.h"
#include "KVector.h"

// 이번 버전 새로운 "이시에이터" 시스템
// "이시니에이터"를 따로 만들어 클라나 에딧에서
// 그 이니시에이터를 상속받아 [발진] 시키도록 한다.
// 이 이니시에이터는 엔진 단계 발진뿐만 아니라 씬, 오브젝트 등 모든 곳에 쓰인다.
// 단 메니저 같이 싱글톤으로 될 녀석들은 못씀ㅇㅇ - 인터페이스를 같게하는 걸로 만족
class KTransform;
class KRenderer : public KComponent
{
protected:
	KRenderer();
	KRenderer(const KRenderer& _Core) = delete;
	KRenderer(const KRenderer&& _Core) = delete;
	void operator=(const KRenderer& _Core) = delete;
	virtual ~KRenderer() = 0;



protected:
	bool bHold;
	bool bRender;

	KTransform* MyTrans;
	KPos2 MyPivot;
	KPos2 RenderPos;
	KSize2 RenderSize;

public:
	float ZSort;

public:
	virtual bool init() override { return true; };
	virtual void create() override;
	virtual void update() override {};

	virtual void update_trans(const KPos2& _CameraPos);
	virtual void render() = 0;
	virtual void release() override;

	void set_hold()
	{
		bHold = true;
	}
	inline virtual void render_size(const KSize2& _RenderSize)
	{
		RenderSize = _RenderSize;
	}

	inline KSize2& render_size()
	{
		return RenderSize;
	}

	inline virtual void pivot(const KPos2& _Pivot)
	{
		MyPivot = _Pivot;
	}
};

