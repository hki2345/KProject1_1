#include "KUnityParse.h"
#include <iostream>
#include <CommDlg.h>

#include <KPathManager.h>
#include <io.h>



#if _DEBUG
#if Win32
#pragma comment(lib, "KContainer_Debug32")
#elif x64
#pragma comment(lib, "KContainer_Debug64")
#endif // WIN32

#else
#if Win32
#pragma comment(lib, "KContainer_Release32")
#elif x64
#pragma comment(lib, "KContainer_Release64")
#endif
#endif


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// 위도우 메시지 처리
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		break;
	}
	default:
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}


void KUnityParse::init()
{
	KPathManager::instance()->init();
	load_cpp(true);
	save_cpp(true);

	MapCpp.clear();

	load_cpp(false);
	save_cpp(false);
}

void KUnityParse::init_window()
{
	WNDCLASS wndclass;
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = NULL;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = L"MyWndClass";

	if (!RegisterClass(&wndclass))
	{
		return;
	}

	// 윈도우 생성
	hWnd = CreateWindow(L"MyWndClass", L"Unity 발생기", WS_OVERLAPPEDWINDOW,
		0, 0, 20, 20, NULL, NULL, NULL, NULL);

	if (hWnd == NULL)
	{
		return;
	}

	ShowWindow(hWnd, SW_SHOWNORMAL);
}


void KUnityParse::load_cpp(const bool& _Core)
{
	if (true == _Core)
	{
		std::wcout << "Load KCore From... KCore Folder" << std::endl;

		std::wstring TargetPath = KPathManager::instance()->directory();

		TargetPath += L"KCore";
		TargetPath += L'\\';

		load_path(TargetPath.c_str());
	}

	else
	{
		std::wcout << "Load Client From... Select Folder" << std::endl;

		const int StrSize = 512;
		wchar_t PathStr[StrSize] = L"a";

		OPENFILENAME NewOpen;
		memset(&NewOpen, 0, sizeof(OPENFILENAME));
		NewOpen.lStructSize = sizeof(OPENFILENAME);
		NewOpen.hwndOwner = hWnd;
		NewOpen.lpstrFilter = L"패쓰\0";
		NewOpen.lpstrFile = PathStr;
		NewOpen.nMaxFile = StrSize;
		NewOpen.lpstrInitialDir = KPathManager::instance()->directory().c_str();

		//if (GetOpenFileName(&NewOpen))
		//{
		//	std::wstring Tmp = NewOpen.lpstrFile;
		//	size_t X = Tmp.find_last_of(L"\\", StrSize);
		//	NewOpen.lpstrFile[X + 1] = 0;
		//	load_path(NewOpen.lpstrFile);
		//}
		//else
		//{
		//	return;
		//}

		// 여기에다가 프로젝트 폴더 잡으삼ㅇㅇㅇ
		std::wstring TargetPath = KPathManager::instance()->directory();
		TargetPath += L"190911_BattleCity";
		TargetPath += L'\\';
		load_path(TargetPath.c_str());
	}
}



void KUnityParse::load_path(const wchar_t* _Path)
{
	struct _wfinddata_t FD;
	intptr_t Handle;
	std::wstring TargetPath = _Path;


	TargetPath += L"*.*";

	Handle = _wfindfirst(TargetPath.c_str(), &FD);


	while (0 == _wfindnext(Handle, &FD))
	{
		std::wstring Tmp = FD.name;
		if (-1 != (int)Tmp.find(L".cpp"))
		{
			MapCpp.insert(Tmp);
		}
	}

	_findclose(Handle);
}

void KUnityParse::save_cpp(const bool& _Core)
{
	if (true == _Core)
	{
		save_path(true);
	}
	else
	{
		save_path(false);
	}
}

void KUnityParse::save_path(const bool& _Core)
{
	sTarget.clear();
	std::wstring TargetPath = KPathManager::instance()->directory();
	if (true == _Core)
	{
		std::wcout << "Save KCoreUnity To... KUnityPerformerCore Folder" << std::endl;
		sTarget += L"00KUnityPerformerCore";
	}

	else
	{
		std::wcout << "Save Target To... KUnityPerformerClient Folder" << std::endl;
		sTarget += L"01KUnityPerformerClient";
	}



	TargetPath += L"KUnityPerformerWindow";
	TargetPath += L'\\';
	sTarget += L".cpp";
	TargetPath += sTarget;


	FILE* NFile;
	_wfopen_s(&NFile, TargetPath.c_str(), L"wt");


	fwprintf_s(NFile, L"#define _WINSOCKAPI_\n");
	fwprintf_s(NFile, L"#include <winsock2.h>\n");
	fwprintf_s(NFile, L"#include <windows.h>\n");
	fwprintf_s(NFile, L"\n");

	std::multiset<std::wstring>::iterator SIter = MapCpp.begin();
	std::multiset<std::wstring>::iterator EIter = MapCpp.end();


	for (; SIter != EIter; ++SIter)
	{
		std::wstring IncludePath = L"#include <";
		IncludePath += SIter->c_str();
		IncludePath += L">\n" ;

		fwprintf_s(NFile, IncludePath.c_str(), IncludePath.capacity());
	}

	fclose(NFile);
}