#include <maxscript/maxscript.h>
HINSTANCE hInstance;
BOOL WINAPI DllMain(HINSTANCE DLLhinst, DWORD fdwReason, LPVOID lpvReserved)
{
	switch(fdwReason)
	{
	case DLL_PROCESS_ATTACH:
		MaxSDK::Util::UseLanguagePackLocale();
		hInstance = DLLhinst;
		DisableThreadLibraryCalls(hInstance);
		break;
	}
	return TRUE;
}
__declspec(dllexport) void LibInit()
{
}
__declspec(dllexport) const TCHAR* LibDescription()
{
	return _T("biped COM value scale");
}
__declspec(dllexport) ULONG LibVersion()
{
	return VERSION_3DSMAX;
}
