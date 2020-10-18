
#include <vector>
#include <queue>
#include <unordered_set>
#include <unordered_map>

namespace AlgoLibR::data_structure::trie::ac_dat{

class ACDATNode{
 public:
  explicit ACDATNode(wchar_t chr): chr(chr), key_index(0), base_index(0){}
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

  bool isExists(wchar_t key){
      auto iter = this->child_indices.find(key);
      return iter != this->child_indices.end();
  }

  ACDATNode* getChild(wchar_t key){
      auto iter = this->child_indices.find(key);
      if(iter == this->child_indices.end()) return nullptr;

      return this->child_nodes[iter->second];
  }

  wchar_t chr;
  ACDATNode *failure;
  size_t  key_index, base_index;
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
      constructFailure();

      // delete trie Tree
//      delete this->m_root;
  }

  V get(std::wstring &key){
      auto idx = exactMatchSearch(key);
      if(idx < 0){
          return (V) NULL;
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

  std::vector<std::pair<size_t, std::wstring>> ParseText(const std::wstring &text){
      std::vector<std::pair<size_t, std::wstring>> words;
      int state = 0, pos=0;
      for(auto key : text){
          std::wcout << pos << ',' << key << ',' << state << std::endl;
          state = transition(state, key);
          std::wcout << state << std::endl;
          collectOutputs(state, pos, words);
          pos++;
      }
      return words;
  }

 protected:
  // build trie Tree
  void buildTrieTree(std::vector<std::wstring> &keys, std::vector<V> &values){
      this->m_keys = keys;
      this->m_values = values;
      for(auto i = 0; i < keys.size(); i++){
          this->m_root->addChild(keys[i], i);
      }
  }

  void constructFailure(){
      this->m_failure.resize(this->m_base.size()+1);
      this->m_output.resize(this->m_base.size());
      std::queue<ACDATNode*> nodes;

      // Step 1: set this->root's child nodes
      for(auto node : this->m_root->child_nodes){
          this->m_failure[node->base_index] = this->m_root->base_index;
          node->failure = this->m_root;
          nodes.push(node);
          constructOutput(node);
      }

      // Step 2: set other nodes (node's depth > 1)
      ACDATNode *current_node, *target_node, *failure_node, *tmp_node;
      while(!nodes.empty()){
          current_node = nodes.front();
          nodes.pop();
          for(auto node : current_node->child_nodes){
              target_node = node;
              nodes.push(target_node);

              // find target_node's failure node from current_node's failure node
              failure_node = current_node->failure;
              tmp_node = failure_node->getChild(target_node->chr);
              while(!tmp_node){
                  failure_node = failure_node->failure;
                  if(!failure_node) break;
                  tmp_node = failure_node->getChild(target_node->chr);
              }
              if(!failure_node){
                  failure_node = this->m_root;
              }else{
                  failure_node = tmp_node;
              }
              target_node->failure = failure_node;
              this->m_failure[target_node->base_index] = failure_node->base_index;
              constructOutput(target_node);
          }
      }
  }

  void constructOutput(ACDATNode* node){
      if(node->key_index == 0) return;
      this->m_output[node->base_index] = node->key_index;
  }

  int transition(int state, wchar_t key){
      auto iter = this->char2id.find(key);
      if(iter == this->char2id.end()) return 0;

      uint16_t key_id = iter->second;
      int next_state = this->m_base[state] + key_id;

      // 按照 success 表跳转
      if(state + 1 == this->m_check[next_state]){
          return next_state;
      }

      state = this->m_failure[state];
      while(state != 0){
          next_state =  this->m_base[state] + key_id;
          if(state + 1 == this->m_check[next_state]){
              return next_state;
          }
          state = this->m_failure[state];
      }
      return 0;
  }

  void collectOutputs(size_t state, size_t pos, std::vector<std::pair<size_t, std::wstring>> &words){
      while(state != 0){
          if(this->m_base[this->m_base[state]] < 0 && state+1 == this->m_check[this->m_base[state]])
              words.emplace_back(pos, this->m_keys[this->m_output[this->m_base[state]]-1]);
          state = this->m_base[this->m_failure[state]];
      }

  }

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
          siblings[i].second->base_index = begin + siblings[i].first;
      }
      siblings.clear();
      return begin;
  }

  const ACDATNode* getRoot(){
      return this->m_root;
  }


 private:
  ACDATNode *m_root{};

  std::vector<int> m_base;
  std::vector<uint> m_check;
  std::vector<std::wstring> m_keys;
  std::vector<V> m_values;

  std::vector<size_t> m_output;
  std::vector<size_t> m_failure;

  std::unordered_map<wchar_t, uint16_t> char2id{{0,0}};
  std::unordered_map<uint16_t, wchar_t> id2char{{0,0}};
};



}