#include <iostream>
#include "ArrayList.h"
using namespace std;

int main() {
    ArrayList<int> num;

    num.add(14);
    num.add(15);
    num.insert(0, 55);

    num.print();

    cout << endl;

    cout << num.pop() << endl;

    num.print();

    return 0;
}