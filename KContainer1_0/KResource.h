#pragma once
#include <string>
#include "KType.h"

class KResource : public KType
{
protected:
	KResource();
	KResource(const KResource& _Other) = delete;
	KResource(const KResource&& _Other) = delete;
	void operator=(const KResource& _Other) = delete;
	virtual ~KResource() = 0;

public:
	std::wstring sPath;

	std::wstring sName;
	std::wstring sFolder;
	std::wstring sExtension;

protected:
	virtual bool load() = 0;
	virtual bool save() = 0;

public:
	bool check(const wchar_t* _Name);
	bool check(KResource* _Other);
};

