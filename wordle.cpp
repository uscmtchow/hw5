// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void generate(const std::string& org_, std::string& word_, std::string& float_, const std::set<std::string>& dict, std::set<std::string>& valids, unsigned int pos);
unsigned int length(string& word_);
void find_float(const std::string& org_, string& word_, string& float_);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    std::string word_(in);
    std::string float_(floating);
    std::set<std::string> valids;

    generate(in, word_, float_, dict, valids, 0);
    return valids;
}

// Define any helper functions here
void generate(const std::string& org_, std::string& word_, std::string& float_, const std::set<std::string>& dict, std::set<std::string>& valids, unsigned int pos) {
    if (length(word_) == word_.size()) {
        if (dict.find(word_) != dict.end()) {
            valids.insert(word_);
        }
        return;
    }
    for (unsigned int i = pos; i < word_.size(); i++) {
        if (word_[i] == '-') {
            std::string temp(word_.substr(i));
            unsigned int empty = temp.size() - length(temp);
            temp.clear();
            temp = float_;

            find_float(org_, word_, temp);
            if (empty <= temp.size()) {
                for (unsigned int j = 0; j < temp.size(); j++) {
                    word_[i] = temp[j];
                    generate(org_, word_, float_, dict, valids, i+1);
                    word_[i] = '-';
                }
                return;
            }
        }
        else {
            generate(org_, word_, float_, dict, valids, i+1);
            return;
        }
    }
}

unsigned int length(string& word_) {
    unsigned int l = 0;
    for (unsigned int i = 0; i < word_.size(); i++) {
        if (word_[i] == '-') continue;
        l++;
    }
    return l;
}

void find_float(const std::string& org_, string& word_, string& float_) {
    for (unsigned int i = 0; i <org_.size(); i++) {
        if (org_[i] == '-') {
            if (float_.find(word_[i]) != float_.npos) float_.erase(float_.find(word_[i], 1));
        }
    }
}