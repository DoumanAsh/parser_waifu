#pragma once

namespace parser {
    /**
     * Internal module of parser.
     *
     * Not intended to be used outside of it.
     */
    namespace internal {
        /**
         * Escapes HTML characters in string
         *
         * @param[in] data String to escape.
         * @returns Escaped string.
         */
        inline std::string escape_html(std::string&& data) {
            std::string buffer;
            buffer.reserve(static_cast<size_t>(std::round(data.size() * 1.1)));
            for (size_t pos = 0; pos != data.size(); ++pos) {
                switch (data[pos]) {
                    case '&':  buffer.append("&amp;");       break;
                    case '\"': buffer.append("&quot;");      break;
                    case '\'': buffer.append("&apos;");      break;
                    case '<':  buffer.append("&lt;");        break;
                    case '>':  buffer.append("&gt;");        break;
                    default:   buffer.append(&data[pos], 1); break;
                }
            }

            return buffer;
        }
    }
}
