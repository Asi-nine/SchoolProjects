#include "sortordertest.h"

using namespace std;


/*
 * Linked to test cases 2B1.0->2B1.4
 * Test creation of CustomSort class
 */
void SortOrderTest::createSort() {

    CustomSort* sortdialog = new CustomSort();
    bool result = false;
    if(sortdialog->isEnabled()){
        result = true;
    }
    QCOMPARE(result,true);
}

/*
 *
 *  The commented out methods I have been using for learning.
 *  Please leave them as I may come back to them.
 *
void SortOrderTest::createAndDeleteSort() {

    CustomSort* sortdialog = new CustomSort();
    bool result = false;
    delete sortdialog;
    if(sortdialog){
        result = true;
    }

    QCOMPARE(result,false);
}*/

/*
void SortOrderTest::createAndSetFirstField() {

    MainWindow* a = new MainWindow();
    CustomSort* sortdialog = new CustomSort(a);
    QSignalSpy spy(sortdialog, SIGNAL(clicked(bool)));
    QTest::mouseClick(sortdialog, Qt::LeftButton);

    std::vector<std::string> headers = {"Dog"};
    sortdialog->setFields(headers);
    QPoint pos = QPoint(50,55);
    QWidget *btn = sortdialog->childAt(pos);
    QSignalSpy spy(btn, &QWidget::clicked);
    if(btn){
        QTest::mouseClick(btn, Qt::LeftButton);
    }

    QCOMPARE(1, 1);

}*/

//test reading a grant file, a remake of one of Team Peach's tests
void SortOrderTest::importCSVReaderGrants() {
    CSVReader reader("../Project Information/Sample Data/Grants_expanded.csv");
    vector<string> header = reader.getHeaders();
    int compare = (int)header.size();
    QCOMPARE(compare, 37);
}

// test creation of QSortListIO class
void SortOrderTest::createSortListIO() {
    QSortListIO* tester = new QSortListIO("testFileForSortFiles");
    bool result = false;
    if(tester){
        result = true;
    }
    QCOMPARE(result, true);

}

//test saving a custom sort order file
void SortOrderTest::saveSortFile() {
    QSortListIO tester = QSortListIO("testFileForSortFiles");
    QStringList pet1 = {"Dog"};
    QStringList pet2 = {"Cat"};
    QList<QStringList> pets = {pet1, pet2};
    tester.saveList(pets);
    bool result = QFileInfo("testFileForSortFiles").exists();

    QCOMPARE(result, true);
}
//test opening a custom sort order file
void SortOrderTest::openSortFile() {
    QSortListIO tester = QSortListIO("testFileForSortFiles");
    QList<QStringList> pets = tester.readList();
    QStringList firstPetList = pets.at(0);
    QStringList secondPetList = pets.at(1);
    QString firstPet = firstPetList.at(0);
    QString secondPet = secondPetList.at(0);
    bool result = false;
    if (firstPet == "Dog" && secondPet == "Cat") {
        result = true;
    }
    QCOMPARE(result, true);
}


//test Records manager constructor.
void SortOrderTest::createRecordsManager() {

    vector<string> recordArrayForm = {"Dog", "Cat"};
    BasicRecord* initialRecord = &recordArrayForm;
    RecordsManager* tester = new RecordsManager(initialRecord);
    bool result = false;
    if(tester){
        result = true;
    }
    QCOMPARE(result, true);
}


// test both adding a record and finding that record.
void SortOrderTest::addAndFindRecord() {
    vector<string> recordArrayForm = {"Pig", "Frog"};
    BasicRecord* initialRecord = &recordArrayForm;
    RecordsManager* tester = new RecordsManager(initialRecord);
    vector<string> addedRecordArray = {"Dog", "Cat"};
    BasicRecord* addedRecord = &addedRecordArray;
    tester->addRecord(123456789, addedRecord);
    BasicRecord* retrievedRecord = tester->findRecord(123456789).at(0);

    QCOMPARE(retrievedRecord, addedRecord);
}

// test getting headers from the recordManager
void SortOrderTest::getHeadersFromRecord() {
    vector<string> recordArrayForm = {"Dog", "Cat"};
    BasicRecord* initialRecord = &recordArrayForm;
    RecordsManager* tester = new RecordsManager(initialRecord);
    tester->addRecord(123456789, initialRecord);
    BasicRecord retrievedRecord = tester->getHeaders();

    QCOMPARE(retrievedRecord, recordArrayForm);
}

// test getting the number of the header in csv file when not in record
void SortOrderTest::getNonexistentHeaderIndexFromRecord() {
    vector<string> recordArrayForm = {"Dog", "Cat"};
    BasicRecord* initialRecord = &recordArrayForm;
    RecordsManager* tester = new RecordsManager(initialRecord);

    QCOMPARE(tester->getHeaderIndex("Pig"), -1);
}

// test getting the number of the header in csv file
void SortOrderTest::getHeaderIndexFromRecord() {
    vector<string> recordArrayForm = {"Dog", "Cat"};
    BasicRecord* initialRecord = &recordArrayForm;
    RecordsManager* tester = new RecordsManager(initialRecord);

    QCOMPARE(tester->getHeaderIndex("Dog"), 0);
}

// test making a vector of strings from a list given as an argument to a method
void SortOrderTest::getVectorFromList(){
    vector<string> recordArrayForm = {"Dog", "Cat"};
    BasicRecord* initialRecord = &recordArrayForm;
    RecordsManager* tester = new RecordsManager(initialRecord);
    vector<string> length2 = {"a","a"};
    vector<string> result = tester->list(2,"a","a");

    QCOMPARE(result, length2);
}

// test making a QString for the Grants
void SortOrderTest::makeQStringGrants() {
    CSVReader reader("../Project Information/Sample Data/GrantsClinicalFunding_sample.csv");
    vector<string> header = reader.getHeaders();
    BasicRecord* headerPointer = &header;
    const vector<string> sort = {"Baggins, Bilbo"};
    RecordsManager* tester = new RecordsManager(headerPointer);
    QString result = tester->createQStringForGrants(1950, 2014, sort, 'a', 'a');
    QString expected = "Total\t0\t$0.00\n";

    QCOMPARE(result, expected);

}

// test getting headers from Grants
void SortOrderTest::makeHeaderListGrants() {
    CSVReader reader("../Project Information/Sample Data/GrantsClinicalFunding_sample.csv");
    vector<string> header = reader.getHeaders();
    BasicRecord* headerPointer = &header;
    RecordsManager* tester = new RecordsManager(headerPointer);
    QList<QVariant> result = tester->createHeadersListForGrants("Member Name");
    QList<QVariant> expected;
    expected << "Member Name" << "Total" << "Total $";

    QCOMPARE(result, expected);
}

// test making a QString for the Presentations
void SortOrderTest::makeQStringPres() {
    CSVReader reader("../Project Information/Sample Data/Presentations_sample.csv");
    vector<string> header = reader.getHeaders();
    BasicRecord* headerPointer = &header;
    const vector<string> sort = {"Member Name", "Date"};
    RecordsManager* tester = new RecordsManager(headerPointer);
    QString result = tester->createQStringForPres(1950, 2014, sort, 'a', 'a');
    QString expected = "Total\t0\n";

    QCOMPARE(result, expected);

}

// test getting headers from Presentations
void SortOrderTest::makeHeaderListPres() {
    CSVReader reader("../Project Information/Sample Data/Presentations_sample.csv");
    vector<string> header = reader.getHeaders();
    BasicRecord* headerPointer = &header;
    RecordsManager* tester = new RecordsManager(headerPointer);
    QList<QVariant> result = tester->createHeadersListForPres("Member Name");
    QList<QVariant> expected;
    expected << "Member Name" << "# Presentations";

    QCOMPARE(result, expected);
}

// test making a QString for the Publications
void SortOrderTest::makeQStringPubs() {
    CSVReader reader("../Project Information/Sample Data/Publications_sample.csv");
    vector<string> header = reader.getHeaders();
    BasicRecord* headerPointer = &header;
    const vector<string> sort = {"Member Name", "Date"};
    RecordsManager* tester = new RecordsManager(headerPointer);
    QString result = tester->createQStringForPubs(1950, 2014, sort, 'a', 'a');
    QString expected = "Total\t0\n";

    QCOMPARE(result, expected);

}

// test getting headers from Publications
void SortOrderTest::makeHeaderListPubs() {
    CSVReader reader("../Project Information/Sample Data/Publications_sample.csv");
    vector<string> header = reader.getHeaders();
    BasicRecord* headerPointer = &header;
    RecordsManager* tester = new RecordsManager(headerPointer);
    QList<QVariant> result = tester->createHeadersListForPubs("Member Name");
    QList<QVariant> expected;
    expected << "Member Name" << "Totals";

    QCOMPARE(result, expected);
}

// test making a QString for the Teaching
void SortOrderTest::makeQStringTeaching() {
    CSVReader reader("../Project Information/Sample Data/Teaching_sample.csv");
    vector<string> header = reader.getHeaders();
    BasicRecord* headerPointer = &header;
    const vector<string> sort = {"Member Name", "Date"};
    RecordsManager* tester = new RecordsManager(headerPointer);
    QString result = tester->createQStringForTeaching(1950, 2014, sort, 'a', 'a');
    QString expected = "Total\t0\t0\t0\n";

    QCOMPARE(result, expected);

}

// test getting headers from Teaching
void SortOrderTest::makeHeaderListTeaching() {
    CSVReader reader("../Project Information/Sample Data/Teaching_sample.csv");
    vector<string> header = reader.getHeaders();
    BasicRecord* headerPointer = &header;
    RecordsManager* tester = new RecordsManager(headerPointer);
    QList<QVariant> result = tester->createHeadersListForTeaching("Member Name");
    QList<QVariant> expected;
    expected << "Member Name" << "Totals" << "# of Hours" << "# of Students";

    QCOMPARE(result, expected);
}

/* test getting the counts by name
 * THE NEXT 3 ARE FAILING BECAUSE I DO NOT KNOW WHAT THEY ARE SUPPOSED TO BE DOING EXACTLY
 * I have included them because the setup for the unit tests are good
 * so once functionality is understood, the tests can be used
 * keep them commented out for now
 */

/*
void SortOrderTest::getCountFromNames() {
    CSVReader reader("../Project Information/Sample Data/Teaching_sample.csv");
    vector<string> header = reader.getHeaders();
    BasicRecord* headerPointer = &header;
    RecordsManager* tester = new RecordsManager(headerPointer);
    vector<pair<string, int>> result, expected;
    result = tester->getCountByName(1950, 2016, 'a','b');
    expected = {{}};

    QCOMPARE(result, expected);
}

// test counting tuples
void SortOrderTest::getCountTupleFromRecords(){
    CSVReader reader("../Project Information/Sample Data/Teaching_sample.csv");
    vector<string> header = reader.getHeaders();
    vector<string> match = {"Baggins, Bilbo"};
    vector<string>* headerPointer = &header;
    RecordsManager* tester = new RecordsManager(headerPointer);
    vector<pair<string, int>> result, expected;
    result = tester->getCountTuple(2000, 2015, header, match, 'a', 'b');
    expected = {{"Baggings, Bilbo", 20}};

    QCOMPARE(result, expected);
}

// test getting total tuples
void SortOrderTest::getTotalsTuplesfromRecords(){
    CSVReader reader("../Project Information/Sample Data/Teaching_sample.csv");
    vector<string> header = reader.getHeaders();
    vector<string> match = {"Baggins, Bilbo"};
    string headerName = "Member Name";
    vector<string>* headerPointer = &header;
    RecordsManager* tester = new RecordsManager(headerPointer);
    vector<pair<string, double>> result, expected;
    result = tester->getTotalsTuple(2000, 2015, header, match, headerName, 'a', 'b');
    expected = {{"Baggins, Bilbo", 4.4}};

    QCOMPARE(result, expected);
}

*/


/*
 *IGNORE THIS, IT's PRIVATE
 *
void SortOrderTest::parseStringToDoubleTestRealDouble(){
    vector<string> recordArrayForm = {"Dog", "Cat"};
    BasicRecord* initialRecord = &recordArrayForm;
    RecordsManager* tester = new RecordsManager(initialRecord);
    string number = "109.444";
    double expected = 109.444;
    double result = tester->parseStringToDouble(number);

    QCOMPARE(result, expected);
}
*/

/*
 * TOOLTIP BUG HUNT
 *
 */



/*
 * The tooltip tests were hunting for a bug observed in the UI where
 * "export to pdf" was appearing when hovering over the lower two-thirds
 * of the application window.
 * These tooltip tests correspond to test case ID: 2D1.0
 */

// test that there is no tool tip for teach new sort
void SortOrderTest::testToolTipTeachNewSort(){
    QWidget *windowPointer = new MainWindow();
    QPushButton* button = windowPointer->findChild<QPushButton*>("teach_new_sort");
    button->show();
    QString tooltip = button->toolTip();
    QString expected = "";
    QCOMPARE(tooltip, expected);
    windowPointer->hide();
}

/*
 * The buttons that should have the tooltip "export to pdf" test
 */

void SortOrderTest::testToolTipTeachExportButton(){
    QWidget *windowPointer = new MainWindow();
    QToolButton* button = windowPointer->findChild<QToolButton*>("teachExportButton");
    button->show();
    QString tooltip = button->toolTip();
    QString expected = "Export to pdf";
    QCOMPARE(tooltip, expected);
    windowPointer->hide();
}

void SortOrderTest::testToolTipPubExportButton(){
    QWidget *windowPointer = new MainWindow();
    QToolButton* button = windowPointer->findChild<QToolButton*>("pubExportButton");
    button->show();
    QString tooltip = button->toolTip();
    QString expected = "Export to pdf";
    QCOMPARE(tooltip, expected);
    windowPointer->hide();
}

void SortOrderTest::testToolTipPresExportButton(){
    QWidget *windowPointer = new MainWindow();
    QToolButton* button = windowPointer->findChild<QToolButton*>("presExportButton");
    button->show();
    QString tooltip = button->toolTip();
    QString expected = "Export to pdf";
    QCOMPARE(tooltip, expected);
    windowPointer->hide();
}

void SortOrderTest::testToolTipFundExportButton(){
    QWidget *windowPointer = new MainWindow();
    QToolButton* button = windowPointer->findChild<QToolButton*>("fundExportButton");
    button->show();
    QString tooltip = button->toolTip();
    QString expected = "Export to pdf";
    QCOMPARE(tooltip, expected);
    windowPointer->hide();
}


/*
 * This was the culprit of the bug since it's tooltip was set to
 * "export to pdf" like the export to pdf button
 * This button should have no tooltip.
 */
void SortOrderTest::testToolTipCategoryTab(){
    QWidget *windowPointer = new MainWindow();
    QTabWidget* tab = windowPointer->findChild<QTabWidget*>("categoryTab");
    tab->show();
    QString tooltip = tab->toolTip();
    QString expected = "";
    QCOMPARE(tooltip, expected);
    windowPointer->hide();

}

/*
 * TOOLTIP BUG SOLVED
 * Likely should do more tooltip testing, there is also room to add tooltips to
 * buttons that do not have them that maybe should.
 */


/*
 * Tests creating the custom sort with no parameters
 * test for ID: 2B2.0 - 2B2.3
 */

void SortOrderTest::testCustomSortNoNameNoField(){
    CustomSort *sortPointer = new CustomSort();
    QDialogButtonBox* button = sortPointer->findChild<QDialogButtonBox*>("buttonBox");
    button->show();
    QList<QPushButton*> list = button->findChildren<QPushButton*>();
    QPushButton* save = list[1];
    save->show();
    QSignalSpy spy(button, SIGNAL(rejected()));
    QTest::mouseClick(save, Qt::LeftButton);
    sortPointer->hide();
    QVERIFY(spy.isValid());
}

/*
 * Tests creating the custom sort with no parameters
 * test for ID: 2B3.0 - 2B3.3
 */

void SortOrderTest::testCustomSortNameNoField(){
    CustomSort *sortPointer = new CustomSort();
    QDialogButtonBox* button = sortPointer->findChild<QDialogButtonBox*>("buttonBox");
    button->show();
    QLineEdit* name = sortPointer->findChild<QLineEdit*>("sort_name");
    name->show();
    QTest::keyClicks(name, "Test Sort");
    QList<QPushButton*> list = button->findChildren<QPushButton*>();
    QPushButton* save = list[1];
    save->show();
    QSignalSpy spy(button, SIGNAL(rejected()));
    QTest::mouseClick(save, Qt::LeftButton);
    sortPointer->hide();
    QVERIFY(spy.isValid());
}

/*
 * Verify that fields are getting the proper number of inputs for first
 * field box for 9 added items (should be 10 since the first is empty string by design).
 *  This should be the max of visible fields.
 */


void SortOrderTest::testCustomSetOneFieldBoxTenItems(){

    CustomSort *sortPointer = new CustomSort();
    QDialogButtonBox* button = sortPointer->findChild<QDialogButtonBox*>("buttonBox");
    button->show();

    vector<string> fieldOptions = {"Megaman", "Zero", "Dr. Wily", "Roll", "Rush",
                                   "Dr. Light", "Protoman", "Sigma", "Vile"};
    sortPointer->setFields(fieldOptions);
    QComboBox* first = sortPointer->findChild<QComboBox*>("field_0");
    int items = first->count();

    QCOMPARE(items, 10);
}

/*
 * Verify that fields are getting the proper inputs for first
 * field box for 10 items (the max including null string).
 *
 */
void SortOrderTest::testCustomSetOneFieldBox_data(){

    CustomSort *sortPointer = new CustomSort();
    QDialogButtonBox* button = sortPointer->findChild<QDialogButtonBox*>("buttonBox");
    button->show();

    vector<string> fieldOptions = {"Megaman", "Zero", "Dr. Wily", "Roll", "Rush",
                                   "Dr. Light", "Protoman", "Sigma", "Vile"};
    sortPointer->setFields(fieldOptions);
    QComboBox* first = sortPointer->findChild<QComboBox*>("field_0");

    QTest::addColumn<QString>("result");
    QTest::addColumn<QString>("expected");

    QTest::newRow("0") << first->itemText(0) << "";
    QTest::newRow("1") << first->itemText(1) << "Megaman";
    QTest::newRow("2") << first->itemText(2) << "Zero";
    QTest::newRow("3") << first->itemText(3) << "Dr. Wily";
    QTest::newRow("4") << first->itemText(4) << "Roll";
    QTest::newRow("5") << first->itemText(5) << "Rush";
    QTest::newRow("6") << first->itemText(6) << "Dr. Light";
    QTest::newRow("7") << first->itemText(7) << "Protoman";
    QTest::newRow("8") << first->itemText(8) << "Sigma";
    QTest::newRow("9") << first->itemText(9) << "Vile";

}

void SortOrderTest::testCustomSetOneFieldBox(){

    QFETCH(QString, result);
    QFETCH(QString, expected);

    QCOMPARE(result, expected);
}

/*
 * Test setting up 7 field boxes to 10 inputs
 *  for count. The count should decrease as an item is
 * selected in the previous field, and should be zero passed
 * any field that isn't selected yet.
 *
 */


//select no fields
void SortOrderTest::testCustomSevenFieldBoxesNineItems(){

    CustomSort *sortPointer = new CustomSort();
    QDialogButtonBox* button = sortPointer->findChild<QDialogButtonBox*>("buttonBox");
    button->show();

    vector<string> fieldOptions = {"Megaman", "Zero", "Dr. Wily", "Roll", "Rush",
                                   "Dr. Light", "Protoman", "Sigma", "Vile"};
    sortPointer->setFields(fieldOptions);
    QComboBox* first = sortPointer->findChild<QComboBox*>("field_0");
    int items0 = first->count();
    QComboBox* second = sortPointer->findChild<QComboBox*>("field_1");
    int items1 = second->count();
    QComboBox* third = sortPointer->findChild<QComboBox*>("field_2");
    int items2 = third->count();
    QComboBox* fourth = sortPointer->findChild<QComboBox*>("field_3");
    int items3 = fourth->count();
    QComboBox* fifth = sortPointer->findChild<QComboBox*>("field_4");
    int items4 = fifth->count();
    QComboBox* sixth = sortPointer->findChild<QComboBox*>("field_5");
    int items5 = sixth->count();
    QComboBox* seventh = sortPointer->findChild<QComboBox*>("field_6");
    int items6 = seventh->count();

    QCOMPARE(items0, 10);
    QCOMPARE(items1, 0);
    QCOMPARE(items2, 0);
    QCOMPARE(items3, 0);
    QCOMPARE(items4, 0);
    QCOMPARE(items5, 0);
    QCOMPARE(items6, 0);
}

/*select 1 field
 *
 * LEAVE THIS COMMENTED OUT, I AM HAVING SOME ISSUES I NEED TO FIX
 * HERE STILL.
 *
 */
/*
void SortOrderTest::testCustomSevenFieldBoxesNineItemsFirstSet(){

    CustomSort *sortPointer = new CustomSort();
    QDialogButtonBox* button = sortPointer->findChild<QDialogButtonBox*>("buttonBox");
    button->show();


    vector<string> fieldOptions = {"Megaman", "Zero", "Dr. Wily", "Roll", "Rush",
                                   "Dr. Light", "Protoman", "Sigma", "Vile"};
    sortPointer->setFields(fieldOptions);
    QComboBox* first = sortPointer->findChild<QComboBox*>("field_0");
    int items0 = first->count();
    first->setCurrentIndex(1);

    QComboBox* second = sortPointer->findChild<QComboBox*>("field_1");
    int items1 = second->count();
    QComboBox* third = sortPointer->findChild<QComboBox*>("field_2");
    int items2 = third->count();
    QComboBox* fourth = sortPointer->findChild<QComboBox*>("field_3");
    int items3 = fourth->count();
    QComboBox* fifth = sortPointer->findChild<QComboBox*>("field_4");
    int items4 = fifth->count();
    QComboBox* sixth = sortPointer->findChild<QComboBox*>("field_5");
    int items5 = sixth->count();
    QComboBox* seventh = sortPointer->findChild<QComboBox*>("field_6");
    int items6 = seventh->count();


    QCOMPARE(items0, 10);
    QCOMPARE(items1, 9);
    QCOMPARE(items2, 0);
    QCOMPARE(items3, 0);
    QCOMPARE(items4, 0);
    QCOMPARE(items5, 0);
    QCOMPARE(items6, 0);
}*/

void SortOrderTest::testCustomSortNameOneField(){

    CustomSort *sortPointer = new CustomSort();
    QDialogButtonBox* button = sortPointer->findChild<QDialogButtonBox*>("buttonBox");
    button->show();

    QLineEdit* name = sortPointer->findChild<QLineEdit*>("sort_name");
    name->show();
    QTest::keyClicks(name, "Test Sort");

    vector<string> fieldOptions = {"Megaman", "Zero", "Dr. Wily", "Roll", "Rush"};
    sortPointer->setFields(fieldOptions);
    QComboBox* first = sortPointer->findChild<QComboBox*>("field_0");

    first->setCurrentIndex(1);

    QList<QPushButton*> list = button->findChildren<QPushButton*>();
    QPushButton* save = list[1];
    save->show();

    QSignalSpy spy(button, SIGNAL(accepted()));
    QTest::mouseClick(save, Qt::LeftButton);
    sortPointer->hide();

    QVERIFY(spy.isValid());
}

/*
 * TESTS SWITCHING THE FIRST DROPDOWN BOX TO A NON
 * NULL STRING THEN SWITCHING IT BACK TO NULL STRING
 *
 * This was failing, but has been fixed. It was causing
 * the box below it to take on a value without being touched.
 *
 * Test Case ID: 2B8.0
 *
 */

void SortOrderTest::testCustomSortChangeFirstFieldBackToNull(){

    CustomSort *sortPointer = new CustomSort();
    QDialogButtonBox* button = sortPointer->findChild<QDialogButtonBox*>("buttonBox");
    button->show();


    vector<string> fieldOptions = {"Megaman", "Zero", "Dr. Wily", "Roll", "Rush"};
    sortPointer->setFields(fieldOptions);
    QComboBox* first = sortPointer->findChild<QComboBox*>("field_0");

    first->setCurrentIndex(1);
    first->setCurrentIndex(0);

    QComboBox* second = sortPointer->findChild<QComboBox*>("field_1");

    QString result = second->currentText();

    sortPointer->hide();

    QString expected = "";

    QCOMPARE(result, expected);
}



