#include <regex>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include "AlgoLibR/framework/string.h"
#include "AlgoLibR/ai/nlp/seg/ahocorasick_double_array_trie_segment.h"


namespace AlgoLibR::ai::nlp::seg::ac_dat_segment{

AhoCorasickDoubleArrayTrieSegment::AhoCorasickDoubleArrayTrieSegment() : is_seg_all_(true){

}

void AhoCorasickDoubleArrayTrieSegment::Build(const char dictionary_fname[], const std::wstring &delimiters){
    std::wifstream dictionary_file(dictionary_fname);
    std::wstring line;
    std::vector<std::wstring> word_props;
    if (!dictionary_file.is_open()){
        std::wcout << dictionary_fname << L"文件打开失败...\n" << std::endl;
        return;
    }
    std::vector<std::wstring> keys;
    std::vector<WordProp> values;
    while(std::getline(dictionary_file,line)){
        // word freq nature
        AlgoLibR::framework::string::split(line, word_props, delimiters);
        keys.push_back(word_props[0]);
        values.push_back(WordProp(AlgoLibR::framework::string::wstr2str(word_props[2]).c_str(),
                                  std::stoi(word_props[1]), word_props[0].length()));
        word_props.clear();
    }
    this->build(keys, values);
    dictionary_file.close();
}

void AhoCorasickDoubleArrayTrieSegment::ExtractDAG(const std::wstring sentence,
                                                   std::map<size_t, std::vector<WordProp>> &dag){
    int state = 0, pos = 0;
    std::vector<WordProp> words;
    for (auto key : sentence) {
        dag[pos] = words;
        state = transition(state, key);
        this->collectValues(state, words);
        if(!words.empty()) {
            for (const auto &word : words)
                dag[pos + 1 - word.word_length].push_back(word);
            words.clear();
        }
        pos++;
    }

    for(auto iter = dag.begin(); iter != dag.end(); iter++){
        if(iter->second.empty()) iter->second.push_back(WordProp("null",0,1));
    }
}

std::vector<std::wstring> AhoCorasickDoubleArrayTrieSegment::SegSentence(const std::wstring sentence){
    std::vector<std::wstring> segmented;
    // std::vector<std::pair<size_t,std::string>> parsed;
    std::map<size_t,std::vector<WordProp>> dag;
    ExtractDAG(sentence, dag);

    std::wstring sen(sentence);
    long begin_pos=0, end_pos=-1;
    if(this->is_seg_all_){
        for(auto iter=dag.begin(); iter != dag.end(); iter++){
            begin_pos = iter->first;
            if(iter->second.size() == 1 && begin_pos > end_pos){
                end_pos = begin_pos + iter->second[0].word_length-1;
                segmented.push_back(sen.substr(begin_pos, iter->second[0].word_length));
            }else{
                for(auto i = 0; i < iter->second.size(); i++){
                    if(iter->second[i].word_length==1) continue;

                    end_pos = begin_pos + iter->second[i].word_length-1;
                    segmented.push_back(sen.substr(begin_pos, iter->second[i].word_length));
                }
            }
        }
    }else{
        begin_pos = 0;
        unsigned int max_word_size = 0;
        while(begin_pos < sen.length()){
            if(dag.find(begin_pos) == dag.end()){
                segmented.push_back(sen.substr(begin_pos, 1));
                begin_pos++;
                continue;
            }
            max_word_size = 0;
            for(auto word : dag[begin_pos]){
                if(max_word_size < word.word_length){
                    max_word_size = word.word_length;
                }
            }
            segmented.push_back(sen.substr(begin_pos, max_word_size));
            begin_pos += max_word_size;
        }
    }

    return segmented;
}

std::vector<std::wstring> AhoCorasickDoubleArrayTrieSegment::Segment(const std::wstring sentence){
    std::vector<std::wstring> sub_sentences ;
    std::vector<unsigned int> sub_sentences_kind ;

    // 对句子进行split，找出待分词的子局
    bool is_splited = AlgoLibR::framework::string::regex_wsplit(sentence, sub_sentences,
                                                                sub_sentences_kind, this->split_pattern_);

    if(!is_splited){
        // split 失败，对整条句子进行分析
        return SegSentence(sentence);
    }

    // split 成功，对非ignore子句进行分词
    std::vector<std::wstring> segmented;
    for(auto i = 0; i < sub_sentences.size(); i++){
        if(sub_sentences[i].size() == 1 || sub_sentences_kind[i] == 0){
            segmented.push_back(sub_sentences[i]);
            continue;
        }
        for(auto sub_seg: SegSentence(sub_sentences[i].c_str())){
            segmented.push_back(sub_seg);
        }
    }

    // 按照pattern进行合并
    std::vector<std::wstring> segmented_combined;
    std::wstring combined;
    for(auto s: segmented){
        if(!std::regex_match(s,this->combine_pattern_re_)){
            if(combined.size() > 0){
                segmented_combined.push_back(combined);
                combined.clear();
            }
            segmented_combined.push_back(s);
        }else{
            combined += s;
        }
    }
    if(combined.size() > 0){
        segmented_combined.push_back(combined);
    }

    segmented.clear();
    return segmented_combined;
}

} // namespace
