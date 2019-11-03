#pragma once
#include "KRenderer.h"
#include <Windows.h>
#include <vector>

class KBitMap;
class KTransform;
class KSpriteRender : public KRenderer
{
public:
	KSpriteRender();
	~KSpriteRender();

private:
	struct KSplit
	{
		KPos2 Pos;
		KPos2 Size;
	};

private:
	KBitMap* MyBitMap;
	std::vector<KSplit> VectorMySplit;
	int SplitX;
	int SplitY;
	int idx;

public:
	void create() override;
	void set_bit(const wchar_t* _Name = L"NONE", const int& _Key = 0);
	void change_bit(const wchar_t* _Name = L"NONE");
	void set_split(const int& _X, const int& _Y);
	void set_idx(const int& _X, const int& _Y);
	void set_idx(const int& _Idx);
	KSize2& set_bitsize();

	bool init() override;
	void render() override;
	void render(HDC _Hdc);
};

