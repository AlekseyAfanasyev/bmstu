#include <iostream>
#include <iomanip>
using namespace std;
bool getIsOver() {
	cout << "Продолжить работу? (y/n)\n";
	char answer; cin >> answer;
	return !(toupper(answer) == 'Y' || toupper(answer) == 'Д');
}
void getNumber(double &a) {
	cout << "Введите число:\n";
	cin >> a;
}
double calculateAnswer(double a) {
	if (a < 0)
		return 28.0;
	else
		return static_cast<double>(147456.0) - a;
};
int main()
{
	system("chcp 1251 > nul");
	cout.precision(6);
	cout << fixed << showpoint;
	double a;
	do {
		getNumber(a);
		cout << calculateAnswer(a) << endl;
	} while (!getIsOver());
}
