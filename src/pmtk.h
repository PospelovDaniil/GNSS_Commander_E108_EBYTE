#ifndef PMTK_H
#define PMTK_H
#include <string>
typedef unsigned char u8;

/**
 * @brief   getContolSum
 * @details Claculate check sum for protocol PMTK
 *          Algorithm: xor every simbol in str
 *
 *          $PGKC Command Arguments * CheckSum CR LF
 *          Ex: $PGKC115,1,0,0,0*2B<CR><LF> == "$PGKC115,1,0,0,0*2B\r\n" . 2B here checksum, PGKC115,1,0,0,0 string for xor
 *          Ex: $X*Y - GNSS command, where X - command, Y - check sum command
 * @param   str
 * @return
 */
inline u8 getContolSum(const std::string &str) noexcept
{
    if(str.empty()) return 0;
    auto it = str.begin();
    u8  res = *it;

    while(it != str.end()) res ^= *++it;
    return res;
}

inline u8 getContolSum(const char *str, const u8 len) noexcept
{
    if(!len) return 0;
    u8 res = str[0];

    for(auto i = 1; i < len; ++i) res ^= str[i];
    return res;
}

#endif // PMTK_H
