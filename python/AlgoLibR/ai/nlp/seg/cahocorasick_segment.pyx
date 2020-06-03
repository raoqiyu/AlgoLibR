# distutils: language = c++
'''
Author: raoqiyu@gmail.com
Date: 2020-05-24 17:38:33
FilePath: /AlgoLibR/python/AlgoLibR/ai/nlp/seg/cahocorasick_segment.pxd
Description: 
'''
from libcpp.vector cimport vector
from AlgoLibR.utils.string cimport wchar_t,wstring, to_wchar_t,to_wstring,from_wstring
from cahocorasick_segment cimport AhoCorasickSegment
from cpython.mem cimport PyMem_Free


cdef class AhoCorasickSegmentor:
    cdef AhoCorasickSegment* c_ac_segmentor

    def __cinit__(self):
        self.c_ac_segmentor = new AhoCorasickSegment()
    
    def add_word(self, word, nature, freq):
        cdef wchar_t* s = to_wchar_t(word)
        self.c_ac_segmentor.AddWord(s, nature.encode(), freq)
        PyMem_Free(s)
    
    def remove_word(self, word):
        cdef wchar_t* s = to_wchar_t(word)
        self.c_ac_segmentor.RemoveWord(s)
        PyMem_Free(s)

    def Build(self, fname, delimiters):
        cdef wstring d = to_wstring(delimiters)
        print(delimiters)
        self.c_ac_segmentor.Build(fname, d)
    
    def set_seg_all(self, is_seg_all):
        self.c_ac_segmentor.SetSegAll(is_seg_all)

    def set_combine_pattern(self, pattern):
        cdef wchar_t* s = to_wchar_t(pattern)
        self.c_ac_segmentor.SetCombinePattern(s)
        PyMem_Free(s)

    def segment(self, sentence: str):
        cdef wchar_t* s = to_wchar_t(sentence)
        cdef vector[wstring] out = self.c_ac_segmentor.Segment(s)
        cdef size_t n = out.size()
        PyMem_Free(s)

        ret = []
        for i in range(n):
            ret.append(from_wstring(out[i]))
        return ret
    
    def __dealloc__(self):
        del self.c_ac_segmentor