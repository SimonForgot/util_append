#include <max.h>
#include <iparamb2.h>
#include <HelloUtil.h>

static HelloUtil hello;

HINSTANCE hInstance = 0;
class MyClassDesc : public ClassDesc2
{
public:
    int IsPublic() { return TRUE; }
    void *Create(BOOL loading = FALSE) override { return &hello; }
    const TCHAR *ClassName() { return _T("MyPlugin"); }
    SClass_ID SuperClassID() { return UTILITY_CLASS_ID; }
    Class_ID ClassID() { return Class_ID(0x6b482709, 0x16376fca); }
    const TCHAR *Category() override { return _T("HiGame"); }
    const MCHAR *NonLocalizedClassName() override { return _T("MyPlugin"); }

    // returns fixed parsable name (scripter-visible name)
    const TCHAR *InternalName() { return _T("MyPlugin"); }

    // returns owning module handle
    HINSTANCE HInstance() { return hInstance; }
};

BOOL WINAPI DllMain(HINSTANCE hinstDLL, ULONG fdwReason, LPVOID /*lpvReserved*/)
{
    if (fdwReason == DLL_PROCESS_ATTACH)
    {
        // Hang on to this DLL's instance handle.
        hInstance = hinstDLL;
        DisableThreadLibraryCalls(hInstance);
    }
    return (TRUE);
}

extern "C"
{
    __declspec(dllexport) const TCHAR *LibDescription()
    {
        return _T("MyPlugin: A simple 3ds Max plugin example");
    }

    __declspec(dllexport) int LibNumberClasses()
    {
        return 1;
    }

    __declspec(dllexport) ClassDesc *LibClassDesc(int i)
    {
        static MyClassDesc widgetDesc;
        return (i == 0) ? &widgetDesc : nullptr;
    }

    __declspec(dllexport) ULONG LibVersion()
    {
        return Get3DSMAXVersion();
    }
    __declspec(dllexport) int LibInitialize()
    {
        // TODO: Perform initialization here.
        return TRUE;
    }

    __declspec(dllexport) int LibShutdown()
    {
        // TODO: Perform uninitialization here.
        return TRUE;
    }
}