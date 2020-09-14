/*
 * @Author: raoqiyu@gmail.com
 * @Date: 2020-08-09 22:15:00
 * @FilePath: /AlgoLibR/cpp/AlgoLibR/ai/nlp/mining/word/NewWordExtractor.h
 * @Description: 
 */

#ifndef NEWWORDEXTRACTOR_H
#define NEWWORDEXTRACTOR_H

#include <unordered_map>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <set>
#include <fstream>
#include <regex>

#include "AlgoLibR/ai/nlp/mining/word/ngram_counter.h"

namespace AlgoLibR {
namespace ai {
namespace nlp {
namespace mining {
namespace word {

typedef struct WordNeighbor {
  double score = 0;
  wchar_t start_char;
  std::unordered_map<wchar_t, u_long> left_neighbors;
} WordNeighbor;

class NewWordExtractor : public NGramCounter {
 public:
  explicit NewWordExtractor(uint8_t max_word_length = 4, unsigned long long min_freq = 5);

  void Extract(const char *src_fname);

 private:
  inline void AddWord(std::wstring &str, u_long start_pos, uint8_t word_size);
  inline void AddWord(std::wstring &str, u_long start_pos, uint8_t word_size, Node **ending_char_ptr);
  inline void AddWord(wchar_t chr, Node **ending_char_ptr);

  inline void AddBeginWords(std::wstring &line);
  inline void AddWords(std::wstring &line, unsigned long start_pos, unsigned long n_end);

  void GetWord(Node *node, std::wstring &word);

  void CalcScore();
  inline void CalcEntropyScore(const std::unordered_map<Node *, WordNeighbor>::iterator &word_iter);
  inline void CalcPointMutalInformation(const std::unordered_map<Node *, WordNeighbor>::iterator &word_iter,
                                        const u_long &word_length_count, const u_long &single_char_count,
                                        uint8_t &word_length);

  inline wchar_t FindLeadingChar(Node *end_node);
  void Filter();

  unsigned long long m_min_freq;
  std::unordered_map<uint8_t, u_long> ngram_count;
  std::unordered_map<uint8_t ,std::unordered_map<Node *, WordNeighbor>> m_words;

  std::wregex delimiters = std::wregex(L"[^\\u4e00-\\u9fa5\\u0030-\\u0039\\u0041-\\u005a\\u0061-\\u007a]");

  std::unordered_map<wchar_t, u_long> start_char_count;
  std::unordered_map<wchar_t, u_long> end_char_count;
};

} // namespace word
} // namespace mining
} // namespace nlp
} // namespace ai
} // namespace AlgoLibR




#endif