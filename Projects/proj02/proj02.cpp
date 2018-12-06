//Created by Chris Nosowsky

#include <iostream>
#include <string>
#include <cmath>
using std::cout;
using std::cin;
using std::endl;

int main() {
    long integer;
    long maxK;
    cout << "";
    cin >> integer;
    cout << "";
    cin >> maxK;
    if (integer < 6 || maxK < 1) {
        cout << 0;
    }
    else {
        long sum = 0;
        int i = 0;
        for (long a = 2; a < std::sqrt(integer); a++) {
            if (integer % a == 0) {
                if ((a == (integer/a))) {
                  sum += a;
                }
                else {
                  sum += a + (integer/a);
                }
            }
        }
        for (long b = 1; b < maxK; b++) {
            if ((sum * b) + 1 == integer) {
                cout << b;
                i = 1;
                break;
            }
        }
        if (i == 0){
          cout << 0;
        }
    }

}
