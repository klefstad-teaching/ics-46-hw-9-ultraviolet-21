#include "ladder.h"
#include <fstream>
#include <unordered_set>

using namespace std;

void error(string word1, string word2, string msg) {
    cout << msg << "No path from " << word1 << " to " << word2 << endl;
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {
    return levenshtein(str1, str2) <= d;
}

int levenshtein(const string& word1, const string& word2) {
    int m = word1.length();
    int n = word2.length();
    
    if (m == 0) return n;
    if (n == 0) return m;

    // Use two vectors to store current and previous rows
    vector<int> prevRow(n + 1, 0);
    vector<int> currRow(n + 1, 0);

    for (int j = 0; j <= n; ++j) {
        prevRow[j] = j;
    }

    for (int i = 1; i <= m; ++i) {
        currRow[0] = i; 
        
        for (int j = 1; j <= n; ++j) {
            if (word1[i - 1] == word2[j - 1]) {
                currRow[j] = prevRow[j - 1]; 
            } else {
                int insert = currRow[j - 1]; 
                int remove = prevRow[j]; 
                int replace = prevRow[j - 1]; 
                currRow[j] = 1 + min(insert, min(remove, replace));
            }
        }
        swap(prevRow, currRow);
    }

    return prevRow[n];
}

bool is_adjacent(const string& word1, const string& word2) {
    //return edit_distance_within(word1, word2, 1);
    if (word1 == word2) return true;
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

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    vector<string> result;
    if (word_list.find(end_word) == word_list.end()) {
        error(begin_word, end_word, "Error: ");
        return result;
    } // no solution

    queue<vector<string>> q;
    q.push({begin_word});

    unordered_set<string> visited;
    visited.insert(begin_word);

    while (!q.empty()) {
        int size = q.size();
        set<string> current_level_visited;

        for (int i = 0; i < size; ++i) {
            vector<string> current_path = q.front();
            q.pop();
            string current_word = current_path.back();

            for ( auto next_word: word_list) {
                if (visited.find(next_word) == visited.end() && is_adjacent(current_word, next_word)) {
                
                    //make sure current_word != next_word
                    if (next_word == end_word) {
                        current_path.push_back(next_word);
                        return current_path; 
                    }
                    else {
                        current_path.push_back(next_word);
                        q.push(current_path);
                        current_path.pop_back();
                        current_level_visited.insert(next_word);
                    }
            }
        }

    }
        for (const string& word : current_level_visited) {
            visited.insert(word);
        }

    }
    return result;
}

void load_words(set<string>& word_list, const string& file_name) {
    ifstream in(file_name);
    string word;
    while (in >> word) {
        word_list.insert(word);
    }
}

void print_word_ladder(const vector<string>& ladder) {
    if (!ladder.empty()) {
    cout << "Word ladder found: ";
    for (const auto& word: ladder) {
        cout << word << " ";
    }
    cout << endl;
    }
    else {
        cout << "No word ladder found." << endl;
    }
}

#define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}

void verify_word_ladder() {
 set<string> word_list;

    load_words(word_list, "words.txt");

    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);

    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);

    //my_assert(generate_word_ladder("code", "data", word_list).size() == 6);

    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);

    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);

    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
}