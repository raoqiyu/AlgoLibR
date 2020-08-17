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

#include "AlgoLibR/ai/nlp/mining/word/ngram_counter.h"

namespace AlgoLibR {
namespace ai {
namespace nlp {
namespace mining {
namespace word {

typedef struct WordNeighbor {
 public:
  WordNeighbor(Node *last_wchar_ptr) : last_wchar_ptr(last_wchar_ptr) {}

  Node *last_wchar_ptr;
  std::set<wchar_t> left_neighbors;
  std::set<wchar_t> right_neighbors;
} WordNeighbor;

class NewWordExtractor : public NGramCounter {
 public:
  NewWordExtractor(const unsigned long min_n = 2, const unsigned long max_n = 4, const wchar_t *delimiters = nullptr);

  void Extract(const char *src_fname);

 private:
  inline void AddBeginWord(std::wstring &line);
  inline void AddWord(std::wstring &line, const unsigned long start_pos, const unsigned long n_end);

  void CalcScore();
  void CalcEntropy();
  void CalcPointMutalInformation();

  std::map<Node *, WordNeighbor> m_words;

};

} // namespace word
} // namespace mining
} // namespace nlp
} // namespace ai
} // namespace AlgoLibR




#endif