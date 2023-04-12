#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <conio.h>

using namespace std;
typedef enum { FIXED, SCIENTIFIC } FORMAT;
const int SCREEN_SIZE = 100;

double** getMatrixRule2(int N) {
	double** arr = new double* [N];

	//инициализация первого ряда
	arr[0] = new double[N];
	arr[0][0] = 1;
	for (int i = 1; i < N; ++i) {
		arr[0][i] = arr[0][i - 1] / double(i + 1);
	}

	//заполнение остальных
	for (int i = 1; i < N; ++i) {
		arr[i] = new double[N];
		for (int j = 0; j < N; ++j) {
			if (i == j) {
				arr[i][j] = 1.;
			}
			else if (j > i) {
				arr[i][j] = arr[i - 1][j] * arr[0][j];
			}
			else if (i > j) {
				if (i - 1 == j && j != 0) {
					arr[i][j] = arr[i - 2][j] * arr[0][j] * arr[0][j];
				}
				else
					arr[i][j] = abs(arr[i - 1][j] * arr[0][j]);
				if (i % 2 == 0)
					arr[i][j] *= -1;
			}
		}
	}
	return arr;
}

double** getMatrixRule1(int N, int M) {
	double** arr = new double* [N];
	for (int row = 0; row < N; ++row) {
		arr[row] = new double[M];
		arr[row][0] = row * M + 1;
		for (int col = 1; col < M; ++col) {
			arr[row][col] = arr[row][col - 1] + 1;
		}
	}
	return arr;
}

template <typename T>
void printArray(T** arr, int N, int M, int n, FORMAT f) {
	int field_l;

	switch (f) {
	case FIXED:
		cout << fixed;
		field_l = to_string(static_cast<int>(arr[N - 1][M - 1])).size() + 2 + n;
		break;
	case SCIENTIFIC:
		cout << scientific;
		field_l = n + 10;
		break;
	}
	cout.precision(n);
	int rows_per_screen = floor(80.0 / (field_l + 2));
	int start = 0;

	while (start < M) {
		for (int j = start; j < min(M, start + rows_per_screen); ++j) {
			cout << setw(field_l) << j+1 << "  ";
		}
		cout << endl;
		for (int i = 0; i < N; ++i) {
			for (int j = start; j < min(M, start + rows_per_screen); ++j) {
				cout << setw(field_l) << arr[i][j] << "  ";
			}
			cout << endl;
		}

		start += rows_per_screen;
	}

}
short menu() {
	cout << "=========================Menu=========================" << endl;
	cout << "| 1 - Вывести массив                                 |" << endl;
	cout << "| 2 - Вывести матрицу(2.2)                           |" << endl;
	cout << "| 3 - Задать точность                                |" << endl;
	cout << "| 4 - Задать формат вывода                           |" << endl;
	cout << "| 5 - Контрольные вопросы                            |" << endl;
	cout << "| 6 - Выход                                          |" << endl;
	cout << "======================================================" << endl;
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
	system("chcp 1251 > nul");
	FORMAT f = SCIENTIFIC;
	int n = 5, N = 10, M = 10;
	double** arr = nullptr;
	
	while (true) {
		short choice = menu();
		system("cls");
		switch (choice) {
		case 1:
			cout << "Введите два числа N, M через пробел." << endl;
			cin >> N >> M;
			if ((N <= 0) || (M <= 0)) {
				cout << "Введены некорректные данные." << endl;
				cout << "Будут использоваться N = 10 и M = 10" << endl;
				N = M = 10;
			}
			arr = getMatrixRule1(N, M);
			printArray(arr, N, M, n, f);
			for (int i = 0; i < N; ++i)
				delete[] arr[i];
			delete[] arr;
			cout << "Нажмите любую клавишу для продолжения" << endl;
			while (!_kbhit());
			break;
		case 2:
			cout << "Введите число N." << endl;
			cin >> N;
			if ((N <= 0) || (M <= 0)) {
				cout << "Введены некорректные данные." << endl;
				cout << "Будет использоваться N = 10" << endl;
				N = 10;
			}
			arr = getMatrixRule2(N);
			printArray(arr, N, N, n, f);
			for (int i = 0; i < N; ++i)
				delete[] arr[i];
			delete[] arr;
			while (!_kbhit());
			break;
		case 3:
			cout << "Введите количество знаков после запятой для вывода" << endl;
			cin >> n;
			if (n <= 0) {
				cout << "Введены некорректные данные." << endl;
				cout << "Будет использоваться n = 5" << endl;
				cout << "Нажмите любую клавишу для продолжения" << endl;
				n = 5;
				while (!_kbhit());
			}
			break;
		case 4:
			cout << "Выберите формат вывода:" << endl;
			cout << "0 - fixed" << endl;
			cout << "1 - scientific" << endl;
			short int temp_f; cin >> temp_f;
			if ((temp_f < 0) || (temp_f > 1)) {
				cout << "Введены некорректные данные." << endl;
				cout << "Будет использоваться формат fixed." << endl;
				cout << "Нажмите любую клавишу для продолжения" << endl;
				temp_f = 0;
				while (!_kbhit());
			}
			f = static_cast <FORMAT> (temp_f);
			break;
		case 5:
			int B[10][10];
			cout << B << endl;
			cout << B + 2 << endl;
			cout << B[0] + 1 << endl;
			while (!_kbhit());
			break;
		case 6:
			return 0;
		default:
			cout << "Некорректная операция." << endl;
			cout << "Для продолжения нажмите любую клавишу" << endl;
			while (!_kbhit());
		}
		system("cls");
	}
}