#include <iostream>
#include <bitset>
using namespace std;

class BinaryCounter {
private:
    int value;
    int totalCost;

public:
    BinaryCounter() {
        value = 0;
        totalCost = 0;
    }

    void increment() {
        int cost = 0;
        int temp = value;
        while (temp % 2 == 1) {
            cost++;
            temp /= 2;
        }
        cost++;
        value++;

        totalCost += cost;
        cout << "Current value (binary): " << std::bitset<8>(value) << " | Cost: " << cost << endl;
    }

    void getTotalCost() {
        cout << "Total cost after all increments: " << totalCost << endl;
    }
};

int main() {
    BinaryCounter counter;

    for (int i = 0; i < 20; i++) {
        counter.increment();
    }

    counter.getTotalCost();
    return 0;
}
