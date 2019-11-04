#pragma once
#include <map>
#include <set>
#include <vector>
#include <string>


#include "KMacro.h"
#include "KPathManager.h"
#include "KResource.h"


#include <Windows.h>
//
//vector<T>::iterator i; // bad, vector<T>::iterator might not be a type
//	// depending on what 'T' is.  For example, there might be a specialization
//	// where iterator is defined as a member var instead of a type.
//
//typename vector<T>::iterator i;  // OK


template <class ResT>
class KResourceManager : public KSingleton<KResourceManager<ResT>>
{
private:
	std::map<std::wstring, ResT*> MapRes;
	std::set<std::wstring> SetFont;


private:
	void set_font()
	{
		std::set<std::wstring>::iterator SIter = SetFont.begin();
		std::set<std::wstring>::iterator EIter = SetFont.end();

		for (; SIter != EIter; SIter++)
		{
			AddFontResourceW((*SIter).c_str());
		}
	}

	void release_font()
	{
		std::set<std::wstring>::iterator SIter = SetFont.begin();
		std::set<std::wstring>::iterator EIter = SetFont.end();

		for (; SIter != EIter; SIter++)
		{
			RemoveFontResourceW((*SIter).c_str());
		}

		SetFont.clear();
	}

public:
	void init() {}
	void release() override
	{
		typename std::map<std::wstring, ResT*>::iterator SIter = MapRes.begin();
		typename std::map<std::wstring, ResT*>::iterator EIter = MapRes.end();

		for (; SIter != EIter; ++SIter)
		{
			RELEASE_PTR(SIter->second);
		}

		MapRes.clear();
		release_font();
		RELEASE_PTR(KSingleton<KResourceManager<ResT>>::MyPtr);
	}



	ResT* find(const wchar_t* _Name)
	{
		typename std::map<std::wstring, ResT*>::iterator FIter = MapRes.find(_Name);

		if (MapRes.end() != FIter)
		{
			return FIter->second;
		}

		return nullptr;
	}

	ResT* load(const wchar_t* _Folder, const wchar_t* _Name)
	{
		ResT* NewRes = new ResT();
		NewRes->sFolder = _Folder;
		NewRes->sName = _Name;
		NewRes->set_ktypeinfo<ResT>();

		if (0 == strcmp("class KSound", NewRes->ktypename().c_str())) // -> 클래스명으로 확장자 결정
		{
			NewRes->sExtension = L".wav";
		}
		else if (0 == strcmp("class KBitMap", NewRes->ktypename().c_str())) // -> 클래스명으로 확장자 결정
		{
			NewRes->sExtension = L".bmp";
		}

		NewRes->sPath += L"\\";
		NewRes->sPath += NewRes->sFolder;
		NewRes->sPath += L"\\";
		NewRes->sPath += NewRes->sName;
		// NewRes->sFile += NewRes->sExtension;

		NewRes->load();

		std::wstring KeyStr;
		KeyStr += NewRes->sFolder;
		KeyStr += L"\\";
		KeyStr += NewRes->sName;
		// KeyStr += NewRes->sExtension;

		MapRes.insert(std::make_pair(KeyStr, NewRes));
		return NewRes;
	}

	bool erase(const wchar_t* _Name)
	{
		typename std::map<std::wstring, ResT*>::iterator FIter = MapRes.find(_Name);

		if (MapRes.end() != FIter)
		{
			delete FIter->second;
			MapRes.erase(FIter);
			return true;
		}

		return false;
	}

	bool save(const wchar_t* _Name)
	{
		typename std::map<std::wstring, ResT*>::iterator FIter = MapRes.find(_Name);

		if (MapRes.end() != FIter)
		{
			return FIter->save();
		}

		return true;
	}

	// 확장자 추론 자동에 해당 폴더를 다 긁어오신다.
	std::vector<KResourcePath> load_forder(const wchar_t* _Target)
	{
		std::wstring Extension;
		const char* ComTmp = typeid(ResT).name(); // -> 클래스명 판독코드

		if (0 == strcmp("class KSound", ComTmp)) // -> 클래스명으로 확장자 결정
		{
			Extension = L".wav";
		}
		else if (0 == strcmp("class KBitMap", ComTmp)) // -> 클래스명으로 확장자 결정
		{
			Extension = L".bmp";
		}

		std::vector<KResourcePath> PathVec =
			KPathManager::instance()->load_totargetfolder(_Target, Extension.c_str());

		for (size_t i = 0; i < PathVec.size(); i++)
		{
			load(PathVec[i].sFolder.c_str(), PathVec[i].sFile.c_str());
		}

		return PathVec;
	}

	void add_font(const wchar_t* _Font)
	{
		SetFont.insert(_Font);
		set_font();
	}
};