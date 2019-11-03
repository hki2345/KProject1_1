#include "KRectCollision.h"
#include "KTransform.h"
#include "KScene.h"
#include "KWindow.h"




KRectCollision::KRectCollision()
{
}


KRectCollision::~KRectCollision()
{
}


void KRectCollision::create()
{
	K2DCollider::create();
	K2DCollider::MyFigure = K2DCollider::COL_FIGURE::COL2D_RECT;
	MyColor = RGB(125, 125, 255);
	sName = L"KRectCollision";
}

void KRectCollision::set_rect(const int& _Key)
{
	kscene()->insert_k2dCollider(this, _Key);
}

void KRectCollision::update()
{
	K2DCollider::update();
	ColRect.Start = MyTrans->Pos;
	ColRect.End = MyTrans->Pos + MyTrans->Size;
}

void KRectCollision::render_debug()
{
	HPEN MyPen = CreatePen(PS_SOLID, 5, MyColor);
	HPEN OldPen = (HPEN)SelectObject(kwindow()->bhdc(), MyPen);

	HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH oldBrush = (HBRUSH)SelectObject(kwindow()->bhdc(), myBrush);


	Rectangle(kwindow()->bhdc(), 
		(int)ColRect.Start.x + (int)MyPivot.x, 
		(int)ColRect.Start.y + (int)MyPivot.y,
		(int)ColRect.End.x + (int)MyPivot.x,
		(int)ColRect.End.y + (int)MyPivot.y);

	SelectObject(kwindow()->bhdc(), OldPen);
	SelectObject(kwindow()->bhdc(), oldBrush);
	DeleteObject(MyPen);
	DeleteObject(myBrush);
}