#include "CSVReaderTest.h"
#include <stdio.h>
#include <string.h>

using namespace std;


/*
 * Linked to test cases 2B1.0->2B1.4
 * Test creation of CustomSort class
 */

void CSVReaderTest::CSVReader_Test_1_Constructor() {
    CSVReader *reader = new CSVReader();
}

void CSVReaderTest::CSVReader_Test_2_loadCSV_Ex1_Teaching() {
    CSVReader *readerTeaching = new CSVReader();
    readerTeaching->loadCSV("../Project Information/Sample Data/Program_Teaching_expanded.csv");
}

void CSVReaderTest::CSVReader_Test_2_loadCSV_Ex2_Presentations() {
    CSVReader *readerTeaching = new CSVReader();
    readerTeaching->loadCSV("../Project Information/Sample Data/Presentations_expanded.csv");
}

void CSVReaderTest::CSVReader_Test_2_loadCSV_Ex3_Publications() {
    CSVReader *readerTeaching = new CSVReader();
    readerTeaching->loadCSV("../Project Information/Sample Data/Publications_expanded.csv");
}

void CSVReaderTest::CSVReader_Test_2_loadCSV_Ex4_Grants() {
    CSVReader *readerTeaching = new CSVReader();
    readerTeaching->loadCSV("../Project Information/Sample Data/Grants_expanded.csv");
}

void CSVReaderTest::CSVReader_Test_3_parseDateString(string testDate, string CSVfile) {
    int year = 2016;
    CSVReader reader(CSVfile);
    int testYear = reader.parseDateString(testDate);
    QCOMPARE(testYear, year);
}

void CSVReaderTest::CSVReader_Test_3_parseDateString_Ex1_year_month_day__Teaching() {
    CSVReader_Test_3_parseDateString("2016/12/25", "../Project Information/Sample Data/Program_Teaching_expanded.csv");
}

void CSVReaderTest::CSVReader_Test_3_parseDateString_Ex2_year_month_day__Presentations() {
    CSVReader_Test_3_parseDateString("2016/12/25", "../Project Information/Sample Data/Presentations_expanded.csv");
}

void CSVReaderTest::CSVReader_Test_3_parseDateString_Ex3_year_month_day__Publications() {
    CSVReader_Test_3_parseDateString("2016/12/25", "../Project Information/Sample Data/Publications_expanded.csv");
}

void CSVReaderTest::CSVReader_Test_3_parseDateString_Ex4_year_month_day__Grants() {
    CSVReader_Test_3_parseDateString("2016/12/25", "../Project Information/Sample Data/Grants_expanded.csv");
}

void CSVReaderTest::CSVReader_Test_3_parseDateString_Ex5_day_month_year__Teaching() {
    CSVReader_Test_3_parseDateString("12/25/2016", "../Project Information/Sample Data/Program_Teaching_expanded.csv");
}

void CSVReaderTest::CSVReader_Test_3_parseDateString_Ex6_day_month_year__Presentations() {
    CSVReader_Test_3_parseDateString("12/25/2016", "../Project Information/Sample Data/Presentations_expanded.csv");
}

void CSVReaderTest::CSVReader_Test_3_parseDateString_Ex7_day_month_year__Publications() {
    CSVReader_Test_3_parseDateString("12/25/2016", "../Project Information/Sample Data/Publications_expanded.csv");
}

void CSVReaderTest::CSVReader_Test_3_parseDateString_Ex8_day_month_year__Grants() {
    CSVReader_Test_3_parseDateString("12/25/2016", "../Project Information/Sample Data/Grants_expanded.csv");
}

void CSVReaderTest::CSVReader_Test_3_parseDateString_Ex9_text_with_date_at_end__Teaching() {
    CSVReader_Test_3_parseDateString("Sept 25th, 2016", "../Project Information/Sample Data/Program_Teaching_expanded.csv");
}

void CSVReaderTest::CSVReader_Test_3_parseDateString_Ex10_text_with_date_at_end__Presentations() {
    CSVReader_Test_3_parseDateString("Sept 25th, 2016", "../Project Information/Sample Data/Presentations_expanded.csv");
}

void CSVReaderTest::CSVReader_Test_3_parseDateString_Ex11_text_with_date_at_end__Publications() {
    CSVReader_Test_3_parseDateString("Sept 25th, 2016", "../Project Information/Sample Data/Publications_expanded.csv");
}

void CSVReaderTest::CSVReader_Test_3_parseDateString_Ex12_text_with_date_at_end__Grants() {
    CSVReader_Test_3_parseDateString("Sept 25th, 2016", "../Project Information/Sample Data/Grants_expanded.csv");
}

void CSVReaderTest::CSVReader_Test_4_getHeaders_count_Ex1_Teaching() {
    CSVReader reader("../Project Information/Sample Data/Program_Teaching_expanded.csv");
    vector<string> header = reader.getHeaders();
    int compare = (int)header.size();
    QCOMPARE(compare, 27);
}

void CSVReaderTest::CSVReader_Test_4_getHeaders_count_Ex2_Presentations() {
    CSVReader reader("../Project Information/Sample Data/Presentations_expanded.csv");
    vector<string> header = reader.getHeaders();
    int compare = (int)header.size();
    QCOMPARE(compare, 25);
}

void CSVReaderTest::CSVReader_Test_4_getHeaders_count_Ex3_Publications() {
    CSVReader reader("../Project Information/Sample Data/Publications_expanded.csv");
    vector<string> header = reader.getHeaders();
    int compare = (int)header.size();
    QCOMPARE(compare, 34);
}

void CSVReaderTest::CSVReader_Test_4_getHeaders_count_Ex4_Grants() {
    CSVReader reader("../Project Information/Sample Data/Grants_expanded.csv");
    vector<string> header = reader.getHeaders();
    int compare = (int)header.size();
    QCOMPARE(compare, 37);
}

void CSVReaderTest::CSVReader_Test_4_getHeaders_confirmLastHeader_Ex1_Teaching() {
    CSVReader reader("../Project Information/Sample Data/Program_Teaching_expanded.csv");
    int comparison=reader.getHeaders().back().compare("Total Hours");
    QCOMPARE(comparison, 0);
}

void CSVReaderTest::CSVReader_Test_4_getHeaders_confirmLastHeader_Ex2_Presentations() {
    CSVReader reader("../Project Information/Sample Data/Presentations_expanded.csv");
    int comparison=reader.getHeaders().back().compare("Personal Remuneration");
    QCOMPARE(comparison, 0);
}

void CSVReaderTest::CSVReader_Test_4_getHeaders_confirmLastHeader_Ex3_Publications() {
    CSVReader reader("../Project Information/Sample Data/Publications_expanded.csv");
    int comparison=reader.getHeaders().back().compare("ISBNISSN");
    QCOMPARE(comparison, 0);
}

void CSVReaderTest::CSVReader_Test_4_getHeaders_confirmLastHeader_Ex4_Grants() {
    CSVReader reader("../Project Information/Sample Data/Grants_expanded.csv");
    int comparison=reader.getHeaders().back().compare("Year");
    QCOMPARE(comparison, 0);
}

void CSVReaderTest::CSVReader_Test_5_getData_countRows_Ex1_Teaching() {
    CSVReader reader("../Project Information/Sample Data/Program_Teaching_expanded.csv");
    vector<vector<string>> data = reader.getData();
    int compare = (int)data.size();
    QCOMPARE(compare, 13585);
}

void CSVReaderTest::CSVReader_Test_5_getData_countRows_Ex2_Presentations() {
    CSVReader reader("../Project Information/Sample Data/Presentations_expanded.csv");
    vector<vector<string>> data = reader.getData();
    int compare = (int)data.size();
    QCOMPARE(compare, 11798);
}

void CSVReaderTest::CSVReader_Test_5_getData_countRows_Ex3_Publications() {
    CSVReader reader("../Project Information/Sample Data/Publications_expanded.csv");
    vector<vector<string>> data = reader.getData();
    int compare = (int)data.size();
    QCOMPARE(compare, 20542);
}

void CSVReaderTest::CSVReader_Test_5_getData_countRows_Ex4_Grants() {
    CSVReader reader("../Project Information/Sample Data/Grants_expanded.csv");
    vector<vector<string>> data = reader.getData();
    int compare = (int)data.size();
    QCOMPARE(compare, 4357);
}
