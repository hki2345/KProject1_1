#include "KPathManager.h"

#include <Windows.h>
#include <direct.h>
#include <stdlib.h>
#include <iostream>
#include <io.h>
#include <fstream>


#include "KMacro.h"


void KPathManager::init()
{
	wchar_t tmpAllpath[KBUFSIZE] = { 0, };
	wchar_t tmpDrive[KBUFSIZE] = { 0, };
	wchar_t tmpDirectory[KBUFSIZE] = { 0, };
	wchar_t tmpFileName[KBUFSIZE] = { 0, };
	wchar_t tmpExe[KBUFSIZE] = { 0, };

	GetCurrentDirectoryW(KBUFSIZE, tmpAllpath);
	_wsplitpath_s(tmpAllpath, tmpDrive, tmpDirectory, tmpFileName, tmpExe);


	mAllpath = tmpAllpath;
	mDrive = tmpDrive;
	mDirectory = tmpDirectory;
	mFileName = tmpFileName;
	mExtension = tmpExe;
}




void KPathManager::set_path(const char* _Path)
{
	std::wstring Tmp = KPathManager::char_towchar(_Path);

	wchar_t tmpAllpath[KBUFSIZE] = { 0, };
	wchar_t tmpDrive[KBUFSIZE] = { 0, };
	wchar_t tmpDirectory[KBUFSIZE] = { 0, };
	wchar_t tmpFileName[KBUFSIZE] = { 0, };
	wchar_t tmpExe[KBUFSIZE] = { 0, };


	memcpy(tmpAllpath, Tmp.c_str(), sizeof(tmpAllpath));
	_wsplitpath_s(tmpAllpath, tmpDrive, tmpDirectory, tmpFileName, tmpExe);

	mAllpath = tmpAllpath;
	mDrive = tmpDrive;
	mDirectory = tmpDirectory;
	mFileName = tmpFileName;
	mExtension = tmpExe;
}


void KPathManager::release()
{
	mAllpath.clear();
	mDrive.clear();
	mDirectory.clear();
	mFileName.clear();
	mExtension.clear();

	RELEASE_PTR(KSingleton::MyPtr);
}


void KPathManager::char_towchar(wchar_t* _Target, char* _Source)
{
	setlocale(LC_ALL, "");	// 추가됨
	size_t newsize = strlen(_Source) + 1;
	size_t convertedChars = 0;
	mbstowcs_s(&convertedChars, _Target, newsize, _Source, _TRUNCATE);
}

std::wstring KPathManager::char_towchar(const char* _Source)
{
	wchar_t TARGET[KBUFSIZE];

	setlocale(LC_ALL, "");	// 추가됨
	size_t newsize = strlen(_Source) + 1;
	size_t convertedChars = 0;
	mbstowcs_s(&convertedChars, TARGET, newsize, _Source, _TRUNCATE);

	return TARGET;
}



std::string KPathManager::wchar_tochar(const wchar_t* _Source)
{
	std::string  TmpStr;
	char TARGET;
	int Size = sizeof(TARGET);
	rsize_t ReSize = sizeof(_Source[0]);


	for (size_t i = 0; i < wcslen(_Source); i++)
	{
		wctomb_s(&Size, &TARGET, ReSize, _Source[i]);
		TmpStr += TARGET;
	}

	return TmpStr;
}





std::vector<KResourcePath> KPathManager::load_totargetfolder(
	const wchar_t* _Folder, 
	const wchar_t* _Extension)
{
	std::wstring TargetPath = KPathManager::instance()->all_path();
	TargetPath += L'\\';
	TargetPath += _Folder;


	std::wstring FolderPath = _Folder;


	std::vector< KResourcePath> PathVecTmp;


	struct _wfinddata_t FD;
	intptr_t Handle;

	TargetPath += L'\\';
	TargetPath += L"*.*";

	Handle = _wfindfirst(TargetPath.c_str(), &FD);


	while (0 == _wfindnext(Handle, &FD))
	{
		std::wstring Name = FD.name;
		// 폴더 경로를 정확히 정해야 쓸 수 있게 합세 ㅇㅇㅇㅇㅇ
		/*if (-1 == (int)Name.find(L"."))
		{
			FolderPath += L"\\";
			FolderPath += Name;
			continue;
		}*/

		if (-1 != (int)Name.find(_Extension))
		{
			PathVecTmp.push_back(KResourcePath({ FolderPath, Name }));
		}
	}

	_findclose(Handle);

	return PathVecTmp;
}


bool KPathManager::input_wchar(wchar_t* _Target, const int& _Target_sizeof, const wchar_t* _Path)
{
	memset(_Target, 0, _Target_sizeof);

	int MaxIdx = (int)(_Target_sizeof * .5f) - 1;
	int idx = (int)wcslen(_Path);

	if (MaxIdx > idx)
	{
		for (int i = 0; i < idx; ++i)
		{
			_Target[i] = _Path[i];
		}
	}
	else
	{
		for (int i = 0; i < MaxIdx; ++i)
		{
			_Target[i] = _Path[i];
		}
	}

	return true;
}


std::vector<std::vector<std::string>> KPathManager::loadcsv_tocharvec(const char* _Path)
{
	std::vector<std::vector<std::string>> ReturnVec;

	std::vector<std::string> Tmp;
	char Arr[KPATHBUFSIZE];

	std::fstream ifs(_Path, std::ios::in | std::ios::binary);
	std::locale loc("KOR");
	ifs.imbue(loc);

	while (!ifs.eof())
	{
		ifs.getline(Arr, KPATHBUFSIZE);
		Tmp.push_back(Arr);
	}

	ifs.close();


	std::vector<std::string> TTmp;
	for (size_t i = 1; i < Tmp.size() - 1; i++)
	{
		std::string PlusTmp;
		for (size_t j = 0; j < Tmp[i].size() - 1; j++)
		{
			if (',' == Tmp[i][j])
			{
				TTmp.push_back(PlusTmp);
				PlusTmp.clear();
			}
			else
			{
				PlusTmp += Tmp[i][j];
			}
		}
		TTmp.push_back(PlusTmp);

		ReturnVec.push_back(TTmp);
		TTmp.clear();
	}

	return ReturnVec;
}

std::string KPathManager::char_tosha1(const char* _Path)
{
	SHA1 checksum;
	checksum.update(_Path);
	return checksum.final();
}