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
	// �������� �޴� ��ũ�� �� �ؿ� end�� ���� ����

	// Ap -> �������� ���� ����Ʈ
	// va_start -> �������� ��������
	// va_arg -> �ڿ� ���ڰ� ��ŭ �����͸� �̵������� -> ���ϰ� �� �������� ���� ��ȯ
	// [���� ����] char, short �� ��쿡�� int�� ��� ����,
	// flaot�� ��쿡�� double�� ��� �� ���� �� ��ȯ�� ���־�� �Ѵٰ� �յ��. 
	// (��. char ch = (char) va_arg(ap, int); )
	// va_end -> �� �ڿ� end�� �־� ���������� ����� �����Ѵ�.��
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