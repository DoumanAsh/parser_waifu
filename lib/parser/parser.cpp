#include <stdexcept>
#include <sstream>
#include <regex>

#include "parser.hpp"

using namespace parser;

Mecab::Mecab() : tagger(MeCab::createTagger("")) {
    if (this->tagger == nullptr) throw std::runtime_error("Unable to create Mecab Tagger!");

    const auto dict_info = this->tagger->dictionary_info();

    if (dict_info == nullptr) throw std::runtime_error("Unable to retrieve Mecab dictionary info");
}

Mecab::~Mecab() {
    MeCab::deleteTagger(this->tagger);
    this->tagger = 0;
}

/**
 * Parses by Mecab.
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
std::string Mecab::parse(const std::string& str) {
    const auto result_ptr = this->tagger->parse(str.c_str(), str.size());

    //It should be unlikely I suppose so let it be an excpetion.
    if (result_ptr == nullptr) std::runtime_error("Mecab is unable to parse");

    const std::string mecab_result(result_ptr);

    //TODO: Prepare a proper output in HTML i suppose
    std::ostringstream result;
    std::regex newline("^(?!EOS)(.+)\\n"); //Look ahead to skip EOS
    const std::sregex_iterator iter_end;
    const auto flags = std::regex_constants::match_not_null;
    for (auto line_iter = std::sregex_iterator(mecab_result.begin(), mecab_result.end(), newline, flags); line_iter != iter_end; ++line_iter)
    {
        static std::regex token_re("([^\\s,]+)", std::regex::ECMAScript);
        const auto line = line_iter->str(1);
        for (auto token = std::sregex_iterator(line.begin(), line.end(), token_re, flags); token != iter_end; ++token) {
            result << token->str() << " | ";
        }

        result << "\n";

    }

    return result.str();
}
