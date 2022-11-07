#include <iostream>
#include <boost/filesystem.hpp>
#include <filesystem>
#include <tbb/tbb.h>
int main()
{
    auto tmp_path = boost::filesystem::temp_directory_path();
    auto temp_str = tmp_path.string();
    std::cout << temp_str;

    auto tmp_dir = std::filesystem::temp_directory_path();
    auto temp_str2 = tmp_dir.string();
    std::cout << temp_str2;

    tbb::parallel_for(0, 100, 1, [](int i)
                      { std::cout << i; });
}