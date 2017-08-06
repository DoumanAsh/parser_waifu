#pragma once

#include <QString>

namespace utils {
    namespace jp {
        /**
         * Checks whether string contains japanese text.
         * @param[in] text String to check.
         * @retval true Contains japanese text.
         * @retval false Otherwise.
         */
        bool has_jp(const QString& text);
    }
}
