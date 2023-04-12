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
	//Condition-������������ �������, �� ������� ����� ������������ ���� ������ ��:
	enum Condition { Undefined, Equal, NotEqual, Less, Greater, LessOrEqual, GreaterOrEqual };

	//DBType-������������ ����� ����� ������ ��:
	enum DBType { NoType, Int32, Double, String, DBDate };

	const int LENGTH1 = 24;//����� ����� ������� � ����� �������.

	//ColumnDesc - �������� ������ � ������� ������� 
	//������ ���� string ����� ���������� ����� (length) ������ ������ �������, 
	//�� � ������ �������� �� ����� ����� ����������
	struct ColumnDesc {
		char colName[LENGTH1];//��� �������
		DBType colType;//��� ������ � ������� �������
		int length; //������������ ����� ��������, ���������� 
		//��� ������������� ������ � �������
	};

	struct Strip {//������ ���������� �������
		int nField;//����� ����� 
		int* fieldWidth;//������ ����� � ������ (������)
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
		DBDate1(string date);//������ ������: dd.mm.yyyy
		DBDate1(int d, int m, int y) : day(d), month(m), year(y) { makeCorrectDate(*this); }
		DBDate1() :day(0), month(0), year(0) {};//����������� �� ���������
		DBDate1(const DBDate1& dat) :day(dat.day), month(dat.month), year(dat.year) {}

		int GetDay() { return day; };
		int GetMonth() { return month; };
		int GetYear() { return year; };
		bool IsLeapYear(int year) { return (!(year % 4) && (year % 100)) || (!(year % 400)); }; //��� ����������?
		int GetDaysInMonth(int month, int year);//���������� ���� � ������
		int DaysInCurYear();//���������� ���� �� ������ ���� �� ������� ����

		bool operator==(DBDate1& date);
		bool operator<(DBDate1& date);
		bool operator>(DBDate1& date);
		bool operator<= (DBDate1& date);
		bool operator>= (DBDate1& date);
		bool operator!= (DBDate1& date);
		DBDate1& operator+=(int days);//���������� � ������� ���� days ����
		DBDate1& operator-=(int days);//�������� �� ������� ���� days ����
		int operator-(DBDate1& date);	//���������� ���� ����� ������� ����� � date
									//���� ������� ���� > date, ��������� < 0.

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
		~DBTableTxt1() {};//!!!���������� ����������, ����� ������, ���������� void*, �� �������
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
		char primaryKey[LENGTH1];//��� ������� �� ���������� ���������� �����
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

#endif //����� _dbmsLib1_