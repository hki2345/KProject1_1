#pragma once
#include "KRenderer.h"

#include <map>
#include <string>
#include <Windows.h>

class KSpriteRender;
class KSpriteAnimator : public KRenderer
{
public:
	KSpriteAnimator();
	~KSpriteAnimator();

private:
	class Clip
	{
	public:
		Clip() :
			fSpeed(.0f), 
			fAniTime(.0f),
			iAniIdx(0),
			Start(0),
			End(0){};
		~Clip() {};

	public:
		float fSpeed;
		float fAniTime;
		int iAniIdx;
		int Start;
		int End;
	};


private:
	KSpriteRender* pSprite;
	std::map<std::wstring, Clip> MapClip;
	std::map<std::wstring, Clip>::iterator CurClip;

public:
	void z_sort(const float& _Key);
	void create() override;
	bool init() override;
	void update() override;
	void render() override;

	void render_size(const KSize2& _RenderSize) override;
	void pivot(const KSize2& _RenderSize) override;

public:
	void insert_animation(
		const wchar_t* _AniName,
		const int& _Start,
		const int& _End,
		const float& _Speed = 0.1f // 초당 약 10장
	);
	void change_animation(const wchar_t* _AniName);

	void set_bit(const wchar_t* _Name = L"NONE", const int& _Key = 0);
	void change_bit(const wchar_t* _Name = L"NONE");
	void set_split(const int& _X, const int& _Y);
	void reset_animate();
	void render(HDC _Hdc);

	bool isover_animate();

	void active_frame(const bool& _Value);
};

