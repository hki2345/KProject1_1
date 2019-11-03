#pragma once



class PtrOf_Component
{
public:
	PtrOf_Component() {};
	PtrOf_Component(const PtrOf_Component& _Core) = delete;
	PtrOf_Component(const PtrOf_Component&& _Core) = delete;
	void operator=(const PtrOf_Component& _Core) = delete;
	~PtrOf_Component() {};


};

