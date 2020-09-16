//
// Created by raoqiyu on 2020/9/14.
//

#ifndef ALGOLIBR_CPP_ALGOLIBR_DATA_STRUCTURE_TRIE_DOUBLE_ARRAY_TRIE_H_
#define ALGOLIBR_CPP_ALGOLIBR_DATA_STRUCTURE_TRIE_DOUBLE_ARRAY_TRIE_H_

#include <vector>
#include <string>
#include <unordered_map>

namespace AlgoLibR {
namespace data_structure {
namespace trie {
namespace dat {
// namespace double array trie

typedef struct DATNode {
  uint16_t chr;
  uint8_t depth;
  size_t left;
  size_t right;
}DATNode;

class DoubleArrayTrie {
 public:
  DoubleArrayTrie();
  ~DoubleArrayTrie();

  void setKeys(std::vector<std::wstring> keys);
  void build(std::vector<std::wstring> keys, std::vector<size_t> values);
  int exactMatchSearch(std::wstring &key);
  std::vector<int> commonPrefixSearch(std::wstring &key);

  wchar_t getCharById(uint16_t id);
  void fetchSibling(DATNode *node, std::vector<DATNode*> &siblings);
//  void insertSibling(std::vector<DATNode*> &siblings);

 protected:
  std::vector<int> base;
  std::vector<int> check;
  std::vector<std::wstring> keys;
  std::vector<size_t> values;

  std::unordered_map<wchar_t, uint16_t> char2id;
  std::unordered_map<uint16_t, wchar_t> id2char;

};

} // namespace dat
} // namespace trie
} // namespace data_structure
} // namespace AlgoLibR

#endif //ALGOLIBR_CPP_ALGOLIBR_DATA_STRUCTURE_TRIE_DOUBLE_ARRAY_TRIE_H_
