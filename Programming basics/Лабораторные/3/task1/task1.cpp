#include <iostream>
using namespace std;
void getNumbers(int& n, int& m) {
	cout << "Введите два числа n и m:\n";
	cin >> n >> m;
}
bool getIsOver() {
	cout << "Продолжить работу? (y/n)";
	char answer; cin >> answer;
	return !(toupper(answer) == 'Y' || toupper(answer) == 'Д');
}
int calculateSum(int n, int m) {
	int sum = 0;
	for (int i = 5; i <= n; i += 5) {
		if (i % m) {
			sum += i;
		}
	}
	return sum;
}
int main() {
	system("chcp 1251 > nul");
	int n, m;
	do {
		getNumbers(n, m);
		if ( !( (n > 0) && (m > 0) ) ) 
			cout << "Вы должны ввести два натуральных числа.\n";
		else
			cout << calculateSum(n, m) << endl;
	} while (!getIsOver());
}