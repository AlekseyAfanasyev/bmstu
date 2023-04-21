//файл dbmsLib.h
#pragma once
#ifndef _dbmsLib_
#define _dbmsLib_
#include <iostream>
#include <fstream>
#include <strstream>
#include <iomanip>
#include <string>
#include <vector>
#include <sstream>
#include <map>

using namespace std;
namespace dbmsLib
{
	//-----------------класс DBDate1----------------------------
	class DBDate1
	{
		static const int arrDays[13];
		friend string DateToStr(DBDate1& date) {
			stringstream ss;
			char sep = '.';
			ss << date.day << sep << date.month << sep << date.year;
			return ss.str();
		};
		friend ostream& operator<<(ostream& out, DBDate1& date) {
			out << DateToStr(date);
			return out;
		};
		int day, month, year;
	public:
		DBDate1(string date);//формат строки: dd.mm.yyyy
		DBDate1(int d, int m, int y) : day(d), month(m), year(y) { makeCorrectDate(*this); }
		DBDate1() :day(0), month(0), year(0) {};//конструктор по умолчанию
		DBDate1(const DBDate1& dat) :day(dat.day), month(dat.month), year(dat.year) {}

		int GetDay() {return day;};
		int GetMonth() { return month; };
		int GetYear() {return year;};
		bool IsLeapYear(int year) { return (!(year % 4) && (year % 100)) || (!(year % 400)); }; //год высокосный?
		int GetDaysInMonth(int month, int year);//Количество дней в месяце
		int DaysInCurYear();//Количество дней от начала года до текущей даты

		bool operator==(DBDate1& date);
		bool operator<(DBDate1& date);
		bool operator>(DBDate1& date);
		bool operator<= (DBDate1& date);
		bool operator>= (DBDate1& date);
		bool operator!= (DBDate1& date);
		DBDate1& operator+=(int days);//Прибавляет к текущей дате days дней
		DBDate1& operator-=(int days);//Вычитает из текущей даты days дней
		int operator-(DBDate1& date);	//Количество дней между текущей датой и date
									//Если текущая дата > date, результат < 0.

	private:
		int DaysUntilNextMonth(DBDate1 date);
		int DaysUntilNextYear(DBDate1 date);
		int DaysUntilMonth(DBDate1 date, int month);
		int DaysUntilYear(DBDate1 date, int year);

		bool isCorrectDate(DBDate1 date);
		void makeCorrectDate(DBDate1& date);
	};
}
#endif