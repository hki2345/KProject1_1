#pragma once
#include <vector>
#include <string>
#include <KCommon.h>


struct KResourcePath
{
	std::wstring sFolder;
	std::wstring sFile;
};

class KPathManager : public KSingleton<KPathManager>
{
public:
	friend class KCore;
	friend class KUnityParse;


private:
	// 암호화 코드 - http://www.zedwood.com/article/cpp-sha1-function
	class SHA1
	{
	public:
		friend class KPathManager;

	public:
		SHA1();
	private:
		typedef unsigned long int uint32;   /* just needs to be at least 32bit */
		typedef unsigned long long uint64;  /* just needs to be at least 64bit */

		static const unsigned int DIGEST_INTS = 5;  /* number of 32bit integers per SHA1 digest */
		static const unsigned int BLOCK_INTS = 16;  /* number of 32bit integers per SHA1 block */
		static const unsigned int BLOCK_BYTES = BLOCK_INTS * 4;

		uint32 digest[DIGEST_INTS];
		std::string buffer;
		uint64 transforms;

	private:
		void update(const std::string &s);
		void update(std::istream &is);

		std::string final();
		void reset();
		void transform(uint32 block[BLOCK_BYTES]);

		static void buffer_to_block(const std::string &buffer, uint32 block[BLOCK_BYTES]);
		static void read(std::istream &is, std::string &s, int max);
	};


private:
	std::wstring mAllpath;
	std::wstring mDrive;
	std::wstring mDirectory;
	std::wstring mFileName;
	std::wstring mExtension;

	// 에디터 때메 일단 열어놈
public:
	void init();
	void release() override;

public:
	void set_path(const char* _Path);

	inline std::wstring& all_path()
	{
		return mAllpath;
	}
	inline std::wstring& drive()
	{
		return mDrive;
	}
	inline std::wstring& directory()
	{
		return mDirectory;
	}
	inline std::wstring& file_name()
	{
		return mFileName;
	}
	inline std::wstring& exe()
	{
		return mExtension;
	}


	template<typename T> 
	std::wstring bind_wcharnum(const wchar_t* _Path, const T& _Target_sizeof)
	{
		std::wstring Tmp;
		Tmp = _Path;
		Tmp += std::to_wstring<T>(_Target_sizeof);
		return Tmp;
	}


public:
	std::vector<KResourcePath> load_totargetfolder(const wchar_t* _Folder, const wchar_t* _Extension);
	bool input_wchar(wchar_t* _Target, const int& _Target_sizeof, const wchar_t* _Path);
	void char_towchar(wchar_t* _Target, char* _Source);
	std::wstring char_towchar(const char* _Source);
	std::string wchar_tochar(const wchar_t* _Source);


	std::vector<std::vector<std::string>> loadcsv_tocharvec(const char* _Path);
	// std::vector<std::vector<std::wstring>> loadcsv_towcharvec(const wchar_t* _Path);


	std::string char_tosha1(const char* _Path);
};

