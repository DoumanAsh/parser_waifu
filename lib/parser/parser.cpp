#include <stdexcept>

#include <iostream>

#include "parser.hpp"

using namespace parser;

Mecab::Mecab() {
    this->tagger = MeCab::createTagger("");
    if (this->tagger == nullptr) throw std::runtime_error("Unable to create Mecab Tagger!");

    const auto dict_info = this->tagger->dictionary_info();

    if (dict_info == nullptr) throw std::runtime_error("Unable to retrieve Mecab dictionary info");

    //TODO: Windows only?
    //      There seems to be no cross-platform way to convert wide string to string.
    if (std::strcmp(dict_info->charset, "SHIFT-JIS") == 0) {
        this->charset = 932;
    }
    else if (std::strcmp(dict_info->charset, "EUC-JP") == 0) {
        this->charset = 20932;
    }
    else if (std::strcmp(dict_info->charset, "UTF-8") == 0) {
        this->charset = 65001;
    }
    else {
        throw std::runtime_error("Unknown chraset in Mecab dictionary!");
    }

}

Mecab::~Mecab() {
    MeCab::deleteTagger(this->tagger);
    this->tagger = 0;
}

std::string Mecab::parse(const std::string& str) {
    //mecab_sparse_tostr

    const auto result = this->tagger->parse(str.c_str(), str.size());

    //TODO: remove excpetion
    if (result == nullptr) std::runtime_error("Mecab is unable to parse");

    return std::string(result);
}
