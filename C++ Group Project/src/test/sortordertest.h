#ifndef SORTORDERTEST_H
#define SORTORDERTEST_H
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
#include "gui/CustomSort.h"


class SortOrderTest: public QObject
{
    Q_OBJECT
private slots:

    void createSort();

  //  void createAndDeleteSort();

   // void createAndSetFirstField();

    void importCSVReaderGrants();

    void createSortListIO();

    void saveSortFile();

    void openSortFile();

    void createRecordsManager();

    void addAndFindRecord();

    void getHeadersFromRecord();

    void getNonexistentHeaderIndexFromRecord();

    void getHeaderIndexFromRecord();

    void getVectorFromList();

    void makeQStringGrants();

    void makeHeaderListGrants();

    void makeQStringPres();

    void makeHeaderListPres();

    void makeQStringPubs();

    void makeHeaderListPubs();

    void makeQStringTeaching();

    void makeHeaderListTeaching();

/*    void getCountFromNames();

    void getCountTupleFromRecords();

    void getTotalsTuplesfromRecords();
*/
    void testToolTipTeachNewSort();

    void testToolTipTeachExportButton();

    void testToolTipPubExportButton();

    void testToolTipPresExportButton();

    void testToolTipFundExportButton();

    void testToolTipCategoryTab();

    void testCustomSortNoNameNoField();

    void testCustomSortNameNoField();

    void testCustomSetOneFieldBoxTenItems();

    void testCustomSetOneFieldBox_data();

    void testCustomSetOneFieldBox();

    void testCustomSevenFieldBoxesNineItems();

   // void testCustomSevenFieldBoxesNineItemsFirstSet();

    void testCustomSortNameOneField();

    void testCustomSortChangeFirstFieldBackToNull();
};

#endif // SORTORDERTEST_H
