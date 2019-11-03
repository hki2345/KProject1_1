#pragma once
#include "KComponent.h"
#include "KVector.h"



class KTransform : public KComponent
{
public:
	KTransform();
	~KTransform();

public:
	void create() override;
	bool init() override;
	void update() override;
	void release() override;


public:
	KVec2	Pos;
	KSize2	Size;
	
public:
	void moving_pluspos(const KVec2& _Speed);
	void moving_pos(const KVec2& _Speed);
	void moving_delta(const KVec2& _Speed);
};

