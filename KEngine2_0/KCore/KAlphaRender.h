#pragma once
#include "KRenderer.h"
#include <Windows.h>
#include <vector>

class KBitMap;
class KTransform;
class KAlphaRender : public KRenderer
{
public:
	KAlphaRender();
	~KAlphaRender() override;

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


	BLENDFUNCTION MyBlendFunc;

public:
	void create() override;
	void set_bit(const wchar_t* _Name = L"NONE", const int& _Key = 0);
	void change_bit(const wchar_t* _Name = L"NONE");
	void set_split(const int& _X, const int& _Y);
	void set_idx(const int& _X, const int& _Y);
	void set_idx(const int& _Idx);
	void set_alpha(const BYTE& _Value);

	bool init() override;
	void render() override;
	void render(HDC _Hdc);
};

