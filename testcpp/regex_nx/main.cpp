#include <boost/algorithm/string/regex.hpp>
#include <boost/filesystem.hpp>
#include <boost/regex.hpp>
#include <iostream>
#include <license_utility.h>

void old_f();

template <class Container> void split(const std::string &str, Container &cont)
{
    boost::algorithm::split_regex(cont, str, boost::regex(":"));
}

int main()
{
    old_f();

    const char *homePath = getenv("HOME");
    assert(homePath != nullptr);
    boost::filesystem::path path_filename(homePath);
    path_filename = path_filename / "NxToolSets" / "license.lic";

    if (boost::filesystem::is_regular_file(path_filename))
    {
        std::ifstream in;
        in.open(path_filename.string());

        std::string EncryptedLicense;
        std::getline(in, EncryptedLicense);

        std::string LicenseKey = "OF3D";
        std::string DecryptedLicense = of3d::license_utility::decrypt(EncryptedLicense, LicenseKey);

        auto msg_array = of3d::license_utility::tokenize(DecryptedLicense);

        std::cout << DecryptedLicense << "\n";

        for (auto i : msg_array)
        {
            std::cout << i << "\n";
        }
    }
}