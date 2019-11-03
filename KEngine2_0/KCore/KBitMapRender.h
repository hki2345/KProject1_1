#pragma once
#include "KRenderer.h"
#include <Windows.h>

class KBitMap;
class KTransform;
class KBitMapRender : public KRenderer
{
public:
	KBitMapRender();
	~KBitMapRender();


private:
	bool MyBitState;
	KBitMap* MyBitMap;

public:
	void create() override;
	void set_bit(const wchar_t* _Name = L"NONE", const int& _Key = 0, const bool& _bBitRender = false);
	KSize2& set_bitsize();
	void set_trans(const bool& _Type);
	void change_bit(const wchar_t* _Name = L"NONE", const bool& _bBitRender = false);

	bool init() override;
	void render() override;
	void render(HDC _Hdc);
};

