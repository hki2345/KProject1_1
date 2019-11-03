#pragma once
#include <string>
#include <set>
#include <KCommon.h>
#include <Windows.h>


class KUnityParse : public KSingleton<KUnityParse>
{
private:
	std::multiset<std::wstring> MapCpp;
	std::wstring sTarget; 
	HWND hWnd;

public:
	void init();


private:
	void init_window();

	void load_cpp(const bool& _Core);
	void load_path(const wchar_t* _Path);
	void save_cpp(const bool& _Core);
	void save_path(const bool& _Core);
};

