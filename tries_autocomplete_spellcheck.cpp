#include<iostream>
#include<vector>
using namespace std;

class trieNode {
public:
    bool isEndOfWord;
    trieNode* children[26];

    trieNode() {
        isEndOfWord = false;
        for (int i = 0; i < 26; i++) {
            children[i] = NULL;
        }
    }
};

class trie {
public:
    trieNode* root;

    trie() {
        root = new trieNode();
    }

    void insert(string word) {
        trieNode* current = root;
        for (char c : word) {
            int index = c - 'a';
            if (current->children[index] == NULL) {
                current->children[index] = new trieNode();
            }
            current = current->children[index];
        }
        current->isEndOfWord = true;
    }

    bool search(string word) {
        trieNode* current = root;
        for (char c : word) {
            int index = c - 'a';
            if (current->children[index] == NULL) {
                return false;
            }
            current = current->children[index];
        }
        return current->isEndOfWord;
    }

    void findWordsWithPrefix(trieNode* current, string prefix, vector<string>& results) {
        if (current->isEndOfWord) {
            results.push_back(prefix);
        }
        for (int i = 0; i < 26; i++) {
            if (current->children[i] != NULL) {
                findWordsWithPrefix(current->children[i], prefix + char(i + 'a'), results);
            }
        }
    }

    vector<string> autoComplete(string prefix) {
        vector<string> results;
        trieNode* current = root;

        for (char c : prefix) {
            int index = c - 'a';
            if (current->children[index] == NULL) {
                return results;
            }
            current = current->children[index];
        }

        findWordsWithPrefix(current, prefix, results);
        return results;
    }
};

int main() {
    trie words;
    words.insert("hello");
    words.insert("hi");
    words.insert("how");
    words.insert("hope");
    words.insert("hero");
    words.insert("her");

    string word;
    cout << "Enter a word to check spelling: ";
    cin >> word;

    if (words.search(word)) {
        cout << "The word '" << word << "' is correct!" << endl;
    } else {
        cout << "The word '" << word << "' is incorrect!" << endl;
        vector<string> suggestions = words.autoComplete(word);
        if (!suggestions.empty()) {
            cout << "Did you mean?" << endl;
            for (const string& suggestion : suggestions) {
                cout << suggestion << endl;
            }
        } else {
            cout << "No suggestions found." << endl;
        }
    }

    return 0;
}
