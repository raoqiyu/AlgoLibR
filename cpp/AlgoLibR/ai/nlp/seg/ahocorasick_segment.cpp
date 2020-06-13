/*
 * @Author: raoqiyu@gmail.com
 * @Date: 2020-02-17 11:08:32
 * @FilePath: /AlgoLibR/cpp/AlgoLibR/ai/nlp/seg/ahocorasick_segment.cpp
 * @Description: 
 */

#include <fstream> 
#include <iostream>
#include <cstring>
#include <vector>
#include <map>
#include "AlgoLibR/ai/nlp/seg/ahocorasick_segment.h"
#include "AlgoLibR/framework/string.h"
#include <regex>


namespace AlgoLibR{
namespace ai{
namespace nlp{
namespace seg{

WordProp::WordProp() : nature(NULL),freq(0), word_length(0){
    this->nature = new char[5];
    strncpy(this->nature, "NULL", 5); 
    this->nature[4] = '\0';
}

WordProp::WordProp(const char nature[], const size_t freq, 
                const unsigned int length) : nature(NULL), freq(freq), word_length(length){
    size_t len = strlen(nature);
    this->nature = new char[len + 1];
    strncpy(this->nature, nature, len+1);
} 

WordProp::WordProp(const WordProp& other) : nature(NULL),freq(0), word_length(0){
    if (this != &other){
        if (nature != NULL){
            delete nature;
            nature = NULL;
        }
        size_t len = strlen(other.nature);
        nature = new char[len + 1];
        strncpy(nature, other.nature, len + 1);
        this->word_length = other.word_length;
        this->freq = other.freq;
    }
}

WordProp& WordProp::operator=(const WordProp& other){
    if (this != &other){
        if (nature != NULL){
            delete nature;
            nature = NULL;
        }
        size_t len = strlen(other.nature);
        nature = new char[len + 1];
        strncpy(nature, other.nature, len + 1);
        this->word_length = other.word_length;
        this->freq = other.freq;
    }
    return *this;
}

WordProp::~WordProp(){
    if(nature != NULL){
        delete nature;
        nature = NULL;
    }
    
}

ACSegNode::ACSegNode(const wchar_t key){
    std::ios::sync_with_stdio(false);
    std::locale::global(std::locale(""));
    std::wcin.imbue(std::locale(""));
    std::wcout.imbue(std::locale(""));

    this->key =key;
    is_ending_key=false;
    parent = NULL;
    failure = NULL;
    word_prop = NULL;
}

ACSegNode::ACSegNode(){
    this->key = L'/';
}

ACSegNode::ACSegNode(const wchar_t key, ACSegNode* parent){
    this->key = key;
    this->parent = parent;
    failure=NULL;
    word_prop = NULL;
    is_ending_key=false;
}

ACSegNode::~ACSegNode(){
    auto iter = this->child_nodes.begin();
    while(iter != this->child_nodes.end()){
        delete iter->second;
        iter->second = NULL;
        child_nodes.erase(iter++);
    }
    if(word_prop != NULL){
        delete word_prop;
        word_prop = NULL;
    }
    parent=NULL;
    failure=NULL;
}

void ACSegNode::AddChild(const wchar_t key){
    if(child_nodes.find(key) != child_nodes.end()){
        return;
    }
    child_nodes[key] = new ACSegNode(key, this);
}

void ACSegNode::RemoveChild(const wchar_t key){
    auto iter = child_nodes.find(key);
    if( iter == child_nodes.end()){
        return;
    }
    delete iter->second;
    iter->second= NULL;
    child_nodes.erase(key);
}

AhoCorasickSegment::AhoCorasickSegment(): is_seg_all(true){
    std::ios::sync_with_stdio(false);
    std::locale::global(std::locale(""));
    std::wcin.imbue(std::locale(""));
    std::wcout.imbue(std::locale(""));
    root = new ACSegNode(L'A');
    this->combine_pattern_re = std::wregex(this->combine_pattern);

    // Build("/home/rqy/AlgoLibR/data/NLP/Dictionary/jieba_dict.txt.big", L" ");
    // std::wcout << "Init" << std::endl << std::flush;

    // std::wstring sentence(L"《三国演义》描写了从东汉末年到西晋初年之间近百年的历史风云，以描写战争为主，诉说了东汉末年的群雄割据混战和魏、蜀、吴三国之间的政治和军事斗争，最终司马炎一统三国，建立晋朝的故事。反映了三国时代各类社会斗争与矛盾的转化，并概括了这一时代的历史巨变，塑造了一群叱咤风云的三国英雄人物。");

    // std::vector<std::wstring> segmented = SegSentence(sentence.c_str());
    
    // for(auto i = 0; i < segmented.size(); i++){
    //     std::wcout << segmented[i] << " " ;
    // }

}

void AhoCorasickSegment::AddWord(const wchar_t word[], const char nature[], const size_t freq){
    ACSegNode* p = Add(word);
    p->word_prop = new WordProp(nature, freq, wcslen(word));
}

void AhoCorasickSegment::RemoveWord(const wchar_t word[]){
    Remove(word);
}



void AhoCorasickSegment::Build(const char dictionary_fname[], const std::wstring& delimiters){
    std::wifstream dictionary_file(dictionary_fname);
    std::wstring line;
    std::vector<std::wstring> word_props;
    if (!dictionary_file.is_open()){ 
        return;
    }
    while(std::getline(dictionary_file,line)){
        // word freq nature
        AlgoLibR::framework::string::split(line, word_props, delimiters);
        AddWord(word_props[0].c_str(), AlgoLibR::framework::string::wstr2str(word_props[2]).c_str(), 
                std::stoi(word_props[1]));
        word_props.clear();
    }
    dictionary_file.close();
}

std::size_t AhoCorasickSegment::GetKeySizeFromNode(const ACSegNode *p){
    const ACSegNode *node  = p;
    size_t word_size=0;
    while(node != this->root){
        word_size += 1;
        node = node->parent;
    }
    return word_size;
}

void AhoCorasickSegment::CollectKeySizesFromNode(const ACSegNode *p, int pos, std::map<size_t,std::vector<WordProp>> &dag){
    // check pointer is not NULL
    if(!p) return;

    ACSegNode *failure_node;
    size_t begin_pos;
    // WordProp word_p;
    std::vector<WordProp> word_list;
    dag[pos] = word_list;
    if(p == this->root) return;

    if(p->is_ending_key){
        // word_size = GetKeySizeFromNode(p);
        begin_pos = pos + 1 - p->word_prop->word_length;
        dag[begin_pos].push_back(*(p->word_prop));
    }
    
    failure_node = p->failure;
    while( failure_node){
        if(failure_node->is_ending_key){
            // word_size = GetKeySizeFromNode(failure_node);
            begin_pos = pos + 1 - failure_node->word_prop->word_length;;
            dag[begin_pos].push_back(*(failure_node->word_prop));
        }
        failure_node = failure_node->failure;
    }
}

void AhoCorasickSegment::ExtractDAG(const wchar_t sentence[], std::map<size_t,std::vector<WordProp>> &dag){
    BuildFailurePtr();

    size_t sen_len = wcslen(sentence);
    int i = 0;
    ACSegNode *p = GetNextNode(this->root, sentence[0]), *failure_node;

    for(i = 0; i < sen_len-1; i++){
        // Collect words ends with position i
        CollectKeySizesFromNode(p, i, dag);
        p = GetNextNode(p, sentence[i+1]);
    }
    CollectKeySizesFromNode(p, i, dag);
    for(auto iter = dag.begin(); iter != dag.end(); iter++){
        if(iter->second.empty()) iter->second.push_back(WordProp("null",0,1));
    }
}


void AhoCorasickSegment::SetSegAll(bool is_seg_all){
    this->is_seg_all = is_seg_all;
}


void AhoCorasickSegment::SetCombinePattern(const wchar_t pattern[]){
    this->combine_pattern = pattern;
    this->combine_pattern_re = std::wregex(pattern);

 }

std::vector<std::wstring> AhoCorasickSegment::SegSentence(const wchar_t sentence[]){
    std::vector<std::wstring> segmented;
    // std::vector<std::pair<size_t,std::string>> parsed;
    std::map<size_t,std::vector<WordProp>> dag;
    ExtractDAG(sentence, dag);

    std::wstring sen(sentence);
    long begin_pos=0, end_pos=-1;
    if(is_seg_all){
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

std::vector<std::wstring> AhoCorasickSegment::Segment(const wchar_t sentence[]){
    std::vector<std::wstring> sub_sentences ;
    std::vector<unsigned int> sub_sentences_kind ;

    // 对句子进行split，找出待分词的子局
    bool is_splited = AlgoLibR::framework::string::regex_wsplit(sentence, sub_sentences, sub_sentences_kind, this->split_pattern);

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
        if(!std::regex_match(s,this->combine_pattern_re)){
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

void AhoCorasickSegment::SegmentFile(const char src_fname[], const char dst_fname[]){
    std::wifstream src_file(src_fname);
    std::wofstream dst_file(dst_fname);
    std::wstring line;
    std::vector<std::wstring> word_props;
    if (!src_file.is_open()){
        std::wcout << src_fname << L" 文件打开失败..." << std::endl;
        return;
    }
    if (!dst_file.is_open()){
        std::wcout << dst_fname << L" 文件打开失败..." << std::endl;
        return;
    }

    std::vector<std::wstring> line_words;
    while(std::getline(src_file,line)){
        line_words = Segment(line.c_str());
        for(auto word:line_words){
            std::wcout << word << ' ';
            dst_file << word << ' ';
        }
        dst_file << '\n';
    }
    src_file.close();
    dst_file.close();
}


} // namespace seg
} // namespace nlp
} // namespace ai
} // namespace AlgoLibR
