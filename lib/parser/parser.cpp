#include <stdexcept>

#include <iostream>

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

std::string Mecab::parse(const std::string& str) {
    const auto result = this->tagger->parse(str.c_str(), str.size());

    //It should be unlikely I suppose so let it be an excpetion.
    if (result == nullptr) std::runtime_error("Mecab is unable to parse");

    return std::string(result);
}
