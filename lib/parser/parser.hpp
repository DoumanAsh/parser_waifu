#pragma once

#include "mecab.h"
#include <string>

namespace parser {
    /**
     * Parser interface for all to implement.
     */
    class Interface {
        public:
            virtual std::string parse(const std::string& str) = 0;
    };

    /**
     * Mecab parser that wraps Mecab::Tagger
     *
     * Assumes utf-8
     */
    class Mecab: public Interface {
        public:
            Mecab();
            ~Mecab();
            std::string parse(const std::string& str) final override;

        private:
            MeCab::Tagger *tagger;
    };
}
