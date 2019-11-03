#pragma once
#include "KRenderer.h"
#include <string>
#include <Windows.h>


class KTextRender : public KRenderer
{
public:
	KTextRender();
	~KTextRender();


private:
	int iMySize;
	std::wstring sMyFont;
	DWORD MyColor;
	DWORD MyAlign;
	HFONT myFont;
	HFONT oldFont;

public:
	std::wstring Parse;

public:
	void create() override;
	void set_font(
		const wchar_t* _Text,
		const int& _Size,
		const int& _Key = 0, 
		const wchar_t* _Font = L"±Ã¼­",
		const DWORD& _Color = RGB(255, 255, 255),
		const DWORD& _Align = TA_CENTER);

	void set_text(const wchar_t* _Text);
	void set_color(const DWORD& _Color);
	void render() override;
};

