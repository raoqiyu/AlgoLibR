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
  Node *last_char_ptr;
  std::map<wchar_t, u_long> left_neighbors;
} WordNeighbor;

class NewWordExtractor : public NGramCounter {
 public:
  NewWordExtractor(const uint8_t max_word_length = 4);

  void Extract(const char *src_fname);

 private:
  inline void AddBeginWord(std::wstring &line);
  inline void AddWord(std::wstring &line, const unsigned long start_pos, const unsigned long n_end);

  void GetWord(Node *node, std::wstring &word);

  void CalcScore();
  inline void CalcEntropyScore(const std::map<Node *, WordNeighbor>::iterator &word_iter);
  void CalcPointMutalInformation();

  std::map<Node *, WordNeighbor> m_words;
  std::wregex delimiters = std::wregex(L"[a-zA-Z0-9!@#$%^&*,./:(){}\\[\\];'“！@#¥%……&*（）！、，。/：；\"，「」【】　]");
};

} // namespace word
} // namespace mining
} // namespace nlp
} // namespace ai
} // namespace AlgoLibR




#endif