#ifndef _WIN32
#include "UnixPlatformMisc.h"
#include <iostream>
#include <algorithm>
//#include <sys/types.h>
#include <ifaddrs.h>
#include <sys/ioctl.h> 
#include <net/if.h> 
#include <string.h> 
#include <stdio.h>
#include <unistd.h>
#include <netdb.h>
//#include <sys/socket.h>
//#include <netinet/in.h>
#include <arpa/inet.h>
#include <boost/filesystem.hpp>
#include <fstream>

namespace of3d
{
	std::string LinuxPlatformMisc::GetDeviceId()
	{
		return GetMacAddress();
	}

	std::string LinuxPlatformMisc::GetOperatingSystemId()
	{
		std::string machineId;

		boost::filesystem::path machineIdFilename("/etc/machine-id");

		if (boost::filesystem::is_regular_file(machineIdFilename))
		{
			std::ifstream in;
			in.open(machineIdFilename.string());

			std::getline(in, machineId);
		}

		return machineId;
	}

	std::string LinuxPlatformMisc::GetMacAddress()
	{
		struct ifreq ifr;
		struct ifconf ifc;
		char buf[1024];
		int success = 0;

		int sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP);
		if (sock == -1) { /* handle error*/ };

		ifc.ifc_len = sizeof(buf);
		ifc.ifc_buf = buf;
		if (ioctl(sock, SIOCGIFCONF, &ifc) == -1) { /* handle error */ }

		struct ifreq* it = ifc.ifc_req;
		const struct ifreq* const end = it + (ifc.ifc_len / sizeof(struct ifreq));

		for (; it != end; ++it) {
			strcpy(ifr.ifr_name, it->ifr_name);
			if (ioctl(sock, SIOCGIFFLAGS, &ifr) == 0) {
				if (!(ifr.ifr_flags & IFF_LOOPBACK)) { // don't count loopback
					if (ioctl(sock, SIOCGIFHWADDR, &ifr) == 0) {
						success = 1;
						break;
					}
				}
			}
			else { /* handle error */ }
		}

		std::string MacAddressString;
		if (success)
		{
			char mac[30];

			sprintf(mac, "%02X%02X%02X%02X%02X%02X", //以太网MAC地址的长度是48位
				(unsigned char)ifr.ifr_hwaddr.sa_data[0],
				(unsigned char)ifr.ifr_hwaddr.sa_data[1],
				(unsigned char)ifr.ifr_hwaddr.sa_data[2],
				(unsigned char)ifr.ifr_hwaddr.sa_data[3],
				(unsigned char)ifr.ifr_hwaddr.sa_data[4],
				(unsigned char)ifr.ifr_hwaddr.sa_data[5]);

			MacAddressString = mac;

			std::transform(MacAddressString.begin(),
				MacAddressString.end(),
				MacAddressString.begin(),
				[](unsigned char c) { return std::tolower(c); });
		}
		else
		{
			MacAddressString = "000000000000";
		}

		return MacAddressString;
	}

} //namespace
#endif