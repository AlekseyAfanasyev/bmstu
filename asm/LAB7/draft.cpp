#include <iostream>
#include <cmath>
#include <bitset>
using namespace std;
int main() {
    string hex;
    cout << "Enter hex number (HHHH):\n";
    cin >> hex;
    int num = 0;
    for (int i = 3; i + 1; --i) {
        if (isdigit(hex[i])) {
            hex[i] -= '0';
        } else {
            hex[i] -= 'A';
            hex[i] += 10;
        }
        num = num + (hex[i] * (int)pow(16, 3 - i));
    }

    cout << "Decimal: ";
    cout << num << endl;
    cout << (num & 2);
    string bin = bitset<16>(num).to_string();
    cout << "Binary: ";
    cout << bin << endl;
    string newHex;
    for (int i = 0; i < 4; ++i) {
        bin = bitset<16>(num).to_string();
        string curDigitBin = bin.substr(12, 15);
        int curDigitDec = 0;
        for (int j = 0; j < 4; ++j) {
            curDigitDec += (curDigitBin[j] == '1')*pow(2, 3-j);
        }
        char curDigitHex;
        if (curDigitDec < 10) {
            curDigitHex = curDigitDec + '0';
        } else {
            curDigitHex = curDigitDec + 'A' - 10;
        }
        newHex = curDigitHex + newHex;
        num = num >> 4;

    }
    cout << "Hex: ";
    cout << newHex << endl;

}
