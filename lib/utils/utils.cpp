#include "utils.hpp"

// 3000-303F : punctuation
// 3040-309F : hiragana
// 30A0-30FF : katakana
// FF00-FFEF : Full-width roman + half-width katakana
// 4E00-9FAF : Common and uncommon kanji

const wchar_t* JP_RE = L"[\u3000-\u303F]|[\u3040-\u309F]|[\u30A0-\u30FF]|[\uFF00-\uFFEF]|[\u4E00-\u9FAF]";

#include <regex>

bool utils::is_jp(const std::wstring& str) {
    static std::wregex jp_re(JP_RE, std::regex::ECMAScript);

    return std::regex_search(str, jp_re);
}


