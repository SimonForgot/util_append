#pragma once

#ifndef _WIN32
#include "GenericPlatformMisc.h"


namespace of3d
{

class LinuxPlatformMisc : public GenericPlatformMisc
{
public:

    static std::string GetDeviceId();
    static std::string GetOperatingSystemId();


private:
    static std::string GetMacAddress();
};

} // namespace

#endif