#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <random>
#include <conio.h>
#include "../../lib/labFunc.h"

using namespace std;

int arraySize = 10;
short arrayType = 0;
string names[3] = {"Name1", "Name2", "Name3"};
int (*cmpType) (Student, Student);
int (*compare) (Student, Student) = compareNames;
int reverseCompare(Student a, Student b) {
	return -((*cmpType)(a, b));
}

Student getRandomStudent() {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dName(0, 2);
	std::uniform_int_distribution<> dID(0, 9);
	std::uniform_int_distribution<> dDay(1, 31);
	std::uniform_int_distribution<> dMonth(1, 12);
	std::uniform_int_distribution<> dYear(1900, 2021);
	Student s =  { names[dName(gen)], {dDay(gen), dMonth(gen), dYear(gen)}, ""};
	for (int i = 0; i < 8; ++i)
		s.id[i] = dID(gen) + '0';
	return s;
}

vector <Student> getRandomVector() {
	vector <Student> v;
	for (int i = 0; i < arraySize; ++i) {
		v.push_back(getRandomStudent());
	}

	switch (arrayType) {
	case 1:
		v = doMinElSort(v, compare).vec;
		v.push_back(v[0]);
		v.erase(v.begin());
		break;
	case 2:
		if (compare == cmpType)
			v = doMinElSort(v, reverseCompare).vec;
		else
			v = doMinElSort(v, cmpType).vec;
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

void inputCompareType() {
	cout << "Введите параметр для сравнения" << endl;
	cout << "1 - name по возрастанию" << endl;
	cout << "2 - birthDay по убыванию" << endl;
	cout << "3 - id по возрастанию" << endl;
	short choice; cin >> choice;
	if (choice <= 0 || choice > 3)
		choice = 1;
	switch (choice) {
	case 1:
		cmpType = compareNames;
		compare = cmpType;
		break;
	case 2:
		cmpType = compareBirthDays;
		compare = reverseCompare;
		break;
	case 3:
		cmpType = compareIds;
		compare = cmpType;
		break;
	}
}

short menu() {
	cout << "=========================Menu=========================" << endl;
	cout << "| 1 - Сортировка методом минимального элемента       |" << endl;
	cout << "| 2 - Сортировка пузырьковым методом                 |" << endl;
	cout << "| 3 - Задать количество элементов массива            |" << endl;
	cout << "| 4 - Задать начальное состояние массива             |" << endl;
	cout << "| 5 - Задать параметр для сравнения                  |" << endl;
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

	while (true) {
		short choice = menu();
		system("cls");
		switch (choice) {
		case 1:
			printSortResult(doMinElSort(getRandomVector(), compare));
			break;
		case 2:
			printSortResult(doBubbleSort(getRandomVector(), compare));
			break;
		case 3:
			inputArraySize();
			break;
		case 4:
			inputArrayType();
			break;
		case 5:
			inputCompareType();
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
	return 0;
}