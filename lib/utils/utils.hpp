#pragma once

#include <string>

namespace utils {
    /**
     * Checks whether Japanese text is present.
     *
     * param[in] str C++ Wide string.
     * @retval true At least one character contains Japanese code point.
     * @retval false Otherwise
     */
    bool is_jp(const std::wstring& str);
}
