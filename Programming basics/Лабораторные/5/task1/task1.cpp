#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <random>
#include <conio.h>
#include "../../lib/labFunc.h"
int arraySize = 10;
short arrayType = 0;
using namespace std;

int compare(int a, int b) {
	if (a > b)
		return 1;
	else if (a == b)
		return 0;
	else
		return -1;
}

vector <int> getRandomVector() {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrib(-10, 10);
	vector <int> v;
	for (int i = 0; i < arraySize; ++i) {
		v.push_back(distrib(gen));
	}

	switch (arrayType) {
	case 1:
		sort(v.begin(), v.end());
		v.push_back(v[0]);
		v.erase(v.begin());
		break;
	case 2:
		sort(v.rbegin(), v.rend());
		v.push_back(v[0]);
		v.erase(v.begin());
		break;
	}
	return v;
}

void inputArraySize() {
	cout << "Введите размер массива." << endl;
	cin >> arraySize;
	if (arraySize <= 0)
		arraySize = 10;
}

void inputArrayType() {
	cout << "Введите тип массива:" << endl;
	cout << "0 - случайное состояние" << endl;
	cout << "1 - отсортированный" << endl;
	cout << "2 - сортировка в обратном порядке" << endl;
	cin >> arrayType;

	if (!((arrayType >= 0) && (arrayType < 3)))
		arrayType = 0;

}
int menu() {
	cout << "=========================Menu=========================" << endl;
	cout << "| 1 - Сортировка методом минимального элемента       |" << endl;
	cout << "| 2 - Сортировка пузырьковым методом                 |" << endl;
	cout << "| 3 - Задать количество элементов массива            |" << endl;
	cout << "| 4 - Задать начальное состояние массива             |" << endl;
	cout << "| 5 - Выход                                          |" << endl;
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
	int (*cmp) (int, int) = compare;

	while (true) {
		switch (menu()) {
		case 1:
			system("cls");
			cout << "Сортировка массива минимального элемента" << endl;
			cout << "Размер массива: " << arraySize << endl;
			printSortResult(doMinElSort(getRandomVector(), cmp));
			system("cls");
			break;	
		case 2:
			system("cls");
			cout << "Сортировка массива методом пузырька" << endl;
			cout << "Размер массива: " << arraySize << endl;
			printSortResult(doBubbleSort(getRandomVector(), cmp));
			system("cls");
			break;
		case 3:
			system("cls");
			inputArraySize();
			system("cls");
			break;
		case 4:
			system("cls");
			inputArrayType();
			system("cls");
			break;
		case 5:
			return 0;
		default:
			cout << "Некорректная операция." << endl;
			cout << "Для выхода нажмите 5." << endl;
			cout << "Для продолжения нажмите любую клавишу" << endl;
			while (!_kbhit());
			system("cls");
		}
	}
	return 0;
}