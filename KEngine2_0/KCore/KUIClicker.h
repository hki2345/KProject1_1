#pragma once
#include "KComponent.h"

class KRenderer;
class KTransform;
class KUIClicker : public KComponent
{
public:
	KUIClicker();
	~KUIClicker();

private:
	KTransform* MyTrans;
	bool bIsClicked;

public:
	int Id;

public:
	void create() override;
	void update() override;

	inline bool& is_clicked()
	{
		return bIsClicked;
	};
};

