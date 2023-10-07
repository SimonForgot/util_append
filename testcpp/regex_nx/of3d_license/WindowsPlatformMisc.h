#pragma once

#ifdef _WIN32
#include "GenericPlatformMisc.h"
#include <windows.h>


namespace of3d
{

class WindowsPlatformMisc : public GenericPlatformMisc
{
public:

    static std::string GetDeviceId();
    static std::string GetOperatingSystemId();


private:
    static bool QueryRegKey(const HKEY InKey, const TCHAR* InSubKey, const TCHAR* InValueName, std::string& OutData);
    static std::string GetMacAddress();
};

} // namespace

#endif