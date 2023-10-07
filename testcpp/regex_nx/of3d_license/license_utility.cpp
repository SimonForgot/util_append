#include "license_utility.h"

//#define USE_STD_REGEX

#ifdef USE_STD_REGEX
#include <regex>
#else
#include <boost/algorithm/string/regex.hpp>
#endif

namespace of3d
{

static std::string AVAILABLE_CHARS = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 ";

std::string license_utility::encrypt(std::string &msg, std::string &key)
{
    auto b64_str = _base64_encode(msg);
    auto vigenere_msg = _encrypt_vigenere(b64_str, key);

    return vigenere_msg;
}

std::string license_utility::decrypt(std::string &encrypted_msg, std::string &key)
{
    auto newKey = _extend_key(encrypted_msg, key);
    auto b64_encoded_str = _decrypt_vigenere(encrypted_msg, newKey);
    auto b64_decode_str = _base64_decode(b64_encoded_str);
    return b64_decode_str;
}

bool license_utility::is_vaild_date(const std::string &endDate)
{
    auto now = _now();
    auto end = _to_time_t(endDate);
    return (end >= now);
}

std::vector<std::string> license_utility::tokenize(std::string &encryptedMsg)
{
#ifdef USE_STD_REGEX
    std::regex ws_re(":");
    std::vector<std::string> tokenizeStr(
        std::sregex_token_iterator(encryptedMsg.begin(), encryptedMsg.end(), ws_re, -1), std::sregex_token_iterator());
    return tokenizeStr;
#else
    std::vector<std::string> res_array;
    boost::algorithm::split_regex(res_array, encryptedMsg, boost::regex(":"));
    return res_array;
#endif
}

std::string license_utility::_extend_key(std::string &msg, std::string &key)
{
    // generating new key
    auto msgLen = msg.size();
    std::string newKey(msgLen, 'x');
    size_t keyLen = key.size(), i, j;
    for (i = 0, j = 0; i < msgLen; ++i, ++j)
    {
        if (j == keyLen)
            j = 0;

        newKey[i] = key[j];
    }
    newKey[i] = '\0';
    return newKey;
}

std::string license_utility::_encrypt_vigenere(std::string &msg, std::string &key)
{
    size_t msgLen = msg.size(), i;
    std::string encryptedMsg(msgLen, 'x');
    std::string newKey = _extend_key(msg, key);

    // encryption
    for (i = 0; i < msgLen; ++i)
    {
        if (isalnum(msg[i]) || msg[i] == ' ')
        {
            encryptedMsg[i] = AVAILABLE_CHARS[((_index(msg[i]) + _index(newKey[i])) % AVAILABLE_CHARS.size())];
        }
        else
        {
            encryptedMsg[i] = msg[i];
        }
    }

    encryptedMsg[i] = '\0';
    return encryptedMsg;
}

std::string license_utility::_decrypt_vigenere(std::string &encryptedMsg, std::string &newKey)
{
    // decryption
    size_t msgLen = encryptedMsg.size();
    std::string decryptedMsg(msgLen, 'x');
    int i;
    for (i = 0; i < msgLen; ++i)
    {
        if (isalnum(encryptedMsg[i]) || encryptedMsg[i] == ' ')
        {
            decryptedMsg[i] = AVAILABLE_CHARS[(
                ((_index(encryptedMsg[i]) - _index(newKey[i])) + AVAILABLE_CHARS.size()) % AVAILABLE_CHARS.size())];
        }
        else
        {
            decryptedMsg[i] = encryptedMsg[i];
        }
    }
    decryptedMsg[i] = '\0';
    return decryptedMsg;
}

size_t license_utility::_index(char c)
{
    auto found = AVAILABLE_CHARS.find(c);
    if (found != std::string::npos)
    {
        return found;
    }
    return -1;
}

std::string license_utility::_base64_encode(const std::string &in)
{
    std::string out;
    auto val = 0, valb = -6;
    for (size_t jj = 0; jj < in.size(); jj++)
    {
        auto c = in[jj];
        val = (val << 8) + c;
        valb += 8;
        while (valb >= 0)
        {
            out.push_back("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"[(val >> valb) & 0x3F]);
            valb -= 6;
        }
    }
    if (valb > -6)
        out.push_back(
            "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"[((val << 8) >> (valb + 8)) & 0x3F]);
    while (out.size() % 4)
        out.push_back('=');
    return out;
}

std::string license_utility::_base64_decode(const std::string &in)
{
    std::string out;
    std::vector<int> T(256, -1);
    for (auto i = 0; i < 64; i++)
        T["ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"[i]] = i;

    auto val = 0, valb = -8;
    for (size_t jj = 0; jj < in.size(); jj++)
    {
        auto c = in[jj];
        if (T[c] == -1)
            break;
        val = (val << 6) + T[c];
        valb += 6;
        if (valb >= 0)
        {
            out.push_back(char((val >> valb) & 0xFF));
            valb -= 8;
        }
    }
    return out;
}

time_t license_utility::_now()
{
    time_t t_now;
    time(&t_now);
    struct tm tm_now;
#ifdef _WIN32
    localtime_s(&tm_now, &t_now);
#else
    localtime_r(&t_now, &tm_now);
#endif
    tm_now.tm_hour = 0;
    tm_now.tm_min = 0;
    tm_now.tm_sec = 0;

    return mktime(&tm_now);
}

time_t license_utility::_to_time_t(const std::string &time, const std::string &format)
{
    struct tm tm_Temp;
    time_t time_Ret;
    try
    {
#ifdef _WIN32
        sscanf_s(time.c_str(), format.c_str(), // "%d/%d/%d" ,
                 &(tm_Temp.tm_year), &(tm_Temp.tm_mon), &(tm_Temp.tm_mday));
#else
        sscanf(time.c_str(), format.c_str(), // "%d/%d/%d" ,
               &(tm_Temp.tm_year), &(tm_Temp.tm_mon), &(tm_Temp.tm_mday));
#endif

        tm_Temp.tm_year -= 1900;
        tm_Temp.tm_mon--;
        tm_Temp.tm_hour = 0;
        tm_Temp.tm_min = 0;
        tm_Temp.tm_sec = 0;
        tm_Temp.tm_isdst = 0;
        time_Ret = mktime(&tm_Temp);
        return time_Ret;
    }
    catch (...)
    {
        return 0;
    }
}

} // namespace of3d
