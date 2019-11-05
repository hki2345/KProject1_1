#include <KCore.h>
#include <CommDlg.h>
#include <commctrl.h>

#include "GMMakerInitiator.h"
#include "GMMakerUpdater.h"
#include "GMMakerReleaser.h"

#include "GMMainWindow.h"


#pragma comment(lib, "comctl32.lib")
#pragma comment(linker, "/manifestdependency:\"type='win32' \
    name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
    processorArchitecture='*' \
    publicKeyToken='6595b64144ccf1df' language='*'\"")

#if _DEBUG
#if Win32
#pragma comment(lib, "KCore_Debug32")
#elif x64
#pragma comment(lib, "KCore_Debug64")
#endif // WIN32

#else
#if Win32
#pragma comment(lib, "KCore_Release32")
#elif x64
#pragma comment(lib, "KCore_Release64")
#endif
#endif



int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	GMMainWindow* NewWindow = new GMMainWindow();
	NewWindow->set_window(hInstance, lpCmdLine, nCmdShow);
	NewWindow->set_clienttowindow({ 1600, 900 });
	NewWindow->set_color(RGB(122, 122, 122));

	return core_launch<GMMakerInitiator, GMMakerUpdater, GMMakerReleaser>(NewWindow);
}
