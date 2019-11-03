#pragma once
#include <string>
#include <map>
#include <KMacro.h>
#include <KCommon.h>
#include "KVector.h"




class KInputManager : public KSingleton<KInputManager>
{
public:
	friend class KCore;


public:
	bool is_down(const int& _Value);
	bool is_press(const int& _Value);
	bool is_up(const int& _Value);
	bool is_unpress(const int& _Value);

	KPos2 pos_mouse();
};

