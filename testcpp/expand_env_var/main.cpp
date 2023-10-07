#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <regex>
#include <map>
#include <utility>

std::pair<std::string, std::string> splitTo2Str(const std::string &s, char delim)
{
	int pos = s.find_first_of(delim);
	std::string head = s.substr(0, pos),
				tail = s.substr(pos + 1);
	return {head, tail};
}

std::map<std::string, std::string> getEnvVarMap()
{
	char **env;
#if defined(WIN) && (_MSC_VER >= 1900)
	env = *__p__environ();
#else
	extern char **environ;
	env = environ;
#endif
	std::map<std::string, std::string> res;
	for (env; *env; ++env)
	{
		std::string varStr = *env;
		auto varPair = splitTo2Str(varStr, '=');
		res[varPair.first] = varPair.second;
	}
	return res;
}

std::string expand_env_var(std::string str)
{
	auto map = getEnvVarMap();
	for (auto itr = map.begin(); itr != map.end(); itr++)
		str = std::regex_replace(str, std::regex("\\$" + itr->first), itr->second);
	return str;
}

int main()
{
	std::string str = "$LD_LIBRARY_PATH/qwe/eqweq/$LD_LIBRARY_PATH/qeweqw";
	std::cout << expand_env_var(str);
}