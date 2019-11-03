#include "KRenderer.h"
#include "KWindow.h"

#include "KScene.h"

#include "KTransform.h"
#include "KOne.h"



KRenderer::KRenderer() :
	MyPivot(KPos2::Zero),
	bHold (false),
	bRender (false),
	MyTrans(nullptr),
	ZSort(.0f)
{

}

KRenderer::~KRenderer()
{

}


void KRenderer::create()
{
	if (nullptr ==MyTrans)
	{
		MyTrans = kone()->get_component<KTransform>();
		RenderSize = MyTrans->Size;
	}

	ZSort = .0f;
}


void KRenderer::update_trans(const KPos2& _CameraPos)
{
	if (false == bHold)
	{
		if (_CameraPos.x > MyTrans->Pos.x + MyTrans->Size.x)
		{
			bRender = false;
		}
		else if (_CameraPos.x < (MyTrans->Pos.x) - kwindow()->size().x)
		{
			bRender = false;
		}
		else
		{
			bRender = true;
		}

		RenderPos = MyTrans->Pos - _CameraPos + MyPivot;
	}
	else if (true == bHold)
	{
		bRender = true;
		RenderPos = MyTrans->Pos + MyPivot;
	}
}


void KRenderer::release()
{
	kscene()->delete_krenderer(this);
}