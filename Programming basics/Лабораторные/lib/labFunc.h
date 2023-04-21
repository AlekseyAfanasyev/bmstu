#pragma once
#include <conio.h>
#include <string>
#include <iostream>
#include <conio.h>
#include <vector>
using namespace std;

struct Date {
	int day;
	int month;
	int year;
};
struct Student {
	std::string name;
	Date birthDay;
	char id[8];//номер зачётной книжки
};


template <typename T> struct sortResult {
	vector <T> vec;
	int change;
	int compare;
};

bool operator > (Date a, Date b) {
	return (a.year > b.year) || ((a.year == b.year) && (a.month > b.month)) || \
		((a.year == b.year) && (a.month == b.month) && (a.day > b.day));
}

bool operator == (Date a, Date b) {
	return ((a.day == b.day) && (b.month == a.month) && (b.year == a.year));
}

bool operator < (Date a, Date b) {
	return (!(a == b)) && (!(a > b));
}

int compareNames(struct Student a, struct Student b) {
	return (a.name == b.name ? 0 : (a.name < b.name ? -1 : 1));
}

int compareBirthDays(struct Student a, struct Student b) {
	return (a.birthDay == b.birthDay ? 0 : (a.birthDay < b.birthDay ? -1 : 1));
}

int compareIds(struct Student a, struct Student b) {
	for (int i = 0; i < 8; ++i) {
		if (a.id[i] > b.id[i])
			return 1;
		else if (a.id[i] < b.id[i])
			return 0;
	}
	return 0;
}	

void printProgressBar(double start, double end) {
	cout << '\r';
	cout << "\x1b[0K";
	cout << "Прогресс: " << start << '/' << end;
}




template <typename T> sortResult<T> doMinElSort(std::vector <T> v, \
	int (*cmp) (T, T)) {
	int change = 0, compare = 0;
	int i, j, index;
	int n = static_cast<int>(v.size());
	for (i = 0; i < n; ++i) {
		index = i;
		printProgressBar(i, n - 1);
		for (j = i + 1; j < n; ++j) {
			//v[j] < v[index]
			if (cmp(v[j], v[index]) == -1)
				index = j;
			compare++;
		}

		if (index != i) {
			swap(v[index], v[i]);
			++change;
		}
		++compare;
	}
	return { v, change, compare };
}

template <typename T> sortResult<T> doBubbleSort(std::vector <T> v, \
	int (*cmp)(T, T)) {
	int change = 0, compare = 0, changesAmount;
	int i, j;
	int n = static_cast<int>(v.size());
	for (i = 0; i < n; ++i) {
		printProgressBar(i, n - 1);
		changesAmount = 0;
		for (j = n - 1; j > 0; --j) {
			//v[j] > v[j - 1]
			if (cmp(v[j], v[j - 1]) == -1) {
				swap(v[j], v[j - 1]);
				++changesAmount;
				++change;
			}
			++compare;
		}
		if (!changesAmount) 
			return { v, change, compare };
	}
	return { v, change, compare };
}

template <typename T> void printArray(vector <T> v) {
	for (auto& i : v)
		cout << i << endl;
};

void printStudents(vector <Student> v) {
	for (auto& i : v) {
		cout << i.name << " ";
		auto b = i.birthDay;
		cout << b.day << " " << b.month << " " << b.year << " ";
		cout << i.id << endl << endl;
	}
}	

template <typename T> void printSortResult(sortResult<T> res) {

	cout << endl << "Сортировка завершена." << endl;
	cout << "swap = " << res.change << endl;
	cout << "compare = " << res.compare << endl;
	cout << "Для выхожа нажмите любую клавишу." << endl;
	while (!_kbhit());
}
