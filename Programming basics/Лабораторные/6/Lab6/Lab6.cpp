#include <iostream>
#include <string>
#include <iomanip>
#include <conio.h>
#include <cmath>
using namespace std;

typedef double (*TPF)(double);
struct I_print {	//данные для печати результатов интегрирования
	char* name;//название функции
	double i_sum;	//значение интегральной суммы
	double i_toch;	//точное значение интеграла
	int n;	//число разбиений области интегрирования 
			//при котором достигнута требуемая точность
};
double f1(double x) { return x; }
double f2(double x) { return sin(22 * x); };
double f3(double x) { return x * x * x * x; };
double f4(double x) { return atan(x); };
double f5(double x) { return cos(x); }

double eps = 0.1, a = -1, b = 3;
int n = 2, startingN = 2;
char* funcNames[] = { (char *)"x", (char*)"sin(22x)", (char*)"x^4", (char*)"atan(x)", (char*)"cos(x)"};
TPF funcs[] = { f1, f2, f3, f4, f5 };

double getRightInt(TPF f) {
	if (f == f1)
		return (b * b - a * a) / 2.0;
	else if (f == f2)
		return (cos(a * 22.0) - cos(b * 22.0)) / 22.0;
	else if (f == f3)
		return (b * b * b * b * b - a * a * a * a * a) / 5.0;
	else if (f == f4)
		return b * atan(b) - a * atan(a) - (log(b * b + 1) - log(a * a + 1)) / 2.0;
	else if (f == f5)
		return sin(b) - sin(a);
}
double intRect(TPF f, int n) {
	double s = s = (f(a) + f(b)) / 2;
	double dx = (b - a) / static_cast<double>(n);
	for (int i = 1; i <= n - 1; ++i) {
		s += f(a + i * dx);
	}
	return s * dx;
}
double intTrap(TPF f, int n) {
	double dy = (b - a) / n;
	double y = f(a) + f(b);
	for (int i = 1; i < n; i++) { y += 2 * (f(a + dy * i)); }
	double In = ((b - a) / (2 * n) * y);
	return In;
}
double getInt(TPF f, double (*searchType) (TPF, int)) {
	while (abs(searchType(f, n * 2) - searchType(f, n)) / 3.0 > eps)
		n *= 2;
	return searchType(f, n * 2); 
}

void PrintTabl(I_print i_prn[], int k)
{
	system("chcp 866>nul");
	const int m = 4;//число столбцов таблицы
	int wn[m] = { 12,18,18,10 };//ширина столбцов таблицы
	char* title[m] = { (char*)"Function",(char*)"Integral",(char*)"IntSum",(char*)"N " };
	int size[m];
	for (int i = 0; i < m; i++)
		size[i] = strlen(title[i]);
	//шапка таблицы
	cout << char(218) << setfill(char(196));
	for (int j = 0; j < m - 1; j++)
		cout << setw(wn[j]) << char(194);
	cout << setw(wn[m - 1]) << char(191) << endl;

	cout << char(179);
	for (int j = 0; j < m; j++)
		cout << setw((wn[j] - size[j]) / 2) << setfill(' ') << ' ' << title[j]
		<< setw((wn[j] - size[j]) / 2) << char(179);
	cout << endl;
	for (int i = 0; i < k; i++)	
	{//заполнение таблицы
		cout << char(195) << fixed;
		for (int j = 0; j < m - 1; j++)
			cout << setfill(char(196)) << setw(wn[j]) << char(197);

		cout << setw(wn[m - 1]) << char(180) << setfill(' ') << endl;

		int field_l = ((wn[0] - strlen(i_prn[i].name)) / 2);

		cout << char(179) << setw((wn[0] - strlen(i_prn[i].name)) / 2) << ' ' << i_prn[i].name << setw((wn[0] - strlen(i_prn[i].name)) / 2);
		if ((wn[0] - strlen(i_prn[i].name)) % 2)
			cout << ' ';
		cout << char(179);

		cout << setw(wn[1] - 1) << setprecision(10) << i_prn[i].i_toch << char(179)
			<< setw(wn[2] - 1) << i_prn[i].i_sum << char(179)
			<< setw(wn[3] - 1) << i_prn[i].n << char(179) << endl;
	}
	//низ таблицы
	cout << char(192) << setfill(char(196));
	for (int j = 0; j < m - 1; j++)
		cout << setw(wn[j]) << char(193);
	cout << setw(wn[m - 1]) << char(217) << endl;
	//восстановление первоначальных значений 
	cout << setprecision(6) << setfill(' ');
	system("chcp 1251>nul");
}
void printIntResults(double (*searchType) (TPF, int)) {
	cout << "Область интегрирования функций: " << a << " <= x <= " << b << endl;
	cout << "Точность вычисления: " << eps << endl;
	I_print results[5];
	for (int i = 0; i < 5; ++i) {
		I_print p;
		p.name = funcNames[i];
		p.i_toch = getRightInt(funcs[i]);
		p.i_sum = getInt(funcs[i], searchType);
		p.n = n;
		n = startingN;
		results[i] = p;
	}
	PrintTabl(results, 5);
	while (!_kbhit());
}
short menu() {
	cout << "======================Menu=======================" << endl;
	cout << "| 1 - Вычислить интеграл методом прямоугольника |" << endl;
	cout << "| 2 - Вычислить интеграл методом трапеции       |" << endl;
	cout << "| 3 - Ввести значение eps                       |" << endl;
	cout << "| 4 - Ввести границы вычислений (a, b)          |" << endl;
	cout << "| 5 - Задать начальную точность n               |" << endl;
	cout << "| 6 - Выход                                     |" << endl;
	cout << "=================================================" << endl;
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
void getEps() {
	cout << "Выберите точность вычислений(eps)" << endl;
	cout << "Текущее значение: " << eps << endl;
	cin >> eps;
	if (eps <= 0)
		eps = 0.000001;
}
void getAB() {
	cout << "Введите a и b через пробел:" << endl;
	cin >> a >> b;
	if (a > b)
		swap(a, b);
}
void getN() {
	cout << "Введите n > 1:" << endl;
	cin >> startingN;
	if (startingN < 2) {
		cout << "Введено некорректное значение n." << endl;
		cout << "Используется n = 2" << endl;
		startingN = 2;
	}
}
void showWrongKeyPressed() {
	cout << "Wrong key pressed" << endl;
	cout << "Press any key to continue" << endl;
	while (!_kbhit());
}
void setupOutput() {
	system("chcp 1251 > nul");
	cout << fixed << showpoint;
}

int main () {
	setupOutput();

	while (true) {
		short choice = menu();
		system("cls");
		switch (choice)
		{
		case 1:
			printIntResults(intRect);
			break;
		case 2:
			printIntResults(intTrap);
			break;
		case 3:
			getEps();
			break;
		case 4:
			getAB();
			break;
		case 5:
			getN();
			break;
		case 6:
			return 0;
		default:
			showWrongKeyPressed();
		}
		system("cls");
	}
}	
