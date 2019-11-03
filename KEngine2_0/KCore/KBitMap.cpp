#include "KBitMap.h"
#include "KWindowManager.h"

#include <KPathManager.h>


KBitMap::KBitMap() :
	MyDC(nullptr),
	MyBitMap(nullptr),
	OldBitmap(nullptr),
	BitMapData(BITMAP())
{
}


KBitMap::~KBitMap()
{
	DeleteDC(MyDC);
	DeleteObject(OldBitmap);
}




bool KBitMap::load()
{	
	MyDC = CreateCompatibleDC(KWindowManager::instance()->main_hdc());
	
	if (0 != wcscmp(KResource::sFolder.c_str(), L"KCore"))
	{
		MyBitMap = (HBITMAP)LoadImage(NULL, KResource::sPath.c_str(), IMAGE_BITMAP
			, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
		OldBitmap = (HBITMAP)SelectObject(MyDC, MyBitMap);
		GetObjectW(MyBitMap, sizeof(BITMAP), &BitMapData);
	}

	return true;
}

HDC& KBitMap::kwindow_size(const KSize2& _Size)
{
	MyBitMap = CreateCompatibleBitmap(KWindowManager::instance()->main_hdc(), (int)_Size.x, (int)_Size.y);
	OldBitmap = (HBITMAP)SelectObject(MyDC, MyBitMap);
	GetObjectW(MyBitMap, sizeof(BITMAP), &BitMapData);

	return MyDC;
}

bool KBitMap::save()
{
	return true;
}

KPos2 KBitMap::size()
{
	return KPos2((float)BitMapData.bmWidth, (float)BitMapData.bmHeight);
}