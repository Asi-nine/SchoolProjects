#include <iostream>
#include <stdio.h>
#include <QApplication>
#include <QStyleFactory>
#include <QTreeView>
#include <gui/GalaxyApp.h>
#include "test/CSVReaderTest.h"
#include "test/chartstest.h"
#include "test/sortordertest.h"
#include "gui/mainwindow.h"
#include "database/TestCSVReader.h"
#include "test/plotinteractiontest.h"

using namespace std;

int main(int argc, char *argv[]) {

    int test = 0;   /* test on */
    GalaxyApp app(argc, argv);
    //give the app a more modern look
    app.setStyle(QStyleFactory::create("Fusion"));

    //application information for session management
    app.setOrganizationName("TeamPerseus");
    app.setApplicationName("PeachyGalaxy");
    app.setOrganizationDomain("TeamPerseus/husseinfahmy/com.github");
    app.setApplicationVersion("2.0.0");
    if (test) {
        CSVReaderTest *test_obj = new CSVReaderTest();
        QTest::qExec(test_obj);
    }

    if (test) {
        ChartsTest *test_obj = new ChartsTest();
        QTest::qExec(test_obj);

    }

    if (test) {
        SortOrderTest *test_obj = new SortOrderTest();
        QTest::qExec(test_obj);
    }

    /*if (test) {
        plotinteractiontest *test_obj = new plotinteractiontest();
        QTest::qExec(test_obj);
    }*/
        
    /*
    TestCSVReader testReader;
    bool pass = testReader.CSV_READER_TEST_01();
    if (pass) cout << "TEST_01 PASSED !\n";
    else cout << "TEST_01 FAILED !\n";
    pass = testReader.CSV_READER_TEST_02();
    if (pass) cout << "TEST_02 PASSED !\n";
    else cout << "TEST_02 FAILED !\n";
    pass = testReader.CSV_READER_TEST_03();
    if (pass) cout << "TEST_03 PASSED !\n";
    else cout << "TEST_03 FAILED !\n";
    pass = testReader.CSV_READER_TEST_04();
    if (pass) cout << "TEST_04 PASSED !\n";
    else cout << "TEST_04 FAILED !\n";
    pass = testReader.CSV_READER_TEST_05();
    if (pass) cout << "TEST_05 PASSED !\n";
    else cout << "TEST_05 FAILED !\n";
    pass = testReader.CSV_READER_TEST_06();
    if (pass) cout << "TEST_06 PASSED !\n";
    else cout << "TEST_06 FAILED !\n";
    pass = testReader.CSV_READER_TEST_07();
    if (pass) cout << "TEST_07 PASSED !\n";
    else cout << "TEST_07 FAILED !\n";
    pass = testReader.CSV_READER_TEST_08();
    if (pass) cout << "TEST_08 PASSED !\n";
    else cout << "TEST_08 FAILED !\n";
    testReader.CSV_READER_TEST_ALL();
    */


    MainWindow mainWindow;
    mainWindow.setObjectName("galaxy");
    app.setMainWindow(&mainWindow);
    mainWindow.show();

    return app.exec();
}
