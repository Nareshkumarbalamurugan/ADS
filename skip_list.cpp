#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

template <typename T>
struct Node {
    T value;
    vector<Node*> forward;

    Node(T val, int level) {
        value = val;
        forward.resize(level + 1, nullptr);  // Resizing the forward vector based on the level
    }
};

template <typename T>
class SkipList {
private:
    int maxLevel;
    int level;
    Node<T>* header;

    int randomLevel() {
        int lvl = 0;
        while (rand() % 2 && lvl < maxLevel) {
            lvl++;
        }
        return lvl;
    }

public:
    SkipList(int maxLvl) {
        maxLevel = maxLvl;
        level = 0;
        header = new Node<T>(T(), maxLevel);
    }

    ~SkipList() {
        Node<T>* current = header;
        while (current) {
            Node<T>* next = current->forward[0];
            delete current;
            current = next;
        }
    }

    void insert(T value) {
        vector<Node<T>*> update(maxLevel + 1);
        Node<T>* current = header;

        for (int i = level; i >= 0; i--) {
            while (current->forward[i] && current->forward[i]->value < value) {
                current = current->forward[i];
            }
            update[i] = current;
        }

        int lvl = randomLevel();

        if (lvl > level) {
            for (int i = level + 1; i <= lvl; i++) {
                update[i] = header;
            }
            level = lvl;
        }

        Node<T>* newNode = new Node<T>(value, lvl);

        for (int i = 0; i <= lvl; i++) {
            newNode->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = newNode;
        }
    }

    bool search(T value) {
        Node<T>* current = header;
        for (int i = level; i >= 0; i--) {
            while (current->forward[i] && current->forward[i]->value < value) {
                current = current->forward[i];
            }
        }

        current = current->forward[0];
        return current != nullptr && current->value == value;
    }

    void display() {
        cout << "Skip List: " << endl;
        for (int i = 0; i <= level; i++) {
            Node<T>* current = header->forward[i];
            cout << "Level " << i << ": ";
            while (current) {
                cout << current->value << " ";
                current = current->forward[i];
            }
            cout << endl;
        }
    }
};

int main() {
    srand(time(0));

    SkipList<int> skipList(3);  // Max level of 3

    skipList.insert(10);
    skipList.insert(20);
    skipList.insert(30);
    skipList.insert(40);
    skipList.insert(50);
    skipList.insert(60);

    skipList.display();

    // Search for elements
    cout << "Searching for 30: " << (skipList.search(30) ? "Found" : "Not Found") << endl;
    cout << "Searching for 100: " << (skipList.search(100) ? "Found" : "Not Found") << endl;

    return 0;
}
