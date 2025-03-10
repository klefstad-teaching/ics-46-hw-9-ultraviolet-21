#include "ladder.h"

using namespace std;

int main() {
    set<string> word_list;
    //load_words(word_list, "short_sorted.txt");
    for (const auto& word : word_list) {
        cout << word << " ";
    }
    cout << endl;

    cout << is_adjacent("fan", "fun") << endl;
    verify_word_ladder();
    return 0;
}
