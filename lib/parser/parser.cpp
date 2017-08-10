#include <stdexcept>
#include <sstream>
#include <regex>

#include "internal.hpp"
#include "parser.hpp"

////////////////////////////////
//Parse result
////////////////////////////////
namespace parser {
    Kanji::Kanji(const std::string& text) :
        text(std::move(text)),
        reading(std::nullopt)
    {
    }

    Kanji::Kanji(const std::string& text, const std::string& reading) :
        text(std::move(text)),
        reading(std::move(reading))
    {
    }

    std::ostream& operator<<(std::ostream &out, const Kanji &kanji) {
        if (kanji.reading.has_value()) {
            return out << "<span title=\"" << *(kanji.reading) << "\">"
                       << kanji.text
                       << "</span>";
        }
        else {
            return out << kanji.text;
        }
    }

    std::ostream& operator<<(std::ostream &out, const Result &result) {
        for (auto kanji : result.inner) {
            out << kanji << " ";
        }

        return out;
    }

    std::string Result::to_string() const {
        std::ostringstream result;

        result << *this;

        return result.str();
    }
}

using namespace parser;

////////////////////////////////
//Mecab
////////////////////////////////

Mecab::Mecab() : tagger(MeCab::createTagger("")) {
    if (this->tagger == nullptr) throw std::runtime_error("Unable to create Mecab Tagger!");

    const auto dict_info = this->tagger->dictionary_info();

    if (dict_info == nullptr) throw std::runtime_error("Unable to retrieve Mecab dictionary info");
}

Mecab::~Mecab() {
    MeCab::deleteTagger(this->tagger);
    this->tagger = 0;
}

std::string Mecab::dict_path() const {
    return std::string(this->tagger->dictionary_info()->filename);
}

/**
 * Parses Mecab output.
 *
 * Its format:
 * Original Form\t
 * Part of Speech,
 * Part of Speech section 1,
 * Part of Speech section 2,
 * Part of Speech section 3,
 * Conjugated form,
 * Inflection,
 * Reading,
 * Pronounciation
 *
 * @param[in] str Japanese string.
 * @returns String with result
 */
Result Mecab::parse(const std::string& str) {
    const auto result_ptr = this->tagger->parse(str.c_str(), str.size());

    //It should be unlikely I suppose so let it be an excpetion.
    if (result_ptr == nullptr) std::runtime_error("Mecab is unable to parse");

    const std::string mecab_result(result_ptr);

    Result result;
    std::regex newline("^(?!EOS)(.+)\\n"); //Look ahead to skip EOS
    const std::sregex_iterator iter_end;
    const auto flags = std::regex_constants::match_not_null;
    for (auto line_iter = std::sregex_iterator(mecab_result.begin(), mecab_result.end(), newline, flags); line_iter != iter_end; ++line_iter) {
        static std::regex token_re("([^\\s,]+)", std::regex::ECMAScript);

        const auto line = line_iter->str(1);
        auto token = std::sregex_iterator(line.begin(), line.end(), token_re, flags);
        const auto kanji = internal::escape_html(token->str());
        ++token; //Original format
        ++token; //Part of Speech
        ++token; //Part of Speech 1
        ++token; //Part of Speech 2
        ++token; //Part of Speech 3
        ++token; //Conjugated form
        ++token; //Inflection
        ++token; //Reading

        if (token != iter_end) {
            const auto reading = token->str();

            result.emplace_back(kanji, reading);
        }
        else {
            result.emplace_back(kanji);
        }
    }

    return result;
}
