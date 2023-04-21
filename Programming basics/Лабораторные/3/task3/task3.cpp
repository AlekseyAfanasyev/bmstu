#define _USE_MATH_DEFINES 
#include <iostream>
#include <iomanip>
#include <math.h>
using namespace std;

//returns S(x) and N
pair <int, double> s(float x, double eps) {
	int n = 1;
	int numerator = 3;
	double last_el = 3 * pow(x, 2);
	double result = 1 + last_el;
	while (last_el >= eps) {
		numerator += 2;
		last_el *= static_cast<double>(numerator) / (static_cast<double>(numerator) * static_cast<double>(n) + 1) * x * x;
		result += last_el;
		++n;
	}
	return { n + 1, result };
}

double y(float x) {
	return (1 + 2 * pow(x, 2)) * pow(M_E, pow(x, 2));
}

void printTable(double eps) {
	int n = 0;
	while (pow(10, -n) != eps) ++n;
	++n;
	string step = "      ";
	int field_l = n + 4;

	//print header
	cout << setw(3) << "x" << step << setw(field_l) << "Y(x)" << step << setw(field_l) <<\
		"S(x)" << step  << setw(3) << "N" << endl;

	//print lines
	const float h = 0.2;
	for (float x = 0; x <= 1; x += h) {
		pair <int, double> s_x = s(x, eps);
		cout << setprecision(1) << setw(3) << x << step;
		cout << setprecision(n) << fixed << setw(field_l) << y(x) << step;
		cout << setw(field_l) << s_x.second << step;
		cout << setw(3) << s_x.first << endl;
	}
}

void getEpsilon(double& eps) {
	cout << "Выберите точность вычислений:" << endl;
	cin >> eps;
	if (eps > 0.01 || eps <= 0) {
		cout << "Введена некорректная погрешность" << endl;
		cout << "Будет использоваться eps = 0.000001" << endl << endl;
		eps = 0.000001;
	}
}

bool getIsOver() {
	cout << "Продолжить работу? (y/n)";
	char answer; cin >> answer;
	return !(toupper(answer) == 'Y' || toupper(answer) == 'Д');
}

int main() {
	system("chcp 1251 > nul");
	double eps;
	do {
		getEpsilon(eps);
		printTable(eps);
	} while (!getIsOver());
}