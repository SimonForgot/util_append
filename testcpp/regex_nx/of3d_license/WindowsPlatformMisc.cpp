#ifdef _WIN32
#include "WindowsPlatformMisc.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <cctype>
#include <clocale>

#include <IPHlpApi.h>

#pragma comment(lib,"Iphlpapi.lib")

namespace of3d
{ 
std::string WindowsPlatformMisc::GetDeviceId()
{
    return GetMacAddress();
}

std::string WindowsPlatformMisc::GetOperatingSystemId()
{
    std::string Result;
    // more info on this key can be found here: http://stackoverflow.com/questions/99880/generating-a-unique-machine-id
    QueryRegKey(HKEY_LOCAL_MACHINE, TEXT("Software\\Microsoft\\Cryptography"), TEXT("MachineGuid"), Result);
    return Result;
}



bool WindowsPlatformMisc::QueryRegKey(const HKEY InKey, const TCHAR* InSubKey, const TCHAR* InValueName, std::string& OutData)
{
    bool bSuccess = false;

    // Redirect key depending on system
    for (int32_t RegistryIndex = 0; RegistryIndex < 2 && !bSuccess; ++RegistryIndex)
    {
        HKEY Key = 0;
        const uint32_t RegFlags = (RegistryIndex == 0) ? KEY_WOW64_32KEY : KEY_WOW64_64KEY;
        if (RegOpenKeyEx(InKey, InSubKey, 0, KEY_READ | RegFlags, &Key) == ERROR_SUCCESS)
        {
            ::DWORD Size = 0;
            // First, we'll call RegQueryValueEx to find out how large of a buffer we need
            if ((RegQueryValueEx(Key, InValueName, NULL, NULL, NULL, &Size) == ERROR_SUCCESS) && Size)
            {
                // Allocate a buffer to hold the value and call the function again to get the data
                char* Buffer = new char[Size];
                if (RegQueryValueEx(Key, InValueName, NULL, NULL, (LPBYTE)Buffer, &Size) == ERROR_SUCCESS)
                {
                    const uint32_t Length = (Size / sizeof(TCHAR)) - 1;
                    std::string str((TCHAR*)Buffer);
                    OutData = str;
                    
                    bSuccess = true;
                }
                delete[] Buffer;
            }
            RegCloseKey(Key);
        }
    }

    return bSuccess;
}

std::string WindowsPlatformMisc::GetMacAddress()
{
    PIP_ADAPTER_INFO AdapterInfo;
    DWORD dwBufLen = sizeof(IP_ADAPTER_INFO);
    char* MacAddress = (char*)malloc(18);

    AdapterInfo = (IP_ADAPTER_INFO*)malloc(sizeof(IP_ADAPTER_INFO));
    if (AdapterInfo == NULL) {
        //printf("Error allocating memory needed to call GetAdaptersinfo\n");
        free(MacAddress);
        return std::string(); 
    }

    // Make an initial call to GetAdaptersInfo to get the necessary size into the dwBufLen variable
    if (GetAdaptersInfo(AdapterInfo, &dwBufLen) == ERROR_BUFFER_OVERFLOW) {
        free(AdapterInfo);
        AdapterInfo = (IP_ADAPTER_INFO*)malloc(dwBufLen);
        if (AdapterInfo == NULL) {
            //printf("Error allocating memory needed to call GetAdaptersinfo\n");
            free(MacAddress);
            return std::string();
        }
    }

    if (GetAdaptersInfo(AdapterInfo, &dwBufLen) == NO_ERROR) {
        // Contains pointer to current adapter info
        PIP_ADAPTER_INFO pAdapterInfo = AdapterInfo;
        do {
            // technically should look at pAdapterInfo->AddressLength
            // and not assume it is 6.
            sprintf_s(MacAddress, 18, "%02X%02X%02X%02X%02X%02X",
                pAdapterInfo->Address[0], pAdapterInfo->Address[1],
                pAdapterInfo->Address[2], pAdapterInfo->Address[3],
                pAdapterInfo->Address[4], pAdapterInfo->Address[5]);
            pAdapterInfo = pAdapterInfo->Next;
        } while (pAdapterInfo);
    }
    free(AdapterInfo);

    std::string MacAddressString(MacAddress);
    std::transform(MacAddressString.begin(),
                    MacAddressString.end(), 
                    MacAddressString.begin(),
                    [](unsigned char c) { return std::tolower(c); });
    free(MacAddress);

    return MacAddressString;
}

} //namespace
#endif