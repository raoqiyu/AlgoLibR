/*
 * @Author: raoqiyu@gmail.com
 * @Date: 2020-08-09 22:15:00
 * @FilePath: /AlgoLibR/cpp/AlgoLibR/ai/nlp/mining/word/NewWordExtractor.h
 * @Description: 
 */

#ifndef NEWWORDEXTRACTOR_H
#define NEWWORDEXTRACTOR_H

#include <map>
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
  double score;
  uint8_t word_length;
  Node *start_char_ptr;
  std::map<wchar_t, u_long> left_neighbors;
} WordNeighbor;

class NewWordExtractor : public NGramCounter {
 public:
  explicit NewWordExtractor(uint8_t max_word_length = 4, unsigned long long min_freq=5);

  void Extract(const char *src_fname);

 private:
  void AddNGram(const wchar_t gram[], Node **start_char_ptr, Node **ending_char_ptr);

  inline void AddBeginWord(std::wstring &line);
  inline void AddWord(std::wstring &line, unsigned long start_pos, unsigned long n_end);

  void GetWord(Node *node, std::wstring &word);

  void CalcScore();
  inline void CalcEntropyScore(const std::map<Node *, WordNeighbor>::iterator &word_iter);
  void CalcPointMutalInformation(const std::map<Node *, WordNeighbor>::iterator &word_iter,
                                 std::map<uint8_t, size_t> &ngram_count);

  inline wchar_t FindLeadingChar(Node *end_node);
  void Filter();

  unsigned long long m_min_freq;
  std::map<Node *, WordNeighbor> m_words;
  std::wregex delimiters = std::wregex(L"[^\\u4e00-\\u9fa5\\u0030-\\u0039\\u0041-\\u005a\\u0061-\\u007a]");

  std::map<wchar_t, u_long> start_char_count;
  std::map<wchar_t, u_long> end_char_count;
};

} // namespace word
} // namespace mining
} // namespace nlp
} // namespace ai
} // namespace AlgoLibR




#endif