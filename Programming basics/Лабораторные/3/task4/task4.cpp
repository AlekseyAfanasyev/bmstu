#include <iostream>
#include <iomanip>
using namespace std;
void getN(int& n) {
    cout << "Введите n:" << endl;
    cin >> n;
    if (n <= 0) {
        cout << "Введено некорректное значение n" << endl;
        cout << "Используется n = 5" << endl;
        n = 5;
    }
};

double Y(double n) {
    double res = 0;
    while (n) {
        res += (2 * n) + 1;
        res = 1.0 / res;
        --n;
    }
    return res;
}

bool getIsOver() {
    cout << "Продолжить работу? (y/n)";
    char answer; cin >> answer;
    return !(toupper(answer) == 'Y');
}
void printValue(int n) {
    cout << "Y(" << n << "): " << Y(n) << endl;
}
void printSteps(int n) {
    if (n > 3) {
        printValue(3);
        if (n > 6) {
            printValue(5);
            if (n > 10) {
                printValue(10);
            }
        }
    }
}
int main()
{
    system("chcp 1251 > nul");
    cout << setprecision(10);

    int n;
    do {        
        getN(n);
        printValue(n);
        printSteps(n);
    } while (!getIsOver());
}