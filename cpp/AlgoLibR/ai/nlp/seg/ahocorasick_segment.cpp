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
    this->key =key;
    is_ending_key=false;
    parent = NULL;
    failure = NULL;
    word_prop = NULL;
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
}

void AhoCorasickSegment::AddWord(const wchar_t word[], const char nature[], const size_t freq){
    ACSegNode* p = Add(word);
    p->word_prop = new WordProp(nature, freq, wcslen(word));

}


void AhoCorasickSegment::Build(const char dictionary_fname[]){
    std::wifstream dictionary_file(dictionary_fname);
    std::wstring word;
    if (!dictionary_file.is_open()){ 
        return;
    }

    while(getline(dictionary_file,word)){
        AddWord(word.c_str(), "null", 1);
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
        // Dynamic Programming

    // }
    // std::vector<std::string> segmented;
    // std::vector<std::pair<size_t,std::string>> parsed;
    // parsed = ParseText(sentence);
    
    // size_t sen_len=wcslen(sentence),begin_pos=0, pos, tmp_pos=-1;
    // std::string word, tmp_word;
    // for(auto i = 0; i < parsed.size(); i++){
    //     pos = parsed[i].first;
    //     word = parsed[i].second;
    //     begin_pos = pos + 1 - word.length();
    //     std::cout << word << ": " << pos << ": " << begin_pos << "-" << pos << std::endl;
    //     if( begin_pos > tmp_pos+1){
    //         for(auto i = begin_pos; i <= pos; i++){
    //             tmp_word.push_back(sentence[i]);
    //         }
    //         segmented.push_back(tmp_word);
    //         tmp_word.clear();
    //     }
    //     segmented.push_back(word);
    //     tmp_pos = pos;
    // }
    // if(pos < sen_len-1){
    //    for(auto i = pos+1; i < sen_len; i++){
    //         tmp_word.push_back(sentence[i]);
    //     }
    //     segmented.push_back(tmp_word);
    //     tmp_word.clear(); 
    // }

    // return segmented;
}


std::vector<std::wstring> AhoCorasickSegment::SegChineseSentence(const wchar_t sentence[]){
    std::vector<std::string> segmented;
    std::vector<std::wstring> segmented_chinese;
    
    std::string str;

    segmented =SegSentence(sentence);
    std::cout << "len(segmented)" << segmented.size() << std::endl;
     for(auto i = 0; i < segmented.size(); i++){
        std::cout << segmented[i] << "," ;
    }
    std::cout << std::endl;
    bool is_zh_first=false, is_zh_second=false;
    for(auto i = 0; i < segmented.size(); i++){
        if(segmented[i].length() > 1){
            segmented_chinese.push_back(AlgoLibR::framework::string::str2wstr(segmented[i]));
            std::cout << "Raw: " <<  segmented[i] << std::endl;
            std::wcout << "Raw seg: " <<  segmented_chinese.back() << std::endl;
            continue;
        }
        if(segmented[i][0] & 0x80){
            if(is_zh_second){
                str = segmented[i]+segmented[i-1];
                std::cout << "str: " <<  str << std::endl;
                segmented_chinese.push_back(AlgoLibR::framework::string::str2wstr(str));
                std::wcout << segmented_chinese.back()<< std::endl;
                is_zh_first=false;
                is_zh_second=false;
             }else{
                 is_zh_second=true;
             }
         }

    }
        std::cout << "len(segmented)" << segmented_chinese.size() << std::endl;
    return segmented_chinese;
}

} // namespace seg
} // namespace nlp
} // namespace ai
} // namespace AlgoLibR
