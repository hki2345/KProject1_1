#include "KDebugManager.h"
#include "KWindowManager.h"
#include "KInputManager.h"

#include <Windows.h>
#include <KMacro.h>



void KDebugManager::init()
{
	bDebugAll = true;
	bDebugFigure = true;
	VectorLog.clear();
}

void KDebugManager::update()
{
	if (true == KInputManager::instance()->is_press(VK_LSHIFT))
	{
		if (true == KInputManager::instance()->is_down(0x42))
		{
			bDebugAll = !bDebugAll;
		}
		else if (true == KInputManager::instance()->is_down(0x43))
		{
			bDebugFigure = !bDebugFigure;
		}
	}
}


void KDebugManager::render()
{
	SetTextAlign(KWindowManager::instance()->back_hdc(), TA_LEFT);
	SetTextColor(KWindowManager::instance()->back_hdc(), RGB(0, 0, 0));
	SetBkMode(KWindowManager::instance()->back_hdc(), OPAQUE);
	
	for (int i = 0; i < (int)VectorLog.size(); i++)
	{
		TextOutW(KWindowManager::instance()->back_hdc(), 20, 20 + (20 * i), VectorLog[i].c_str(), (int)VectorLog[i].size());
	}

	VectorLog.clear();
}

void KDebugManager::release()
{
	VectorLog.clear();
	RELEASE_PTR(KSingleton::MyPtr);
}



void KDebugManager::insert_log(const wchar_t* const _Str, ...)
{
	if (false == bDebugAll)
	{
		return;
	}

#if _DEBUG
#else
	return;
#endif
	// 가변인자 받는 매크로 맨 밑에 end와 같이 쓰임

	// Ap -> 가변인자 들어가는 리스트
	// va_start -> 가변인자 시작지점
	// va_arg -> 뒤에 인자값 만큼 포인터를 이동시켜줌 -> 리턴값 그 포인터의 값을 반환
	// [단위 참고] char, short 의 경우에는 int로 대신 쓰고,
	// flaot의 경우에는 double로 대신 쓴 이후 형 변환을 해주어야 한다고 합디다. 
	// (예. char ch = (char) va_arg(ap, int); )
	// va_end -> 맨 뒤에 end를 넣어 가변인자의 사용을 종료한다.ㄴ
	va_list Ap;
	va_start(Ap, _Str);
	const wchar_t* TextPar = _Str;
	std::wstring TempString;

	while (*TextPar != 0)
	{
		if ('%' == *TextPar)
		{
			TextPar += 1;

			switch (*TextPar)
			{
			case 'd':
			{
				std::wstring NumTemp;
				NumTemp = std::to_wstring((int)(va_arg(Ap, int)));
				TempString += NumTemp;

				break;
			}
			case 'c':
			{
				TempString += (char)(va_arg(Ap, int));
				break;
			}
			case 'f':
			{
				std::wstring NumTemp;
				NumTemp = std::to_wstring((float)(va_arg(Ap, double)));
				TempString += NumTemp;

				break;
			}
			case 'b':
			{
				std::wstring NumTemp;

				if (0 == (va_arg(Ap, int)))
				{
					NumTemp = L"false";
				}
				else
				{
					NumTemp = L"true";
				}
				TempString += NumTemp;

				break;
			}
			default:
				break;
			}

			TextPar += 1;
		}
		else {
			TempString += *TextPar;
			TextPar += 1;
		}
	}

	VectorLog.push_back({ TempString.c_str() });

	va_end(Ap);
}