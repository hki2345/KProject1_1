#include "KResource.h"
#include "KPathManager.h"


KResource::KResource() : sPath(KPathManager::instance()->all_path())
{
}


KResource::~KResource()
{
}



bool KResource::check(const wchar_t* _Name)
{
	// -1 �̰ų� 1�̸� ���ڿ� ���̰� �ٸ� ��
	if (0 == wcscmp(sName.c_str(), _Name))
	{
		return true;
	}
	return false;
}

bool KResource::check(KResource* _Other)
{
	return this == _Other;
}
