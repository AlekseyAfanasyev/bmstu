#pragma once
//dbmsLib_v2_1
#pragma once
#pragma warning(disable : 4996)
#ifndef _dbmsLib1_
#define _dbmsLib1_
#include <iostream>
#include <fstream>
#include <strstream>
#include <iomanip>
#include <string>
#include <vector>
#include <map>
#include <sstream>

using namespace std;

namespace dbmsLib1
{
	//Condition-перечисление условий, по которым могут сравниваться поля таблиц БД:
	enum Condition { Undefined, Equal, NotEqual, Less, Greater, LessOrEqual, GreaterOrEqual };

	//DBType-перечисление типов полей таблиц БД:
	enum DBType { NoType, Int32, Double, String, DBDate };

	const int LENGTH1 = 24;//длина имени таблицы и имени столбца.

	//ColumnDesc - описание данных в столбце таблицы 
	//данные типа string имеют одинаковую длину (length) внутри одного столбца, 
	//но в разных столбцах их длина может отличаться
	struct ColumnDesc {
		char colName[LENGTH1];//имя столбца
		DBType colType;//тип данных в столбце таблицы
		int length; //максимальное число символов, допустимое 
		//для представления данных в столбце
	};

	struct Strip {//полоса распечатки таблицы
		int nField;//число полей 
		int* fieldWidth;//ширина полей в полосе (массив)
	};
	typedef map<string, void*> Row;
	typedef map<string, ColumnDesc> Header;


	//================================== DBDate =======================================
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

		int GetDay() { return day; };
		int GetMonth() { return month; };
		int GetYear() { return year; };
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



	//===================================== DbTable =========================================
	class DBTable1 {
	public:
		DBType GetType1(string columnName);
		const char* TypeName1(DBType type);
		virtual ~DBTable1() {};
		virtual string valueToString1(Row& row, string columnName) = 0;

		//----------------------------------------------
		virtual void ReadDBTable1(string  fileName) = 0; 			//fileName="..\\"+dbName+"\\"+tableName+".bin"|".txt"	
		virtual void WriteDBTable1(string fileName) = 0;
		virtual void PrintTable1(int screenWidth) = 0;
		//----------------------------------------------
	};


	//================================= DBTableTxt ======================================
	class DBTableTxt1 :public DBTable1 {
	private:
		Header columnHeaders;
		string tableName;
		string primaryKey;
		vector<Row> data;
		string fileName;
	public:
		DBTableTxt1() {}
		DBTableTxt1(string tabName)
		{
			tableName = tabName;
		}
		DBTableTxt1(string tabName, Header hdr, string primKey); 	/*:DBTable(tabName,hdr,primKey){}*/
		~DBTableTxt1() {};//!!!деструктор перегружен, чтобы память, выделенная void*, не утекала
		string valueToString1(Row& row, string columnName) override;
		string ignoreBlanc(const string str);

		//------------------------------------------------------------
		void ReadDBTable1(string fileName) override;
		void PrintTable1(int screenWidth) override;
		void WriteDBTable1(string fileName) override;//tabName=path+tableName
		//------------------------------------------------------------
		void WriteTableBin1(string fileName);
		void ReadTableBin1(string fileName);
		//------------------------------------------------------------
		int GetSize1();
		Row GetRow(int index);
		void CreateTableMaket(Strip*& strips, int& nStrips, int screenWidth);

	};


	//=============================== DBTableBin ========================================
	class DBTableBin1 : public DBTable1 {
		char tabName[LENGTH1];
		char primaryKey[LENGTH1];//имя столбца со значениями первичного ключа
	public:
		DBTableBin1() {}
		DBTableBin1(string tableName) {}
		//DBTableBin8(string tableName,Header GetHeader(),string primKey);		
		~DBTableBin1()
		{
			cout << "~DBTableBin()" << endl;
		}

		string valueToString1(Row& row, string columnName) override;

		//---------------------------------------------------------------------------------
		void ReadDBTable1(string fileName) override;//fileName="..\\"+dbName+"\\"+tableName+".bin"											
		void WriteDBTable1(string fileName) override;
		void PrintTable1(int screenWidth) override;
		//---------------------------------------------------------------------------------

	};


	//============================== DBTableSet =======================================
	class DBTableSet1 {
	private:
		string dbName;
		map<string, DBTable1*> db;
	public:
		DBTableSet1() {};
		DBTableSet1(string name);
		void ReadDB1();
		void PrintDB1(int screenWidth);
		void WriteDB1();
		string GetDBName1() { return dbName; }
		DBTableSet1* operator[](string tableName);
	};
}

#endif //конец _dbmsLib1_