#include <iostream>
#include <vector>

class BinaryCounter {
private:
    std::vector<bool> counter;

public:
    BinaryCounter(int bits) {
        counter.resize(bits, false);
    }

    void increment() {
        int i = 0;
        while (i < counter.size() && counter[i]) {
            counter[i] = false;
            i++;
        }
        if (i < counter.size()) {
            counter[i] = true;
        }
    }

    void display() {
        for (int i = counter.size() - 1; i >= 0; --i) {
            std::cout << counter[i];
        }
        std::cout << std::endl;
    }
};

int main() {
    BinaryCounter counter(5);

    for (int i = 0; i < 32; ++i) {
        counter.increment();
        counter.display();
    }

    return 0;
}
