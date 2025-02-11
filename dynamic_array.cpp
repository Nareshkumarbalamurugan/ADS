#include <iostream>
#include <vector>
using namespace std;

class DynamicArray {
private:
    vector<int> arr;
    int capacity;
    int size;
    int totalCost;

public:
    DynamicArray() {
        capacity = 1;
        size = 0;
        totalCost = 0;
        arr.resize(capacity);
    }

    void insert(int value) {
        int cost = 1;
        if (size == capacity) {
            cost += capacity;
            capacity *= 2;
            vector<int> newArr(capacity);
            for (int i = 0; i < size; i++) {
                newArr[i] = arr[i];
            }
            arr = newArr;
        }

        arr[size++] = value;
        totalCost += cost;
    }

    void display() {
        for (int i = 0; i < size; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }

    void getCost() {
        cout << "Total cost after all insertions: " << totalCost << endl;
    }
};

int main() {
    DynamicArray dynArr;
    dynArr.insert(1);
    dynArr.insert(2);
    dynArr.insert(3);
    dynArr.insert(4);
    dynArr.insert(5);

    dynArr.display();
    dynArr.getCost();
    return 0;
}

                    
