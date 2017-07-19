set(MECAB_LIB_SRC ../mecabrc viterbi.cpp tagger.cpp  utils.cpp utils.h eval.cpp iconv_utils.cpp iconv_utils.h dictionary_rewriter.h dictionary_rewriter.cpp dictionary_generator.cpp dictionary_compiler.cpp context_id.h context_id.cpp winmain.h thread.h connector.cpp nbest_generator.h nbest_generator.cpp connector.h writer.h writer.cpp mmap.h ucs.h string_buffer.h string_buffer.cpp tokenizer.h stream_wrapper.h common.h darts.h char_property.h ucstable.h freelist.h viterbi.h param.cpp tokenizer.cpp ucstable.h char_property.cpp dictionary.h scoped_ptr.h param.h mecab.h dictionary.cpp feature_index.cpp  feature_index.h  lbfgs.cpp lbfgs.h  learner_tagger.cpp  learner_tagger.h  learner.cpp  learner_node.h libmecab.cpp)

option(SHARED_LIB "Build shared library" OFF)

if(SHARED_LIB)
    add_library(mecab SHARED ${MECAB_LIB_SRC})
else()
    add_library(mecab STATIC ${MECAB_LIB_SRC})
endif()


option(MECAB_EXE "Build shared library" OFF)

if(MECAB_EXE)
    add_executable(mecab-dict-index  mecab-dict-index.cpp)
    target_link_libraries(mecab-dict-index mecab)

    add_executable(mecab-dict-gen mecab-dict-gen.cpp)
    target_link_libraries(mecab-dict-gen mecab)

    add_executable(mecab-system-eval mecab-system-eval.cpp)
    target_link_libraries(mecab-system-eval mecab)

    add_executable(mecab-cost-train mecab-cost-train.cpp)
    target_link_libraries(mecab-cost-train mecab)

    add_executable(mecab-test-gen mecab-test-gen.cpp)
    target_link_libraries(mecab-test-gen mecab)

    add_executable(mecab-cli mecab.cpp)
    target_link_libraries(mecab-cli mecab)
endif()
