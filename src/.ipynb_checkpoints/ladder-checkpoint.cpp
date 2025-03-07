#include "ladder.h"
#include <fstream>

using namespace std;

void error(string word1, string word2, string msg);

bool edit_distance_within(const std::string& str1, const std::string& str2, int d); //use word ladder for this

bool is_adjacent(const string& word1, const string& word2) {
    return change_letter(word1, word2) || add_letter(word1, word2) || delete_letter(word1, word2);
}

bool change_letter(const string& word1, const string& word2) {
    if (word1.length() != word2.length())
        return false;
  
    int diff = 0;
    int len = word1.length();
    for (int i = 0; i < len; ++i) {
        if (word1[i] != word2[i])
            ++diff;
    }
    return diff == 1;
}

bool add_letter(const string& word1, const string& word2) {
    if (word1.length() + 1 != word2.length()) 
        return false;
    int i = 0, j = 0;
    bool dif = false;
    int len1 = word1.length(), len2 = word2.length();
    while (i < len2 && j < len1) {
        if (word1[j] != word2[i]) {
            if (dif)
                return false;
            dif = true;
            ++i;
        }
        else {
            ++i;
            ++j;
        }
    }
    return true;
}

bool delete_letter(const string& word1, const string& word2) {
    if (word1.length() - 1 != word2.length()) 
        return false;
    int i = 0, j = 0;
    bool dif = false;
    int len1 = word1.length(), len2 = word2.length();
    while (i < len1 && j < len2) {
        if (word1[i] != word2[j]) {
            if (dif)
                return false;
            dif = true;
            ++i;
        }
        else {
            ++i;
            ++j;
        }
    }
    return true;
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list);

void load_words(set<string>& word_list, const string& file_name) {
    ifstream in(file_name);
    string word;
    while (in >> word) {
        word_list.insert(word);
    }
}

void print_word_ladder(const vector<string>& ladder) {
    for (const auto& word: ladder) {
        cout << word << " ";
    }
    cout << endl;
}

void verify_word_ladder();