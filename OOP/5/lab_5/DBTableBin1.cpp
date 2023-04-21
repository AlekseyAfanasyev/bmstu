//DBTableBin1
#include <iostream>
#include <iomanip>
#include "dbmsLib_v2_1.h"
#pragma warning(disable : 4996)
#include <string.h>
#include <fstream>

using namespace dbmsLib1;

string DBTableBin1::valueToString1(Row& row, string columnName) {
	return(columnName);
}
void DBTableBin1::ReadDBTable1(string fileName) {
	cout << "ReadDBTable1 Bin | " << fileName << endl;
}

void DBTableBin1::WriteDBTable1(string fileName)
{
	cout << "WriteDBTable1 Bin | " << fileName << endl;
}

void DBTableBin1::PrintTable1(int screenWidth)
{
	cout << "PrintTable1 Bin | " << endl;
}