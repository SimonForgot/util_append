#include <boost/filesystem.hpp>
#include <filesystem>
#include <iostream>

void test()
{
    auto tmp_path = boost::filesystem::temp_directory_path();
    auto temp_str = tmp_path.string();
    std::cout << temp_str << "\n";

    auto tmp_dir = std::filesystem::temp_directory_path();
    auto temp_str2 = tmp_dir.string();
    std::cout << temp_str2 << "\n";

    boost::filesystem::path path_filename("/home/zhangxinlong");
    path_filename = path_filename / "NxToolSets" / "license123.lic";
    std::cout << boost::filesystem::is_regular_file(path_filename);
}