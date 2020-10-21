
#include <vector>
#include <queue>
#include <unordered_set>
#include <unordered_map>

namespace AlgoLibR::data_structure::trie::ac_dat {

class ACDATNode {
 public:
  explicit ACDATNode(wchar_t chr) : chr(chr), key_index_(0), base_index_(0) {}
  ~ACDATNode() {
      for (auto & child_node : this->child_nodes_) {
          delete child_node;
      }
      this->child_nodes_.clear();
      this->child_indices_.clear();
      failure_ = nullptr;
  }

  ACDATNode *addChild(wchar_t key) {
      auto iter = this->child_indices_.find(key);
      if (iter != this->child_indices_.end()) {
          return this->child_nodes_[iter->second];
      }
      auto node = new ACDATNode(key);
      child_nodes_.push_back(node);
      child_indices_[key] = child_nodes_.size() - 1;
      return node;
  }

  void addChild(std::wstring key, size_t index) {
      ACDATNode *node = this;
      for (auto k : key) {
          node = node->addChild(k);
      }
      node = node->addChild(0);
      node->key_index_ = index + 1;
  }

  size_t getChildCount() const {
      return this->child_nodes_.size();
  }

  bool isExists(wchar_t key) {
      auto iter = this->child_indices_.find(key);
      return iter != this->child_indices_.end();
  }

  ACDATNode *getChild(wchar_t key) {
      auto iter = this->child_indices_.find(key);
      if (iter == this->child_indices_.end()) return nullptr;

      return this->child_nodes_[iter->second];
  }

  template <typename V> friend class AhoCorasickDoubleArrayTrie;
 protected:
  wchar_t chr;
  ACDATNode *failure_{};
  size_t key_index_, base_index_;
  std::unordered_map<wchar_t, size_t> child_indices_;
  std::vector<ACDATNode *> child_nodes_;
};

template<typename V>
class AhoCorasickDoubleArrayTrie {
 public:
  AhoCorasickDoubleArrayTrie() {
      this->root_ = new ACDATNode(L'/');
  }
  ~AhoCorasickDoubleArrayTrie() {
      if(this->root_ != nullptr) delete this->root_;
      this->base_.clear();
      this->check_.clear();
      this->keys_.clear();
      this->values_.clear();
      this->char2id_.clear();
      this->id2char_.clear();
  }

  void build(std::vector<std::wstring> keys, std::vector<V> values) {
      // build trie Tree
      buildTrieTree(keys, values);

      // build Double Array Trie
      buildDoubleArrayTrie();

      // construct failure array & output array
      constructFailure();

      // delete trie Tree
      delete this->root_;
      this->root_ = nullptr;
  }

  V get(std::wstring &key) {
      auto idx = exactMatchSearch(key);
      if (idx < 0) {
          return (V) NULL;
      }
      return this->values_[idx - 1];
  }

  V operator[](std::wstring &key) {
      return get(key);
  }

  int exactMatchSearch(std::wstring &key) {
      int result = -1;
      if (key.empty()) return result;
      int pos = this->base_[0], next_pos;
      for (auto chr:key) {
          auto chr_iter = this->char2id_.find(chr);
          if (this->char2id_.end() == chr_iter) return -1;
          next_pos = this->base_[pos] + chr_iter->second;
          if (pos + 1 == this->check_[next_pos]) {
              pos = next_pos;
          } else {
              return result;
          }
      }
      if (this->base_[this->base_[pos]] < 0 && pos + 1 == this->check_[this->base_[pos]])
          result = -this->base_[this->base_[pos]];
      return result;
  }

  std::vector<std::pair<size_t, std::wstring>> ParseText(const std::wstring &text) {
      std::vector<std::pair<size_t, std::wstring>> words;
      int state = 0, pos = 0;
      for (auto key : text) {
          std::wcout << pos << ',' << key << ',' << state << std::endl;
          state = transition(state, key);
          std::wcout << state << std::endl;
          collectOutputs(state, pos, words);
          pos++;
      }
      return words;
  }

 protected:
  int transition(int state, wchar_t key) {
      auto iter = this->char2id_.find(key);
      if (iter == this->char2id_.end()) return 0;

      uint16_t key_id = iter->second;
      int next_state = this->base_[state] + key_id;

      // 按照 success 表跳转
      if (state + 1 == this->check_[next_state]) {
          return next_state;
      }

      state = this->failures_[state];
      next_state = this->base_[state] + key_id;
      while (next_state != 0) {
          if (state + 1 == this->check_[next_state]) {
              return next_state;
          }
          if(this->failures_[state] == state) break;
          state = this->failures_[state];
          next_state = this->base_[state] + key_id;
      }
      return 0;
  }

  void collectOutputs(size_t state, size_t pos, std::vector<std::pair<size_t, std::wstring>> &words) {
      while (state != 0) {
          if (this->base_[this->base_[state]] < 0 && state + 1 == this->check_[this->base_[state]])
              words.emplace_back(pos, this->keys_[this->outputs_[this->base_[state]] - 1]);
          state = this->base_[this->failures_[state]];
      }
  }

  void collectValues(size_t state, std::vector<V> &words) {
      while (state != 0) {
          if (this->base_[this->base_[state]] < 0 && state + 1 == this->check_[this->base_[state]])
              words.push_back(this->values_[this->outputs_[this->base_[state]] - 1]);
          state = this->base_[this->failures_[state]];
      }
  }


 private:
  // build trie Tree
  void buildTrieTree(std::vector<std::wstring> &keys, std::vector<V> &values) {
      this->keys_ = keys;
      this->values_ = values;
      for (auto i = 0; i < keys.size(); i++) {
          this->root_->addChild(keys[i], i);
      }
  }

  void constructFailure() {
      this->failures_.resize(this->base_.size() + 1);
      this->outputs_.resize(this->base_.size());
      std::queue<ACDATNode *> nodes;

      // Step 1: set this->root's child nodes
      for (auto node : this->root_->child_nodes_) {
          this->failures_[node->base_index_] = this->root_->base_index_;
          node->failure_ = this->root_;
          nodes.push(node);
          constructOutput(node);
      }

      // Step 2: set other nodes (node's depth > 1)
      ACDATNode *current_node, *target_node, *failure_node, *tmp_node;
      while (!nodes.empty()) {
          current_node = nodes.front();
          nodes.pop();
          for (auto node : current_node->child_nodes_) {
              target_node = node;
              nodes.push(target_node);

              // find target_node's failure node from current_node's failure node
              failure_node = current_node->failure_;
              tmp_node = failure_node->getChild(target_node->chr);
              while (!tmp_node) {
                  failure_node = failure_node->failure_;
                  if (!failure_node) break;
                  tmp_node = failure_node->getChild(target_node->chr);
              }
              if (!failure_node) {
                  failure_node = this->root_;
              } else {
                  failure_node = tmp_node;
              }
              target_node->failure_ = failure_node;
              this->failures_[target_node->base_index_] = failure_node->base_index_;
              constructOutput(target_node);
          }
      }
  }

  void constructOutput(ACDATNode *node) {
      if (node->key_index_ == 0) return;
      this->outputs_[node->base_index_] = node->key_index_;
  }

  // build double array trie from trie Tree
  void buildDoubleArrayTrie() {
      std::unordered_set<int> used;
      std::vector<std::pair<uint16_t, ACDATNode *>> siblings;

      fetchSibling(this->root_, siblings);
      insertSibling(siblings, 1, used);
  }

  void fetchSibling(ACDATNode *node, std::vector<std::pair<uint16_t, ACDATNode *>> &siblings) {
      if (node->getChildCount() == 0)
          return;
      uint16_t chr_id;
      wchar_t chr;
      for (auto child_node : node->child_nodes_) {
          chr = child_node->chr;
          auto chr_iter = char2id_.find(chr);
          if (chr_iter == char2id_.end()) {
              chr_id = char2id_.size();
              char2id_[chr] = chr_id;
              id2char_[chr_id] = chr;
          } else {
              chr_id = char2id_[chr];
          }
          siblings.emplace_back(chr_id, child_node);
      }
  }

  size_t insertSibling(std::vector<std::pair<uint16_t, ACDATNode *>> &siblings,
                       size_t parent_pos,
                       std::unordered_set<int> &used) {
      if (siblings.empty()) return 0;

      long begin = -1, end, i, sub_begin;
      bool is_find = false;
      while (true) {
          begin++;
          if (this->base_.size() <= begin) {
              this->base_.resize(begin + 1);
              this->check_.resize(begin + 1);
          }

          if (used.end() != used.find(begin) || this->check_[begin] != 0) {
              continue;
          }

          end = begin + siblings.back().first + 1;
          if (this->base_.size() <= end) {
              this->base_.resize(end);
              this->check_.resize(end);
          }
          is_find = true;
          for (i = 0; i < siblings.size(); i++) {
              if (this->check_[begin + siblings[i].first] != 0 || this->base_[begin + siblings[i].first] != 0) {
                  is_find = false;
                  break;
              }
          }
          if (is_find) {
              break;
          }
      }
      for (i = 0; i < siblings.size(); i++) {
          this->check_[begin + siblings[i].first] = parent_pos;
      }
      used.insert(begin);
      std::vector<std::pair<uint16_t, ACDATNode *>> sub_siblings;
      for (i = 0; i < siblings.size(); i++) {
          sub_siblings.clear();
          fetchSibling(siblings[i].second, sub_siblings);

          if (sub_siblings.empty()) {
              // end of words
              this->base_[begin + siblings[i].first] = -siblings[i].second->key_index_;

          } else {
              sub_begin = insertSibling(sub_siblings, begin + siblings[i].first + 1, used);
              this->base_[begin + siblings[i].first] = sub_begin;
          }
          siblings[i].second->base_index_ = begin + siblings[i].first;
      }
      siblings.clear();
      return begin;
  }

  const ACDATNode *getRoot() {
      return this->root_;
  }

 private:
  ACDATNode *root_{};

  std::vector<long long> base_;
  std::vector<unsigned long long> check_;
  std::vector<std::wstring> keys_;
  std::vector<V> values_;

  std::vector<unsigned long long> outputs_;
  std::vector<unsigned long long> failures_;

  std::unordered_map<wchar_t, uint16_t> char2id_{{0, 0}};
  std::unordered_map<uint16_t, wchar_t> id2char_{{0, 0}};
};

}