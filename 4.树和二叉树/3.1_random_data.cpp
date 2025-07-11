#include <iostream>
#include <cstdlib>
using namespace std;
int main() {
    srand(time(0));
    cout << "26" << endl;
    for (int i = 0; i < 26; i++) {
        printf("%c %d\n", 'a' + i, rand() % 100000);
    }
}