#include <iostream>
#include <iomanip>
#include <conio.h>
#include <cmath>
#include <vector>

using namespace std;

double k = 10, step = 0.1, eps = 0.000001;
double start = -20, finish = 20;

typedef pair <int, double> root;

template <typename T> int sign(T val) {
	return (T(0) < val) - (val < T(0));
}
int getDoubleLength(double x) {
	return -log10(x);
}
double Function(double x) {
	return x * x + k * x - 1;
}

void getK() {
	cout << "Введите значение для коэффициента k" << endl;
	cout << "Текущее значение: " << k << endl;
	cin >> k;
}
void getEps() {
	cout << "Выберите точность вычислений(eps)" << endl;
	cout << "Текущее значение: " << eps << endl;
	cin >> eps;
	if (eps <= 0)
		eps = 0.1;
}
void getStep() {
	cout << "Введите шаг для поиска интервалов с одним корнем" << endl;
	cout << "Текущее значение: " << step << endl;
	cin >> step;
	if (step <= 0)
		step = 0.1;
}
void getBoarders() {
	cout << "Введите границы для поиска корней через пробел" << endl;
	cout << "Текущее границы: " << start << " - " << finish << endl;
	cin >> start >> finish;
	if (finish < start) {
		swap(start, finish);
	}
}

void printWrongCommand() {
	cout << "Введена некорректная команда." << endl;
	cout << "Для выхода нажмите 6." << endl;
	cout << "(Для продолжения нужно было нажать любую клавишу)" << endl;
	while (!_kbhit());
}

void setupOutput() {
	system("chcp 1251 > nul");
	cout << fixed << showpoint;
}

void printProgressBar(double start, double end) {
	cout << '\r';
	cout << "\x1b[0K";
	cout << "Loading: |";
	int pointsAmount = ((float)(100.0 * (start / end)) / 5.0);
	for (int i = 0; i < pointsAmount; ++i) {
		cout << "#";
	}
	for (int i = pointsAmount; i < 20; ++i)
		cout << " ";
	cout << '|';
}

root calculateRoot(double Xn, double Xk, double (*F) (double)) {
	int step = 1;
	if (!F(Xn))
		return { step, Xn };
	if (!F(Xk))
		return { step, Xk };

	double dx, Xi;
	while (Xk - Xn > eps) {
		++step;
		dx = (Xk - Xn) / 2;
		Xi = Xn + dx;
		if (sign(F(Xn)) != sign(F(Xi)))
			Xk = Xi;
		else
			Xn = Xi;
	}
	return { step, Xi };
}
bool getNextInterval(double& Xn, double& Xk, double (*F) (double)) {
	Xn = Xk;
	Xk = Xn + 2 * eps;
	while (F(Xk) * F(Xn) > 0) {
		Xk += step;
		if (Xk >= finish)
			return false;
	}
	return true;
}
vector <root> solveFunc(double (*F) (double)) {
	vector <root> v;
	double curL = 0, curR = start;
	while (curR <= finish) {
		if (!getNextInterval(curL, curR, F)) {
			printProgressBar(finish, finish);
			return v;
		}
		printProgressBar(curR, finish);
		v.push_back(calculateRoot(curL, curR, F));
	}
	return v;
}
void printFunc(double (*F) (double)) {
	cout << "Расчёт корней функции со следующими параметрами:" << endl;
	cout << "k = " << k << endl;
	cout << setprecision(getDoubleLength(eps)) << "eps = " << eps << endl;
	cout << "Границы: " << start << " - " << finish << endl;
	cout << "Шаг: " << setprecision(getDoubleLength(step)) << step << endl;

	vector <root> funcRoots = solveFunc(F);
	cout << endl;
	if (!funcRoots.size()) {
		cout << "Корни не найдены." << endl;
		return;
	}
	for (auto& i : funcRoots) {
		cout << setprecision(getDoubleLength(eps)) << i.second;
		cout << "(Шаг: " << i.first << " )" << endl;
 	}
	cout << "Итого корней: " << funcRoots.size() << endl;
	cout << "Для продолжения нажмите любую клавишу" << endl;
	while (!_kbhit());
}

short menu() {
	cout << "============Menu============" << endl;
	cout << "| 1 - Ввести значение k    |" << endl;
	cout << "| 2 - Ввести значение eps  |" << endl;
	cout << "| 3 - Ввести границы       |" << endl;
	cout << "| 4 - Вычислить корни      |" << endl;
	cout << "| 5 - Выбрать шаг          |" << endl;
	cout << "| 6 - Выход                |" << endl;
	cout << "============================" << endl;
	cout << "Выберите номер:" << endl;
	int choice;
	cin >> choice;
	while (cin.fail()) {
		cout << "Ошибка ввода. Повторите ввод\n";
		cin.clear();
		cin.ignore(10, '\n');
		cin >> choice;
	}
	return choice;
}

int main() {
	setupOutput();

	while (true) {
		short choice = menu();
		system("cls");

		switch (choice) { 
		case 1:
			getK();
			break;
		case 2:
			getEps();
			break;
		case 3:
			getBoarders();
			break;
		case 4:
			printFunc(Function);
			break;
		case 5:
			getStep();
			break;
		case 6:
			return 0;
		default:
			printWrongCommand();
		}
		system("cls");
	}
}
