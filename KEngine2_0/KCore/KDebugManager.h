#pragma once
#include <vector>
#include <string>

#include <KCommon.h>


class KDebugManager : public KSingleton<KDebugManager>
{
public:
	friend class KCore;
	friend class KScene;
private:
	bool bDebugAll;
	bool bDebugFigure;
	std::vector<std::wstring> VectorLog;


public:
	void insert_log(const wchar_t* const _Str, ...);



private:
	void init();
	void update();
	void render();
	void release() override;
};