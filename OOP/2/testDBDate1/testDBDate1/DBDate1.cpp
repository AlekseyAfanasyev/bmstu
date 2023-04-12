#include "dbmsLib1.h"
using namespace dbmsLib;

const int DBDate1::arrDays[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

DBDate1::DBDate1(string date) {
	std::stringstream s(date);
	char sep;
	s >> day >> sep >> month >> sep >> year;

	makeCorrectDate(*this);
}

int DBDate1::GetDaysInMonth(int month, int year) {
	return (month == 2) * IsLeapYear(year) + arrDays[month];
}

int DBDate1::DaysInCurYear() {
	int sum = day;
	for (int m = 1; m < month; ++m) {
		sum += GetDaysInMonth(m, year);
	}
	return sum;
}

bool DBDate1::operator==(DBDate1& date) {
	return (day == date.day) && (month == date.month) && (year == date.year);
}

bool DBDate1::operator<(DBDate1& date) {
	return (year < date.year) || (year == date.year && month < date.month) || \
		(year == date.year && month == date.month && day < date.day);
}

bool DBDate1::operator>(DBDate1& date) {
	return (year > date.year) || (year == date.year && month > date.month) || \
		(year == date.year && month == date.month && day > date.day);
}

bool DBDate1::operator<=(DBDate1& date) {
	return (*this == date) || (*this < date);
}

bool DBDate1::operator>=(DBDate1& date) {
	return (*this == date) || (*this > date);
}

bool DBDate1::operator!=(DBDate1& date) {
	return !(*this == date);
}

DBDate1& DBDate1::operator+=(int days) {
	day += days;
	while (day > GetDaysInMonth(month, year)) {
		day -= GetDaysInMonth(month, year);
		++month;
		if (month == 13) {
			++year;
			month = 1;
		}
	}
	return *this;
}//Прибавляет к текущей дате days дней
DBDate1& DBDate1::operator-=(int days) {
	day -= days;
	while (day <= 0) {
		day += GetDaysInMonth(month, year);
		--month;
		if (!month) {
			--year;
			month = 12;
		}
	}
	return *this;
}//Вычитает из текущей даты days дней

int DBDate1::DaysUntilNextMonth(DBDate1 date) {
	return GetDaysInMonth(date.month, date.year) - date.day + 1;
}
int DBDate1::DaysUntilNextYear(DBDate1 date) {
	int dif = DaysUntilNextMonth(date);
	for (int i = date.month + 1; i != 13; ++i) {
		dif += GetDaysInMonth(i, date.year);
	}
	return dif;
}
int DBDate1::DaysUntilMonth(DBDate1 date, int month) {
	if (date.month == month)
		return 0;
	if (date.month > month) {
		int dif = DaysUntilNextYear(date);
		for (int i = 1; i < month; ++i) {
			dif += GetDaysInMonth(i, date.year + 1);
		}
		return dif;
	}
	else {
		int dif = DaysUntilNextMonth(date);
		for (int i = date.month + 1; i != month; ++i) {
			dif += GetDaysInMonth(i, date.year);
		}
		return dif;
	}
}
int DBDate1::DaysUntilYear(DBDate1 date, int year) {
	if (date.year == year)
		return 0;
	int dif = DaysUntilNextYear(date);
	for (int i = date.year + 1; i < year; ++i) {
		dif += 365 + IsLeapYear(i);
	}
	return dif;
}
int DBDate1::operator-(DBDate1& date) {
	DBDate1 min, max;
	if (*this == date)
		return 0;
	else if (*this < date) {
		min = *this; max = date;
	} else if (*this > date) {
		min = date; max = *this;
	}

	int dif;
	if (min.year == max.year) {
		if (min.month == max.month) {
			dif = max.day - min.day;
		}
		else {
			dif = DaysUntilMonth(min, max.month) + max.day - 1;
		}
	} else {
		dif = DaysUntilYear(min, max.year) + DaysUntilMonth(DBDate1(1, 1, max.year), max.month) + max.day - 1;
	}
	return (*this < date ? -dif : dif);
}	//Количество дней между текущей датой и date
							//Если текущая дата > date, результат < 0.

bool DBDate1::isCorrectDate(DBDate1 date) {
	return !(date.day < 0 || date.month < 0 || date.year < 0) &&
		!(date.month > 13 || date.day > GetDaysInMonth(date.month, date.year));
}

void DBDate1::makeCorrectDate(DBDate1& date) {
	if (!isCorrectDate(date)) {
		date = DBDate1(0, 0, 0);
	}
}