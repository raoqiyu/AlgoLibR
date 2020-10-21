#ifndef AI_SEG_AC_DAT_H
#define AI_SEG_AC_DAT_H

#include <map>
#include <vector>
#include <string>
#include <regex>
#include "AlgoLibR/data_structure/trie/ac_double_array_trie.hpp"

namespace AlgoLibR::ai::nlp::seg::ac_dat_segment{

class WordProp {
 public:
  unsigned int word_length;
  size_t freq;
  char *nature;

  WordProp(const char nature[], const size_t freq, const size_t word_length): freq(freq), word_length(word_length){
      auto len = strlen(nature);
      this->nature = new char[len + 1];
      strncpy(this->nature, nature, len+1);
  }
  WordProp(const WordProp& other) : nature(NULL),freq(0), word_length(0){
      if (this != &other){
          if (nature != NULL){
              delete nature;
              nature = NULL;
          }
          size_t len = strlen(other.nature);
          nature = new char[len + 1];
          strncpy(nature, other.nature, len + 1);
          this->word_length = other.word_length;
          this->freq = other.freq;
      }
  }
  ~WordProp(){
      if(this->nature != NULL) delete this->nature;
  }
};

class AhoCorasickDoubleArrayTrieSegment: private AlgoLibR::data_structure::trie::ac_dat::AhoCorasickDoubleArrayTrie<WordProp> {
 public:
  AhoCorasickDoubleArrayTrieSegment();
  void Build(const char dictionary_fname[], const std::wstring &delimiters);

  void SetSegAll(bool is_seg_all){ this->is_seg_all_ = is_seg_all;}

  void SetCombinePattern(const wchar_t pattern[]){
      this->combine_pattern_re_ = std::wregex(pattern);
  }

  std::vector<std::wstring> Segment(std::wstring sentence);
  std::vector<std::wstring> SegSentence(std::wstring sentence);

 private:
  void ExtractDAG(std::wstring sentence, std::map<size_t, std::vector<WordProp>> &dag);

  bool is_seg_all_;
  std::wstring split_pattern_ = L"([\u4E00-\u9FD5a-zA-Z0-9+#&._%-]+)";
  std::wregex combine_pattern_re_{L"([a-zA-Z0-9.-]+)"};
};

} // namespace


#endif
