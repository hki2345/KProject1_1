#pragma once
#include "KComponent.h"
#include "KVector.h"

// �̹� ���� ���ο� "�̽ÿ�����" �ý���
// "�̽ôϿ�����"�� ���� ����� Ŭ�� ��������
// �� �̴Ͻÿ����͸� ��ӹ޾� [����] ��Ű���� �Ѵ�.
// �� �̴Ͻÿ����ʹ� ���� �ܰ� �����Ӹ� �ƴ϶� ��, ������Ʈ �� ��� ���� ���δ�.
// �� �޴��� ���� �̱������� �� �༮���� �������� - �������̽��� �����ϴ� �ɷ� ����
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

