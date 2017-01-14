#ifndef CSVREADERTEST_H
#define CSVREADERTEST_H
#include <QtTest/QTest>
#include <iostream>
#include <stdio.h>
#include <QDataStream>
#include <QFile>
#include <QStringList>
#include "gui/CustomSort.h"
#include <QSignalSpy>
#include "gui/mainwindow.h"
#include "database/CSVReader.h"
#include "database/QSortListIO.h"
#include <vector>
#include <string>
#include "database/RecordsManager.h"
#include <QToolTip>
#include <QtWidgets>

class CSVReaderTest: public QObject
{
    Q_OBJECT
private slots:
    void CSVReader_Test_1_Constructor();
    void CSVReader_Test_2_loadCSV_Ex1_Teaching();
    void CSVReader_Test_2_loadCSV_Ex2_Presentations();
    void CSVReader_Test_2_loadCSV_Ex3_Publications();
    void CSVReader_Test_2_loadCSV_Ex4_Grants();
    void CSVReader_Test_3_parseDateString(std::string testDate, std::string CSVfile);
    void CSVReader_Test_3_parseDateString_Ex1_year_month_day__Teaching();
    void CSVReader_Test_3_parseDateString_Ex2_year_month_day__Presentations();
    void CSVReader_Test_3_parseDateString_Ex3_year_month_day__Publications();
    void CSVReader_Test_3_parseDateString_Ex4_year_month_day__Grants();
    void CSVReader_Test_3_parseDateString_Ex5_day_month_year__Teaching();
    void CSVReader_Test_3_parseDateString_Ex6_day_month_year__Presentations();
    void CSVReader_Test_3_parseDateString_Ex7_day_month_year__Publications();
    void CSVReader_Test_3_parseDateString_Ex8_day_month_year__Grants();
    void CSVReader_Test_3_parseDateString_Ex9_text_with_date_at_end__Teaching();
    void CSVReader_Test_3_parseDateString_Ex10_text_with_date_at_end__Presentations();
    void CSVReader_Test_3_parseDateString_Ex11_text_with_date_at_end__Publications();
    void CSVReader_Test_3_parseDateString_Ex12_text_with_date_at_end__Grants();
    void CSVReader_Test_4_getHeaders_count_Ex1_Teaching();
    void CSVReader_Test_4_getHeaders_count_Ex2_Presentations();
    void CSVReader_Test_4_getHeaders_count_Ex3_Publications();
    void CSVReader_Test_4_getHeaders_count_Ex4_Grants();
    void CSVReader_Test_4_getHeaders_confirmLastHeader_Ex1_Teaching();
    void CSVReader_Test_4_getHeaders_confirmLastHeader_Ex2_Presentations();
    void CSVReader_Test_4_getHeaders_confirmLastHeader_Ex3_Publications();
    void CSVReader_Test_4_getHeaders_confirmLastHeader_Ex4_Grants();
    void CSVReader_Test_5_getData_countRows_Ex1_Teaching();
    void CSVReader_Test_5_getData_countRows_Ex2_Presentations();
    void CSVReader_Test_5_getData_countRows_Ex3_Publications();
    void CSVReader_Test_5_getData_countRows_Ex4_Grants();
    //void importCSVReaderGrants();
};

#endif // CSVREADERTEST_H
