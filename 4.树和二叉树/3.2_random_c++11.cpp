#include <iostream>
#include <random>
using namespace std;
int main() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(1, 100000);
    cout << "26" << endl;
    for (int i = 0; i < 26; i++) {
        cout << char('a' + i ) << " " << dist(gen) << endl;
    }
    return 0;
}