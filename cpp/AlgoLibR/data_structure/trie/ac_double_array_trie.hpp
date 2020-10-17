
#include <vector>
#include <unordered_set>
#include <unordered_map>

namespace AlgoLibR::data_structure::trie::ac_dat{

class ACDATNode{
 public:
  explicit ACDATNode(wchar_t chr): chr(chr), key_index(0){}
  ~ACDATNode(){
      for(auto child_node:this->child_nodes){
          delete child_node;
          child_node = nullptr;
      }
      this->child_nodes.clear();
      this->child_indices.clear();
  }

  ACDATNode* addChild(wchar_t key){
      auto iter = this->child_indices.find(key);
      if( iter != this->child_indices.end()){
          return this->child_nodes[iter->second];
      }
      auto node = new ACDATNode(key);
      child_nodes.push_back(node);
      child_indices[key] = child_nodes.size()-1;
      return node;
  }

  void addChild(std::wstring key, size_t index){
      ACDATNode *node = this;
      for(auto k : key) {
        node = node->addChild(k);
      }
      node = node->addChild(0);
      node->key_index = index+1;
  }

  size_t getChildCount() const{
      return this->child_nodes.size();
  }

  wchar_t chr;
  size_t  key_index;
  std::unordered_map<wchar_t, size_t> child_indices;
  std::vector<ACDATNode*> child_nodes;
};

template<typename V>
class AhoCorasickDoubleArrayTrie{
 public:
  AhoCorasickDoubleArrayTrie(){
      this->m_root = new ACDATNode(L'/');
  }

  void build(std::vector<std::wstring> keys, std::vector<V> values){
      // build trie Tree
      buildTrieTree(keys, values);

      // build Double Array Trie
      buildDoubleArrayTrie();

      // construct failure array & output array
//      constructFailure();

  }

  V get(std::wstring &key){
      auto idx = exactMatchSearch(key);
      if(idx < 0){
          return NULL;
      }
      return this->m_values[idx-1];
  }

  V operator[](std::wstring &key){
      return get(key);
  }

  int exactMatchSearch(std::wstring &key){
      int result = -1;
      if(key.empty()) return result;
      int  pos = this->m_base[0], next_pos;
      for(auto chr:key){
          auto chr_iter = this->char2id.find(chr);
          if(this->char2id.end() == chr_iter) return -1;
          next_pos = this->m_base[pos] + chr_iter->second;
          if(pos+1 == this->m_check[next_pos]){
              pos = next_pos;
          }else{
              return result;
          }
      }
      if(this->m_base[this->m_base[pos]] < 0 && pos+1 == this->m_check[this->m_base[pos]])
          result = -this->m_base[this->m_base[pos]];
      return result;
  }


 protected:
  // build trie Tree
  void buildTrieTree(std::vector<std::wstring> &keys, std::vector<V> &values){
      this->m_values = values;
      for(auto i = 0; i < keys.size(); i++){
          this->m_root->addChild(keys[i], i);
      }
  }

  void constructFailure();
  void constructOutput();

  // build double array trie from trie Tree
  void buildDoubleArrayTrie(){
      std::unordered_set<int> used;
      std::vector<std::pair<uint16_t, ACDATNode*>> siblings;

      fetchSibling(this->m_root, siblings);
      insertSibling(siblings, 1, used);
  }

  void fetchSibling(ACDATNode *node, std::vector<std::pair<uint16_t, ACDATNode*>> &siblings){
      if(node->getChildCount() == 0)
          return ;
      uint16_t chr_id;
      wchar_t chr;
      for(auto child_node : node->child_nodes){
          chr = child_node->chr;
          auto chr_iter = char2id.find(chr);
          if(chr_iter == char2id.end()){
              chr_id = char2id.size();
              char2id[chr] = chr_id;
              id2char[chr_id] = chr;
          }else{
              chr_id = char2id[chr];
          }
          siblings.emplace_back(chr_id, child_node);
      }
  }

  size_t insertSibling(std::vector<std::pair<uint16_t, ACDATNode*>> &siblings, size_t parent_pos, std::unordered_set<int> &used){
      if (siblings.empty()) return 0;

      long begin = -1, end, i, sub_begin;
      bool is_find = false;
      while (true) {
          begin++;
          if (this->m_base.size() <= begin) {
              this->m_base.resize(begin + 1);
              this->m_check.resize(begin + 1);
          }

          if (used.end() != used.find(begin) || this->m_check[begin] != 0) {
              continue;
          }

          end = begin + siblings.back().first + 1;
          if (this->m_base.size() <= end) {
              this->m_base.resize(end);
              this->m_check.resize(end);
          }
          is_find = true;
          for (i = 0; i < siblings.size(); i++) {
              if (this->m_check[begin + siblings[i].first] != 0 || this->m_base[begin + siblings[i].first] != 0) {
                  is_find = false;
                  break;
              }
          }
          if (is_find) {
              break;
          }
      }
      for (i = 0; i < siblings.size(); i++) {
          this->m_check[begin + siblings[i].first] = parent_pos;
      }
      used.insert(begin);
      std::vector<std::pair<uint16_t, ACDATNode*>> sub_siblings;
      for (i = 0; i < siblings.size(); i++) {
          sub_siblings.clear();
          fetchSibling(siblings[i].second, sub_siblings);

          if (sub_siblings.empty()) {
              // end of words
              this->m_base[begin + siblings[i].first] =  -siblings[i].second->key_index;

          } else {
              sub_begin = insertSibling(sub_siblings, begin + siblings[i].first + 1, used);
              this->m_base[begin + siblings[i].first] = sub_begin;
          }
      }
      siblings.clear();
      return begin;
  }

  const ACDATNode* getRoot(){
      return this->m_root;
  }


 private:
  ACDATNode *m_root{};

  std::vector<int> m_base{0};
  std::vector<int> m_check{0};
  std::vector<V> m_values;

  std::vector<std::vector<std::wstring>> output;
  std::vector<int> failure;

  std::unordered_map<wchar_t, uint16_t> char2id{{0,0}};
  std::unordered_map<uint16_t, wchar_t> id2char{{0,0}};
};



}