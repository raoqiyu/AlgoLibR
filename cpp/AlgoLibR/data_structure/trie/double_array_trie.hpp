//
// Created by raoqiyu on 2020/9/14.
//

#ifndef ALGOLIBR_CPP_ALGOLIBR_DATA_STRUCTURE_TRIE_DOUBLE_ARRAY_TRIE_H_
#define ALGOLIBR_CPP_ALGOLIBR_DATA_STRUCTURE_TRIE_DOUBLE_ARRAY_TRIE_H_


#include <unordered_set>
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

template<typename VALUETYPE>
class DoubleArrayTrie {
 public:

  DoubleArrayTrie() {}
  ~DoubleArrayTrie() {}

  void setKeys(std::vector<std::wstring> keys){
      this->m_keys = keys;
  }
  void build(std::vector<std::wstring> keys, std::vector<VALUETYPE> values) {
      this->m_keys = keys;
      this->m_values = values;

      DATNode root;
      root.depth = 0;
      root.left = 0;
      root.right = keys.size();

      std::vector<DATNode> siblings;
      std::unordered_set<int> used;

      fetchSibling(root, siblings);
      insertSibling(siblings, 1, used);
  }

  int exactMatchSearch(std::wstring &key){
      int result = -1;
      if(key.empty()) return result;
      int  pos = this->base[0], next_pos;
      for(auto chr:key){
          auto chr_iter = this->char2id.find(chr);
          if(this->char2id.end() == chr_iter) return -1;
          next_pos = this->base[pos] + chr_iter->second;
          if(pos+1 == this->check[next_pos]){
              pos = next_pos;
          }else{
              return result;
          }
      }
      if(this->base[this->base[pos]] < 0 && pos+1 == this->check[this->base[pos]])
          result = -this->base[this->base[pos]];
      return result;
  }

  wchar_t getCharById(uint16_t id){
      auto iter = this->id2char.find(id);
      if(this->id2char.end() == iter){
          return '\0';
      }else{
          return iter->second;
      }
  }


  void fetchSibling(DATNode &node, std::vector<DATNode> &siblings){
      auto target_depth = node.depth+1;
      wchar_t chr, last_char=0;
      uint16_t chr_id;
      for(auto i = node.left; i < node.right; i++){
          if(this->m_keys[i].size() < node.depth) continue;

          if(this->m_keys[i].size() == node.depth){
              chr = 0;
          }{
              chr = this->m_keys[i][node.depth];
          }

          if(chr != last_char or siblings.size() == 0){
              auto chr_iter = char2id.find(chr);
              if(chr_iter == char2id.end()){
                  chr_id = char2id.size();
                  char2id[chr] = chr_id;
                  id2char[chr_id] = chr;
              }else{
                  chr_id = char2id[chr];
              }

              DATNode sibling;
              sibling.depth = target_depth;
              sibling.chr = chr_id;
              sibling.left = i;
              if(siblings.size() > 0)
                  siblings[siblings.size() - 1].right = i;
              siblings.push_back(sibling);
          }
          last_char = chr;

      }
      if (siblings.size() != 0)
          siblings[siblings.size() - 1].right = node.right;
  }


  size_t insertSibling(std::vector<DATNode> &siblings, size_t parent_pos, std::unordered_set<int> &used) {
      if (siblings.empty()) return 0;

      long begin = -1, end, i, sub_begin;
      bool is_find = false;
      while (true) {
          begin++;
          if (this->base.size() <= begin) {
              this->base.resize(begin + 1);
              this->check.resize(begin + 1);
          }

          if (used.end() != used.find(begin) || this->check[begin] != 0) {
              continue;
          }

          end = begin + siblings.back().chr + 1;
          if (this->base.size() <= end) {
              this->base.resize(end);
              this->check.resize(end);
          }
          is_find = true;
          for (i = 0; i < siblings.size(); i++) {
              if (check[begin + siblings[i].chr] != 0 || base[begin + siblings[i].chr] != 0) {
                  is_find = false;
                  break;
              }
          }
          if (is_find) {
              break;
          }
      }
      for (i = 0; i < siblings.size(); i++) {
          check[begin + siblings[i].chr] = parent_pos;
      }
      used.insert(begin);
      std::vector<DATNode> sub_siblings;
      for (i = 0; i < siblings.size(); i++) {
          sub_siblings.clear();
          fetchSibling(siblings[i], sub_siblings);

          if (sub_siblings.empty()) {
              // end of words
              base[begin + siblings[i].chr] = -(long) siblings[i].left - 1;

          } else {
              sub_begin = insertSibling(sub_siblings, begin + siblings[i].chr + 1, used);
              base[begin + siblings[i].chr] = sub_begin;
          }

      }
      return begin;
  }
  

// protected:
  std::vector<int> base{0};
  std::vector<int> check{0};
  std::vector<std::wstring> m_keys;
  std::vector<VALUETYPE> m_values;
  size_t nextCheckPos{0};

  std::unordered_map<wchar_t, uint16_t> char2id{{0,0}};
  std::unordered_map<uint16_t, wchar_t> id2char{{0,0}};

};


} // namespace dat
} // namespace trie
} // namespace data_structure
} // namespace AlgoLibR

#endif //ALGOLIBR_CPP_ALGOLIBR_DATA_STRUCTURE_TRIE_DOUBLE_ARRAY_TRIE_H_
