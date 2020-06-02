# distutils: language=c++
'''
Author: raoqiyu@gmail.com
Date: 2020-05-24 17:38:33
FilePath: /AlgoLibR/python/AlgoLibR/ai/nlp/seg/cahocorasick_segment.pxd
Description: 
'''
cimport cython
from libcpp cimport bool
from libcpp.vector cimport vector
from libcpp.pair cimport pair
from libc.stddef cimport wchar_t
from AlgoLibR.utils.string cimport wstring


cdef extern from "AlgoLibR/data_structure/tree/trie_tree.h" namespace "AlgoLibR::data_structure::tree::trie":
    cdef cppclass Trie[T]:
        Trie()
        T* Add(const wchar_t keys[])
        T* FindNode(const wchar_t keys[])
        bool Search(const wchar_t keys[])
        void Remove(const wchar_t keys[])

cdef extern from "AlgoLibR/data_structure/tree/ac_trie.h" namespace "AlgoLibR::data_structure::tree::ac_trie":
    cdef cppclass ACTrieBase[T](Trie[T]):
        ACTrieBase()
        vector[pair[size_t,wstring]] ParseText(const wchar_t keys[])
        void BuildFailurePtr()
        T* FindNode(const wchar_t key[])
        T* GetNextNode(const T *p, const wchar_t key)

cdef extern from "AlgoLibR/ai/nlp/seg/ahocorasick_segment.h" namespace "AlgoLibR::ai::nlp::seg":
    cdef cppclass ACSegNode:
        ACSegNode()
        ACSegNode(const wchar_t key)
        ACSegNode(const wchar_t key, ACSegNode* parent)
        void AddChild(const wchar_t key, ACSegNode* parent)
        void RemoveChild(const wchar_t key)

    cdef cppclass AhoCorasickSegment(ACTrieBase[ACSegNode]):
        AhoCorasickSegment()
        void AddWord(const wchar_t word[], const char nature[], const size_t freq)
        void SetSegAll(bool is_seg_all)
        void SetIgnorePattern(const wchar_t pattern[])
        void Build(const char dictionary_fname[], const wstring& delimiters)
        vector[wstring] Segment(const wchar_t*)