#include "KTextRender.h"
#include "KScene.h"
#include "KWindow.h"
#include "KOne.h"


KTextRender::KTextRender() :
	iMySize(0),
	sMyFont(L""),
	MyColor(RGB(0,0,0)),
	MyAlign(TA_CENTER),
	myFont(nullptr),
	oldFont(nullptr)
{
}


KTextRender::~KTextRender()
{
}


void KTextRender::create()
{
	KRenderer::create();
	sName = L"KTextRender";
}

void KTextRender::set_font(
	const wchar_t* _Text,
	const int& _Size,
	const int& _Key/* = 0*/,
	const wchar_t* _Font/* = L"±Ã¼­"*/,
	const DWORD& _Color /*= RGB(255, 255, 255)*/,
	const DWORD& _Align /*TA_CENTER*/)
{
	iMySize = _Size;
	MyColor = _Color;
	Parse = _Text;
	sMyFont = _Font;
	MyAlign = _Align;
	kscene()->insert_krender(this, _Key);
}

void KTextRender::set_text(const wchar_t* _Text)
{
	Parse = _Text;
}


void KTextRender::set_color(const DWORD& _Color)
{
	MyColor = _Color;
}

void KTextRender::render()
{
	if (false == bRender)
	{
		return;
	}

	myFont = CreateFont(iMySize, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, sMyFont.c_str());
	oldFont = (HFONT)SelectObject(kwindow()->bhdc(), myFont);
	SetTextColor(kwindow()->bhdc(), MyColor);
	SetBkMode(kwindow()->bhdc(), TRANSPARENT);
	SetTextAlign(kwindow()->bhdc(), MyAlign);

	TextOutW(kwindow()->bhdc(), (int)RenderPos.x, (int)RenderPos.y, Parse.c_str(), (int)Parse.size());

	SelectObject(kwindow()->bhdc(), oldFont);
	DeleteObject(myFont);
}