#pragma once
#include <iostream>
#include <vector>

#include <KMacro.h>
#include <KCommon.h>


class KFileStream : public KSingleton<KFileStream>
{
public:
	template<typename T>
	bool write_file(const wchar_t* _Path, const T& _File)
	{
		FILE* TFILE;
		_wfopen_s(&TFILE, _Path, L"w");
		fwrite(&_File, sizeof(_File), 1, TFILE);
		fclose(TFILE);

		return true;
	}

	template<typename T>
	bool read_file(const wchar_t* _Path, T& _File)
	{
		FILE* TFILE;
		_wfopen_s(&TFILE, _Path, L"r");
		fread_s(&_File, sizeof(_File), sizeof(_File), 1, TFILE);
		fclose(TFILE);

		return true;
	}

	template<typename T>
	bool write_file(const wchar_t* _Path, const std::vector<T>& _File)
	{
		FILE* TFILE;
		_wfopen_s(&TFILE, _Path, L"w");
		int Size = (int)_File.size();
		fwrite(&Size, sizeof(Size), 1, TFILE);
		for (int i = 0; i < Size; i++)
		{
			fwrite(&_File[i], sizeof(_File[i]), 1, TFILE);
		}
		fclose(TFILE);

		return true;
	}

	template<typename T>
	bool read_file(const wchar_t* _Path, std::vector<T>& _File)
	{
		_File.clear();
		FILE* TFILE;
		_wfopen_s(&TFILE, _Path, L"r");
		int Size = 0;
		fread_s(&Size, sizeof(Size), sizeof(Size), 1, TFILE);
		for (int i = 0; i < Size; i++)
		{
			T Tmp;
			fread_s(&Tmp, sizeof(Tmp), sizeof(Tmp), 1, TFILE);

			_File.push_back(Tmp);
		}
		fclose(TFILE);

		return true;
	}
};

