#pragma once

#include <string>
#include <vector>
#include <ctime>

namespace of3d
{
class license_utility
{
public:
    license_utility() = delete;
    ~license_utility() = delete;

    static std::string encrypt( std::string& msg, std::string& key );
    static std::string decrypt( std::string& encryptedMsg, std::string& key );
    static bool is_vaild_date( const std::string& endDate);
    static std::vector<std::string> tokenize( std::string& encryptedMsg );

private:

    static std::string _encrypt_vigenere(std::string& msg, std::string& key);
    static std::string _decrypt_vigenere(std::string& encryptedMsg, std::string& newKey);
    static std::string _extend_key(std::string& msg, std::string& key);
    static size_t _index(char c);

    static std::string _base64_encode(const std::string& in);
    static std::string _base64_decode(const std::string& in);

    static time_t _now();
    static time_t _to_time_t(const std::string& time, const std::string& format = "%d.%d.%d");
};

} // namespace