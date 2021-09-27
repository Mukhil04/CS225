/**
 * @file anagram_dict.cpp
 * Implementation of the AnagramDict class.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include "anagram_dict.h"

#include <algorithm> /* I wonder why this is included... */
#include <fstream>
#include <iostream>

using std::string;
using std::vector;
using std::ifstream;

/**
 * Constructs an AnagramDict from a filename with newline-separated
 * words.
 * @param filename The name of the word list file.
 */
AnagramDict::AnagramDict(const string& filename)
{
    /* Your code goes here! */
    ifstream wordsFile(filename);
    string word;
    std::map<string, int> values;
    if (wordsFile.is_open()) {
        while (getline(wordsFile, word)) {
            int value = 1;
            for (char c : word){
                value*= (int(c) - 96);
            }
            string str = word;
            values.insert(std::pair<string,int>(str, value));
        }
        while(values.size() != 1 && values.size() != 0){
            int flag = 0;
            for (auto itr = values.begin(); itr != values.end(); ++itr){
                if (!(itr != values.begin())){
                    continue;
                }
                if (values.begin()->second == itr->second){
                    if (!(dict.find(values.begin()->first) != dict.end())){
                        dict.insert(std::pair<string,std::vector<std::string>>(values.begin()->first, {itr ->first}));
                        dict.insert(std::pair<string,std::vector<std::string>>(itr->first, {values.begin()->first}));
                        flag = 1;
                        values.erase(itr->first);
                        values.erase(values.begin()->first);
                        break;
                    }  
                }
            }
            if (flag == 0){
                dict.insert(std::pair<string,std::vector<std::string>>(values.begin()->first, {}));
                values.erase(values.begin()->first);
            }
        }
        if (values.size()!=0){
            dict.insert(std::pair<string,std::vector<std::string>>(values.begin()->first, {}));
        }
    }
}

/**
 * Constructs an AnagramDict from a vector of words.
 * @param words The vector of strings to be used as source words.
 */
AnagramDict::AnagramDict(const vector<string>& words)
{  
    std::map<string, int> values;
    for (size_t i = 0; i < words.size(); i++){
        int value = 1;
        for (char c : words[i]){
            value*= (int(c) - 96);
        }
        string str = words[i];
        values.insert(std::pair<string,int>(str, value));
    }
    while(values.size() != 1 && values.size() != 0){
        int flag = 0;
        for (auto itr = values.begin(); itr != values.end(); ++itr){
            if (!(itr != values.begin())){
                continue;
            }
            if (values.begin()->second == itr->second){
                if (!(dict.find(values.begin()->first) != dict.end())){
                    dict.insert(std::pair<string,std::vector<std::string>>(values.begin()->first, {itr ->first}));
                    dict.insert(std::pair<string,std::vector<std::string>>(itr->first, {values.begin()->first}));
                    flag = 1;
                    values.erase(itr->first);
                    values.erase(values.begin()->first);
                    break;
                }  
            }
        }
        if (flag == 0){
            dict.insert(std::pair<string,std::vector<std::string>>(values.begin()->first, {}));
            values.erase(values.begin()->first);
        }
    }
    if (values.size()!=0){
        dict.insert(std::pair<string,std::vector<std::string>>(values.begin()->first, {}));
    }
}

/**
 * @param word The word to find anagrams of.
 * @return A vector of strings of anagrams of the given word. Empty
 * vector returned if no anagrams are found or the word is not in the
 * word list.
 */
vector<string> AnagramDict::get_anagrams(const string& word) const
{
    /* Your code goes here! */
    vector <string> result;
    if (dict.find(word) != dict.end()){
        result.push_back(dict.find(word)->second[0]);
        if (dict.find(dict.find(word)->second[0]) != dict.end()){
            result.push_back(dict.find(dict.find(word)->second[0])->second[0]);
        }
        return result;
    }
    else{
        return vector<string>();
    }
    
}

/**
 * @return A vector of vectors of strings. Each inner vector contains
 * the "anagram siblings", i.e. words that are anagrams of one another.
 * NOTE: It is impossible to have one of these vectors have less than
 * two elements, i.e. words with no anagrams are ommitted.
 */
vector<vector<string>> AnagramDict::get_all_anagrams() const
{
    /* Your code goes here! */
    vector<vector<string>> vect;
    vector <string> median;
    for (auto itr = dict.begin(); itr != dict.end(); ++itr){   
        if (dict.find(itr->first) != dict.end() && !dict.find(itr->first)->second.empty()){
            median = get_anagrams(itr->first);
            if (median.empty()){
                continue;
            }
            else{
                vect.push_back(median);
            }
        }
    }
    return vect;
}
