#include <iostream>
#include <filesystem>
namespace fs = std::filesystem;
int main()
{
    std::string str = fs::temp_directory_path();
    std::cout << "Temp directory is " << str << '\n';

}