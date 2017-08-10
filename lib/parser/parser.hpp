#pragma once

#include "mecab.h"
#include <vector>
#include <string>
#include <utility>
#include <optional>

namespace parser {
    /**
     * Describes parsed kanji.
     */
    class Kanji {
        public:
            ///Constructs parsed kanji
            Kanji(const std::string& text);
            Kanji(const std::string& text, const std::string& reading);
            ///Kanji's text
            std::string text;
            ///Reading of Kanji in kana
            std::optional<std::string> reading;
        private:
            friend std::ostream& operator<<(std::ostream &out, const Kanji &result);
    };

    /**
     * Result of parsing.
     */
    class Result {
        public:
            template<class... Args>
            void emplace_back(Args&&... args) {
                this->inner.emplace_back(std::forward<Args>(args)...);
            }
            std::string to_string() const;
            friend std::ostream& operator<<(std::ostream &out, const Result &result);

        private:
            std::vector<Kanji> inner;
    };

    /**
     * Parser interface for all to implement.
     */
    class Interface {
        public:
            virtual Result parse(const std::string& str) = 0;
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

            Result parse(const std::string& str) final override;

            ///@returns Path to dictionary
            std::string dict_path() const;

        private:
            MeCab::Tagger *tagger;
    };
}
