#include <QDate>
#include <QDebug>
#include <QDirModel>
#include <QFileDialog>
#include <QHeaderView>
#include <QMessageBox>
#include <QPainter>
#include <QPdfWriter>
#include <QPrintDialog>
#include <QPrinter>
#include <QString>
#include <QSortFilterProxyModel>
#include <QGuiApplication>
#include <iostream>


#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "CustomSort.h"
#include "ErrorEditDialog.h"

#include "database/CSVReader.h"
#include "database/QSortListIO.h"
#include "database/RecordsManager.h"
#include "datamodel/TreeModel.h"
#include "datamodel/GrantFundingTreeModel.h"
#include "datamodel/PresentationTreeModel.h"
#include "datamodel/PublicationTreeModel.h"
#include "datamodel/TeachingTreeModel.h"

#define FUNDORDER_SAVE  "fundsortorder.dat"
#define PRESORDER_SAVE  "pressortorder.dat"
#define PUBORDER_SAVE   "pubsortorder.dat"
#define TEACHORDER_SAVE "teachsortorder.dat"


std::vector<std::string> MainWindow::GRANTS_MANFIELDS = {"Member Name", "Division", "Start Date", "Funding Type", "Status", "Peer Reviewed?", "Role", "Title"};
std::vector<std::string> MainWindow::PRES_MANFIELDS = {"Member Name", "Division", "Date", "Type", "Role", "Title"};
std::vector<std::string> MainWindow::PUBS_MANFIELDS = {"Member Name", "Division", "Type", "Status Date", "Role", "Title"};
std::vector<std::string> MainWindow::TEACH_MANFIELDS = {"Member Name", "Division", "Start Date", "Program"};

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow),
    fundTree(NULL), presTree(NULL), pubTree(NULL), teachTree(NULL),
    funddb(NULL), presdb(NULL), pubdb(NULL), teachdb(NULL) {

    this->restoreDate();

    std::cout << "Teaching file loaded: " << previousTeachingFile.toStdString() << "\n";
    std::cout << "Grants file loaded: " << previousGrantsFile.toStdString() << "\n";
    std::cout << "Presentations file loaded: " << previousPresentationsFile.toStdString() << "\n";
    std::cout << "Publications file loaded: " << previousPublicationsFile.toStdString() << "\n";


    //create app settings
    appSettings = new QSettings("TeamPerseus", "PerseusGalaxy", this);

    // draw GUI elements
    ui->setupUi(this);

    // set up the logo
    QPixmap logo(":/logo.png");
    ui->logo_label->setPixmap(logo);

    // set up application icon
    QIcon icon(":/icon32.ico");
    MainWindow::setWindowIcon(icon);

    // set the date format
    QString dFormat("yyyy");
    ui->FromDate->setDisplayFormat(dFormat);
    ui->ToDate->setDisplayFormat(dFormat);

    // set start year to be 1950
    QDate defaultStartDate(1950, 1, 1);

    // set ranges for spinbox
    ui->FromDate->setDateRange(defaultStartDate, QDate::currentDate());
    ui->ToDate->setDateRange(defaultStartDate, QDate::currentDate());

    //if this session has a restored user-chosen year, that is used as
    //the start date; 1950 otherwise
    if(this->yearStart != 0)
    {
        //set default date to user chosen year
        QDate changedStartDate(this->yearStart, 1, 1);
        ui->FromDate->setDate(changedStartDate);
    }
    else
    {
        ui->FromDate->setDate(defaultStartDate);
    }

    //if this session has a restored user-chosen year, that is used as
    //the end date; current year otherwise
    if(this->yearEnd != 0)
    {
        QDate changedEndDate(this->yearEnd, 1, 1);
        ui->ToDate->setDate(changedEndDate);
    }
    else
    {
        ui->ToDate->setDate(QDate::currentDate());
    }

    // set variables to the current date values
    yearStart = this->yearStart;
    yearEnd = this->yearEnd;

    //default print is disabled
    ui->teachPrintButton->setEnabled(false);
    ui->fundPrintButton->setEnabled(false);
    ui->pubPrintButton->setEnabled(false);
    ui->presPrintButton->setEnabled(false);

    ui->teachExportButton->setEnabled(false);
    ui->fundExportButton->setEnabled(false);
    ui->pubExportButton->setEnabled(false);
    ui->presExportButton->setEnabled(false);

    //Setup printer
    printer = new QPrinter();

    dateChanged = {false, false, false, false};

    this->restoreState();

}

MainWindow::~MainWindow() {

    delete ui;

    delete fundTree;
    delete presTree;
    delete pubTree;
    delete teachTree;

    delete funddb;
    delete presdb;
    delete pubdb;
    delete teachdb;
    delete printer;

}

void MainWindow::on_actionLoad_file_triggered() {
    QStringList filePaths = QFileDialog::getOpenFileNames(this,
                                                          "Select one or more files to load",
                                                          QDir::currentPath(),
                                                          tr("CSV (*.csv);; All files (*.*)"));
    if (filePaths.size() > 0) {
        const int NUM_TABS = 4;
        bool all_loaded[NUM_TABS] = {false, false, false, false};
        int sum = std::accumulate(all_loaded, all_loaded + NUM_TABS, 0);
        QStringList::Iterator it = filePaths.begin();
        while (sum != NUM_TABS && it != filePaths.end()) {
            QString path = it[0];
            //note short-circuit eval
            if (!all_loaded[FUNDING] && load_fund(path, true)) {
                all_loaded[FUNDING] = true;
            } else if (!all_loaded[TEACH] && load_teach(path, true)) {
                all_loaded[TEACH] = true;
            } else if (!all_loaded[PUBLICATIONS] && load_pub(path, true)) {
                all_loaded[PUBLICATIONS] = true;
            } else if (!all_loaded[PRESENTATIONS] && load_pres(path, true)) {
                all_loaded[PRESENTATIONS] = true;
            }
            sum = std::accumulate(all_loaded, all_loaded + NUM_TABS, 0);
            ++it;
        }
    }
}


/*
 * When the load file button is clicked a file open dialog box
 * is opened.  If a file name is successfully returned, makeTree()
 * is called.
 */
QString MainWindow::load_file() {
    QString filePath = QFileDialog::getOpenFileName(this, "Open File", QDir::currentPath(),
                                                    tr("CSV (*.csv);; All files (*.*)"));

    if (!filePath.isEmpty()) {

        /*All if statements ensure that the type of file is properly stored so that
         *it can be used for saving and restoring session. */
        if(load_teach(filePath, true) == true)
        {
            previousTeachingFile = filePath;
        }
        if(load_pres(filePath, true) == true)
        {
            previousPresentationsFile = filePath;
        }
        if(load_pub(filePath, true) == true)
        {
            previousPublicationsFile = filePath;
        }
        if(load_fund(filePath, true) == true)
        {
            previousGrantsFile = filePath;
        }
        return filePath;
    } else {
        return "";
    }
}

void MainWindow::refresh(int tabIndex) {
    // if we've loaded in a file, update that data
    switch (tabIndex) {
    case FUNDING:
        if (!fundPath.isEmpty()) {
            makeTree(FUNDING);
            ui->fund_graph_stackedWidget->hide();
            ui->fundGraphTitle->clear();
        }
        break;

    case PRESENTATIONS:
        if (!presPath.isEmpty()) {
            makeTree(PRESENTATIONS);
            ui->pres_graph_stackedWidget->hide();
            ui->presGraphTitle->clear();
        }
        break;
    case PUBLICATIONS:
        if (!pubPath.isEmpty()) {
            makeTree(PUBLICATIONS);
            ui->pub_graph_stackedWidget->hide();
            ui->pubGraphTitle->clear();
        }
        break;

    case TEACH:
        if (!teachPath.isEmpty()) {
            makeTree(TEACH);
            ui->teach_graph_stackedWidget->hide();
            ui->teachGraphTitle->clear();
        }
        break;
    }
}

int MainWindow::checkFile(int index, QString filePath) {
    CSVReader reader;
    std::vector<std::string> header;
    std::string searchstring;

    int sortHeaderIndex = 2;

    switch (index) {

    case TEACH:
        // read if first or if a new file is loaded
        if (teachPath.isEmpty() || (!teachPath.isEmpty() && filePath.compare(teachPath))) {
            // create a new reader to read in the file
            reader = CSVReader(filePath.toStdString());
            header = reader.getHeaders();

            // create a new manager for the data
            delete teachdb;
            teachdb = new RecordsManager(&header);

            // check for right file type by searching for unique header
            searchstring = "Program";
            if (std::find(header.begin(), header.end(), searchstring) != header.end()) {
                // load in data into the manager, with the date as the key
                sortHeaderIndex = teachdb->getHeaderIndex("Start Date");
                teachData = reader.getData();
                std::vector<std::vector<std::string>*> f_errs;
                unsigned int j;
                for (int i = 0; i < (int) teachData.size(); i++) {
                    for (j = 0; j < TEACH_MANFIELDS.size(); j++) {
                        int index = teachdb->getHeaderIndex(TEACH_MANFIELDS[j]);
                        if (teachData[i][index].compare("") == 0) {
                            f_errs.push_back(&teachData[i]);
                            break;
                        }
                    }

                    // if all mandatory fields are okay
                    if (j == TEACH_MANFIELDS.size()) {
                        // date interpretation
                        int yrIndex = teachdb->getHeaderIndex("Start Date");
                        int year;
                        //sscanf(teachData[i][yrIndex].c_str(), "%4d", &year);
                        //teachData[i][yrIndex] = std::to_string(year);

                        teachdb->addRecord(reader.parseDateString(teachData[i][sortHeaderIndex]), &teachData[i]);
                    }
                }

                if (f_errs.size() > 0) {
                    if(handle_field_errors(f_errs, header, TEACH_MANFIELDS)) {
                        for (unsigned int i = 0; i < f_errs.size(); i++) {
                            teachdb->addRecord(reader.parseDateString((*(f_errs[i]))[sortHeaderIndex]), f_errs[i]);

                        }
                    }
                }
            } else {
                return EXIT_FAILURE;
            }
        } else {
            return EXIT_SUCCESS;
        }
        ui->teachPrintButton->setEnabled(true);
        ui->teachExportButton->setEnabled(true);
        break;

    case PUBLICATIONS:
        // read if first or if a new file is loaded
        if (pubPath.isEmpty() || (!pubPath.isEmpty() && filePath.compare(pubPath))) {
            // create a new reader to read in the file
            reader = CSVReader(filePath.toStdString());
            header = reader.getHeaders();

            // create a new manager for the data
            delete pubdb;
            pubdb = new RecordsManager(&header);

            // check for right file type by searching for unique header
            searchstring = "Publication Status";
            if (std::find(header.begin(), header.end(), searchstring) != header.end()) {
                // load in data into the manager, with the date as the key
                sortHeaderIndex = pubdb->getHeaderIndex("Status Date");
                pubData = reader.getData();
                std::vector<std::vector<std::string>*> f_errs;
                unsigned int j;
                for (int i = 0; i < (int) pubData.size(); i++) {
                    for (j = 0; j < PUBS_MANFIELDS.size(); j++) {
                        int index = pubdb->getHeaderIndex(PUBS_MANFIELDS[j]);
                        if (pubData[i][index].compare("") == 0) {
                            f_errs.push_back(&pubData[i]);
                            break;
                        }
                    }

                    // if all mandatory fields are okay
                    if (j == PUBS_MANFIELDS.size()) {
                        // date interpretation
                        int yrIndex = pubdb->getHeaderIndex("Status Date");
                        int year;
                        //sscanf(pubData[i][yrIndex].c_str(), "%4d", &year);
                        //pubData[i][yrIndex] = std::to_string(year);

                        pubdb->addRecord(reader.parseDateString(pubData[i][sortHeaderIndex]), &pubData[i]);
                    }
                }

                if (f_errs.size() > 0) {
                    if(handle_field_errors(f_errs, header, PUBS_MANFIELDS)) {
                        for (unsigned int i = 0; i < f_errs.size(); i++) {
                            pubdb->addRecord(reader.parseDateString((*(f_errs[i]))[sortHeaderIndex]), f_errs[i]);
                        }
                    }
                }
            } else {
                return EXIT_FAILURE;
            }
        } else {
            return EXIT_SUCCESS;
        }
        ui->pubPrintButton->setEnabled(true);
        ui->pubExportButton->setEnabled(true);
        break;

    case PRESENTATIONS:
        // read if first or if a new file is loaded
        if (presPath.isEmpty() || (!presPath.isEmpty() && filePath.compare(presPath))) {
            // create a new reader to read in the file
            reader = CSVReader(filePath.toStdString());
            header = reader.getHeaders();

            // create a new manager for the data
            delete presdb;
            presdb = new RecordsManager(&header);

            // check for right file type by searching for unique header
            searchstring = "Activity Type";
            if (std::find(header.begin(), header.end(), searchstring) != header.end()) {
                // load in data into the manager, with the date as the key
                sortHeaderIndex = presdb->getHeaderIndex("Date");
                presData = reader.getData();
                std::vector<std::vector<std::string>*> f_errs;
                unsigned int j = 0;
                for (int i = 0; i < (int) presData.size(); i++) {
                    //check through mandatory fields for empty fields
                    for (j = 0; j < PRES_MANFIELDS.size(); j++) {
                        int index = presdb->getHeaderIndex(PRES_MANFIELDS[j]);
                        if (presData[i][index].compare("") == 0) {
                            f_errs.push_back(&presData[i]);
                            break;
                        }
                    }

                    // if all mandatory fields are okay
                    if (j == PRES_MANFIELDS.size()) {
                        // date interpretation
                        int yrIndex = presdb->getHeaderIndex("Date");
                        int year;
                        //sscanf(presData[i][yrIndex].c_str(), "%4d", &year);
                        //presData[i][yrIndex] = std::to_string(year);

                        presdb->addRecord(reader.parseDateString(presData[i][sortHeaderIndex]), &presData[i]);
                    }
                }

                if (f_errs.size() > 0) {
                    if(handle_field_errors(f_errs, header, PRES_MANFIELDS)) {
                        for (unsigned int i = 0; i < f_errs.size(); i++) {
                            presdb->addRecord(reader.parseDateString((*(f_errs[i]))[sortHeaderIndex]), f_errs[i]);
                        }
                    }
                }
            } else {
                return EXIT_FAILURE;
            }
        } else {
            return EXIT_SUCCESS;
        }
        ui->presPrintButton->setEnabled(true);
        ui->presExportButton->setEnabled(true);
        break;

    case FUNDING:
        // read if first or if a new file is loaded
        if (fundPath.isEmpty() || (!fundPath.isEmpty() && filePath.compare(fundPath))) {
            // create a new reader to read in the file
            reader = CSVReader(filePath.toStdString());
            header = reader.getHeaders();

            // create a new manager for the data
            delete funddb;
            funddb = new RecordsManager(&header);

            // check for right file type by searching for unique header
            searchstring = "Funding Type";

            if (std::find(header.begin(), header.end(), searchstring) != header.end()) {
                // load in data into the manager, with the date as the key
                sortHeaderIndex = funddb->getHeaderIndex("Start Date");
                fundData = reader.getData();
                std::vector<std::vector<std::string>*> f_errs;
                unsigned int j;
                for (int i = 0; i < (int) fundData.size(); i++) {
                    for (j = 0; j < GRANTS_MANFIELDS.size(); j++) {
                        int index = funddb->getHeaderIndex(GRANTS_MANFIELDS[j]);
                        if (fundData[i][index].compare("") == 0) {
                            f_errs.push_back(&fundData[i]);
                            break;
                        }
                    }

                    // if all mandatory fields are okay
                    if (j == GRANTS_MANFIELDS.size()) {
                        // date interpretation
                        int yrIndex = funddb->getHeaderIndex("Start Date");
                        int year;
                        //sscanf(fundData[i][yrIndex].c_str(), "%4d", &year);
                        //fundData[i][yrIndex] = std::to_string(year);

                        // boolean interpretation
                        int prIndex = funddb->getHeaderIndex("Peer Reviewed?");
                        if (fundData[i][prIndex].compare("True") == 0) {
                            fundData[i][prIndex] = "Peer Reviewed";
                        } else {
                            fundData[i][prIndex] = "Not Peer Reviewed";
                        }
                        funddb->addRecord(reader.parseDateString(fundData[i][sortHeaderIndex]), &fundData[i]);
                    }
                }
                if (f_errs.size() > 0) {
                    if(handle_field_errors(f_errs, header, GRANTS_MANFIELDS)) {
                        for (unsigned int i = 0; i < f_errs.size(); i++) {
                            funddb->addRecord(reader.parseDateString((*(f_errs[i]))[sortHeaderIndex]), f_errs[i]);
                        }
                    }
                }
            } else {
                return EXIT_FAILURE;
            }
        } else {
            return EXIT_SUCCESS;
        }
        ui->fundPrintButton->setEnabled(true);
        ui->fundExportButton->setEnabled(true);
        break;
    }
    return EXIT_SUCCESS;
}

void MainWindow::createDefaultSortOrder(int tabIndex) {
    QStringList defaultOrder;
    defaultOrder << "Default";

    switch (tabIndex) {
    case FUNDING:
        // specify default sort order
        defaultOrder << "Member Name" << "Funding Type" << "Peer Reviewed?" << "Status" << "Role" << "Title";

        // add default list to member variable
        allFundOrders << defaultOrder;

    {
        // save the default for the user
        QSortListIO saveFundSort(FUNDORDER_SAVE);
        saveFundSort.saveList(allFundOrders);
    }

        break;
    case PRESENTATIONS:
        // specify default sort order
        defaultOrder << "Member Name" << "Type" << "Role" << "Title";

        // add default list to member variable
        allPresOrders << defaultOrder;

    {
        // save the default for the user
        QSortListIO savePresSort(PRESORDER_SAVE);
        savePresSort.saveList(allPresOrders);
    }

        break;
    case PUBLICATIONS:
        // specify default sort order
        defaultOrder << "Member Name" << "Type" << "Role" << "Title";

        // add default list to member variable
        allPubOrders << defaultOrder;

    {
        // save the default for the user
        QSortListIO savePubSort(PUBORDER_SAVE);
        savePubSort.saveList(allPubOrders);
    }

        break;
    case TEACH:
        // specify default sort order
        defaultOrder << "Member Name" << "Program";

        // add default list to member variable
        allTeachOrders << defaultOrder;

    {
        // save the default for the user
        QSortListIO saveTeachSort(FUNDORDER_SAVE);
        saveTeachSort.saveList(allFundOrders);
    }

        break;
    }
}

/*
 * err: vector of pointers to record entries.
 * headers: vector of strings containing the db headers
 * mandatory: vector of strings containing the mandatory fields in the db
 *
 * Returns true when the passed err vector contains edited fields.
 * Returns false when no fields have been edited.
 */
bool MainWindow::handle_field_errors(std::vector<std::vector<std::string>*>& err,
                                     std::vector<std::string>& headers,
                                     std::vector<std::string>& mandatory) {
    //Since CSVReader alldata contains completely empty records
    //remove them first.
    std::vector<std::vector<std::string>*>::iterator it;
    for (it = err.begin(); it != err.end(); it++) {
        bool allEmpty = true;
        for (int col = 0; col < (int) (*it)->size(); col++) {
            if ((*it)->at(col).compare("") != 0) {
                allEmpty = false;
            }
        }
        if (allEmpty) {
            it = err.erase(it);
            it--;
        }
    }
    //Return false; there are no errors to correct
    if (err.size() == 0) {
        return false;
    }
    QMessageBox prompt;
    QString mainText = "File contains records with missing mandatory fields.";
    prompt.setText(mainText);
    prompt.setInformativeText("Do you want to edit these entries or discard?");
    prompt.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    prompt.setDefaultButton(QMessageBox::Yes);
    prompt.setButtonText(QMessageBox::Yes, "Edit");
    prompt.setButtonText(QMessageBox::No, "Discard");
    prompt.setWindowIcon(QIcon(":/icon32.ico"));
    int ret = prompt.exec();

    switch (ret) {
    case QMessageBox::Yes: {

        ErrorEditDialog diag(this, err, headers, mandatory); // initialize an ErrorEditDialog
        if(diag.exec()) {
            return true;
        }
        return false;
    }

    case QMessageBox::No:
    default:
        return false;
    }
}

/*
 * Builds a TreeModel for the ui's embedded treeview.
 */
void MainWindow::makeTree(int tabIndex) {
    switch (tabIndex) {
    case TEACH:
        // set up some member variables to point to the current data in use
        currentdb = teachdb;
        delete teachTree;
        teachTree = new TeachingTreeModel(currentdb);
        currentTree = teachTree;

        // get some UI elements so we can put the tree and graphs into them
        currentView = ui->teachTreeView;

        // analyze the data into a tree
        currentTree->setupModel(yearStart, yearEnd, teachSortOrder, getFilterStartChar(TEACH), getFilterEndChar(TEACH));

        ui->teach_pie_button->toggle();

        break;

    case PUBLICATIONS:
        // set up some member variables to point to the current data in use
        currentdb = pubdb;
        delete pubTree;
        pubTree = new PublicationTreeModel(currentdb);
        currentTree = pubTree;

        // get some UI elements so we can put the tree and graphs into them
        currentView = ui->pubTreeView;

        // analyze the data into a tree
        currentTree->setupModel(yearStart, yearEnd, pubSortOrder, getFilterStartChar(PUBLICATIONS), getFilterEndChar(PUBLICATIONS));

        ui->pub_pie_button->toggle();

        break;
    case PRESENTATIONS:
        // set up some member variables to point to the current data in use
        currentdb = presdb;
        delete presTree;

        presTree = new PresentationTreeModel(currentdb);
        currentTree = presTree;

        // get some UI elements so we can put the tree and graphs into them
        currentView = ui->presTreeView;

        // analyze the data into a tree
        currentTree->setupModel(yearStart, yearEnd, presSortOrder, getFilterStartChar(PRESENTATIONS), getFilterEndChar(PRESENTATIONS));

        ui->pres_pie_button->toggle();

        break;

    case FUNDING:
        // set up some member variables to point to the current data in use
        currentdb = funddb;
        delete fundTree;
        fundTree = new GrantFundingTreeModel(currentdb);
        currentTree = fundTree;

        // get some UI elements so we can put the tree and graphs into them
        currentView = ui->fundTreeView;

        // analyze the data into a tree
        currentTree->setupModel(yearStart, yearEnd, fundSortOrder, getFilterStartChar(FUNDING), getFilterEndChar(FUNDING));

        ui->fund_pie_button->toggle();

        break;
    }


    /*
     *CUSTOM USER SORT
     *
     */

    // set up the tree in our UI
    //Currently sorting by string need to fix this for the doubles and ints
    QSortFilterProxyModel *sortWrapTreeView = new QSortFilterProxyModel(currentView);
    sortWrapTreeView->setSourceModel(currentTree);
    //sort the strings based on letter in ascending order, and allow toggle between ascending/descending
    sortWrapTreeView->setSortCaseSensitivity(Qt::CaseInsensitive);
    //currentView->header()->
    currentView->setModel(sortWrapTreeView);
    currentView->header()->setSortIndicator(0, Qt::AscendingOrder);
    currentView->setSortingEnabled(true);

    // set resize property to be resized
    currentView->header()->resizeSections(QHeaderView::ResizeToContents);
}

void MainWindow::setupPieChart(PieChartWidget* pieChart, QListWidget *pieListWidget, std::vector<std::pair <std::string, double>> pieChartList) {
    // draws the pie graph by sending piechartwidget a vector of name, presentation count
    int pieSize = (int) pieChartList.size();
    pieListWidget->clear();
    QVector<QColor> colorList(pieSize);
    // set colors
    for (int i = 0; i < pieSize; i++) {
        //set a color order
        if(i%3==0){
            colorList[i] = (QColor(255/6*((i+6)%7), 255/6*((i)%7), 255/6*((i+4)%7)));
        }
        if(i%3==1){
            colorList[i] = (QColor(255/6*((i)%7), 255/6*((i+4)%7), 255/6*((i+6)%7)));
        }
        if(i%3==2){
            colorList[i] = (QColor(255/6*((i+4)%7), 255/6*((i+6)%7), 255/6*((i)%7)));
        }
        pieListWidget->addItem(QString::fromStdString(pieChartList[i].first));

        // set legend colors
        QPixmap pixmap(100, 100);
        pixmap.fill(QColor(colorList[i]));
        QIcon tempIcon(pixmap);
        pieListWidget->item(i)->setIcon(tempIcon);
    }

    pieChart->setData(pieChartList, colorList); //passes vector list to piechartwidget
}

void MainWindow::setupBarChart(QCustomPlot *barChart, std::vector<std::pair <std::string, double>> barChartList) {

    barChart->axisRect()->setupFullAxesBox();

    //get label list
    int barSize = (int) barChartList.size();
    double maxCount = 0;
    double scaledCount;
    QVector<double> ticks;
    QVector<QString> ylabels;
    QVector<double> count;

    //add label list to y axis labels
    for (int i = 0; i < barSize; i++){
        ticks << (i+1);
        ylabels << QString::fromStdString(barChartList[i].first);

        // scale the count number
        if (barChartList[i].second>1000000){
            scaledCount = barChartList[i].second/1000000;
        } else if (barChartList[i].second>1000){
            scaledCount = barChartList[i].second/1000;
        } else{
            scaledCount = barChartList[i].second;
        }
        count <<scaledCount;

        if (maxCount < barChartList[i].second)
            maxCount = barChartList[i].second;

        // create a bar graph and add it to barchart
        QCPBars *newbar = new QCPBars(barChart->yAxis, barChart->xAxis);
        // set names and colors:
        QPen pen;
        pen.setWidthF(1.2);
        newbar->setName(ylabels[i]);
        QColor color;
        if(i%3==0){
            color = (QColor(255/6*((i+6)%7), 255/6*((i)%7), 255/6*((i+4)%7)));
        }
        if(i%3==1){
            color = (QColor(255/6*((i)%7), 255/6*((i+4)%7), 255/6*((i+6)%7)));
        }
        if(i%3==2){
            color = (QColor(255/6*((i+4)%7), 255/6*((i+6)%7), 255/6*((i)%7)));
        }
        pen.setColor(color);
        newbar->setPen(pen);
        newbar->setBrush(color);

        // set data of the bar
        newbar->addData(ticks[i], count[i]);


    }

    // set y axis label by text
    QSharedPointer<QCPAxisTickerText> tickerText(new QCPAxisTickerText);
    tickerText->addTicks(ticks,ylabels);
    barChart->yAxis->setTicker(tickerText);

    // set y axis format
    barChart->yAxis->setTickLabelPadding(1);
    barChart->yAxis->setTickLength(0, 1);
    barChart->yAxis->grid()->setVisible(true);
    barChart->yAxis->setRange(0, barSize+1);

    // if the count number as total, scale it if nessassry
    if(maxCount>1000000){
        maxCount = maxCount/1000000;
        barChart->xAxis->setLabel("Total (in Millions)");
    }else if (maxCount>1000){
        maxCount = maxCount/1000;
        barChart->xAxis->setLabel("Total (in Thousands)");
    }else{
        barChart->xAxis->setLabel("Total");
    }

    // setup X Axis
    barChart->xAxis->setRange(0,maxCount+(maxCount*.05));
    barChart->xAxis->grid()->setSubGridVisible(true);

    // set grid lines
    QPen gridPen;
    gridPen.setStyle(Qt::SolidLine);
    gridPen.setColor(QColor(0, 0, 0, 25));
    barChart->xAxis->grid()->setPen(gridPen);
    gridPen.setStyle(Qt::DotLine);
    barChart->xAxis->grid()->setSubGridPen(gridPen);

    // set legends invisable
    barChart->legend->setVisible(false);

    // set barChart interactions
    barChart->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom|QCP::iSelectAxes|QCP::iSelectLegend|QCP::iSelectPlottables);

    // connect slot that ties some axis selections together (especially opposite axes):
    QObject::connect(barChart, SIGNAL(selectionChangedByUser()), this, SLOT(selectionChanged()));
    // connect slots that takes care that when an axis is selected, only that direction can be dragged and zoomed:
    QObject::connect(barChart, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(mousePress()));
    QObject::connect(barChart, SIGNAL(mouseWheel(QWheelEvent*)), this, SLOT(mouseWheel()));

    // make bottom and left axes transfer their ranges to top and right axes:
    QObject::connect(barChart->xAxis, SIGNAL(rangeChanged(QCPRange)), barChart->xAxis2, SLOT(setRange(QCPRange)));
    QObject::connect(barChart->yAxis, SIGNAL(rangeChanged(QCPRange)), barChart->yAxis2, SLOT(setRange(QCPRange)));
}

void MainWindow::setupLineChart(QCustomPlot *lineChart, std::vector<std::pair <std::string, double>> lineChartList){

    lineChart->axisRect()->setupFullAxesBox();

    // create create and configure plottables
    QCPGraph *linegraph = new QCPGraph(lineChart->yAxis, lineChart->xAxis);
    linegraph->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, QPen(Qt::blue,1.5), QBrush(Qt::white),9));
    linegraph->setPen(QPen(QColor(0,102,204),2));

    //get label list
    int lineSize = (int) lineChartList.size();
    double maxCount = 0;
    double scaledCount;
    QVector<double> ticks;
    QVector<QString> ylabels;
    QVector<double> count;

    //add label list to x axis labels
    for (int i = 0; i < lineSize; i++){
        ticks << (i+1);
        ylabels << QString::fromStdString(lineChartList[i].first);
        if (lineChartList[i].second>1000000){
            scaledCount = lineChartList[i].second/1000000;
        } else if (lineChartList[i].second>1000){
            scaledCount = lineChartList[i].second/1000;
        } else{
            scaledCount = lineChartList[i].second;
        }
        count <<scaledCount;

        if (maxCount < lineChartList[i].second)
            maxCount = lineChartList[i].second;

    }

    // set y axis label by text
    QSharedPointer<QCPAxisTickerText> tickerText(new QCPAxisTickerText);
    tickerText->addTicks(ticks,ylabels);
    lineChart->yAxis->setTicker(tickerText);

    // set y axis format
    lineChart->yAxis->setTickLabelPadding(1);
    lineChart->yAxis->setTickLength(0, 1);
    lineChart->yAxis->grid()->setVisible(true);
    lineChart->yAxis->setRange(0, lineSize+1);

    // if the count number as total, scale it if nessassry
    if(maxCount>1000000){
        maxCount = maxCount/1000000;
        lineChart->xAxis->setLabel("Total (in Millions)");
    }else if (maxCount>1000){
        maxCount = maxCount/1000;
        lineChart->xAxis->setLabel("Total (in Thousands)");
    }else{
        lineChart->xAxis->setLabel("Total");
    }

    // setup y Axis
    lineChart->xAxis->setRange(0,maxCount+(maxCount*.05));
    lineChart->xAxis->grid()->setSubGridVisible(true);

    // setup grid lines
    QPen gridPen;
    gridPen.setStyle(Qt::SolidLine);
    gridPen.setColor(QColor(0, 0, 0, 25));
    lineChart->xAxis->grid()->setPen(gridPen);
    gridPen.setStyle(Qt::DotLine);
    lineChart->xAxis->grid()->setSubGridPen(gridPen);

    linegraph->setData(ticks, count);

    // set legends invisable
    lineChart->legend->setVisible(false);

    // set up linechart interactions
    lineChart->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom|QCP::iSelectAxes|QCP::iSelectLegend|QCP::iSelectPlottables);
    // connect slot that ties some axis selections together (especially opposite axes):
    QObject::connect(lineChart, SIGNAL(selectionChangedByUser()), this, SLOT(selectionChanged()));
    // connect slots that takes care that when an axis is selected, only that direction can be dragged and zoomed:
    QObject::connect(lineChart, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(mousePress()));
    QObject::connect(lineChart, SIGNAL(mouseWheel(QWheelEvent*)), this, SLOT(mouseWheel()));

    // make bottom and left axes transfer their ranges to top and right axes:
    QObject::connect(lineChart->xAxis, SIGNAL(rangeChanged(QCPRange)), lineChart->xAxis2, SLOT(setRange(QCPRange)));
    QObject::connect(lineChart->yAxis, SIGNAL(rangeChanged(QCPRange)), lineChart->yAxis2, SLOT(setRange(QCPRange)));

}

void MainWindow::setupBubbleChart(QCustomPlot *bubbleChart, std::vector<std::pair <std::string, double>> bubbleChartList){

    bubbleChart->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom|QCP::iSelectAxes|QCP::iSelectLegend|QCP::iSelectPlottables);

    bubbleChart->axisRect()->setupFullAxesBox();

    //get label list
    int bubbleSize = (int) bubbleChartList.size();
    double maxCount = 0;
    double scaledCount;
    QVector<double> ticks;
    QVector<QString> ylabels;
    QVector<double> count;

    //add label list to x axis labels
    for (int i = 0; i < bubbleSize; i++){
        ticks << (i+1);
        ylabels << QString::fromStdString(bubbleChartList[i].first);

        if (bubbleChartList[i].second>1000000){
            scaledCount = bubbleChartList[i].second/1000000;
        } else if (bubbleChartList[i].second>1000){
            scaledCount = bubbleChartList[i].second/1000;
        } else{
            scaledCount = bubbleChartList[i].second;
        }
        count <<scaledCount;

        if (maxCount < bubbleChartList[i].second)
            maxCount = bubbleChartList[i].second;

        // create create and configure plottables
        QCPGraph *bubblegraph = new QCPGraph(bubbleChart->yAxis, bubbleChart->xAxis);
        QColor color;
        if(i%3==0){
            color = (QColor(255/6*((i+6)%7), 255/6*((i)%7), 255/6*((i+4)%7)));
        }
        if(i%3==1){
            color = (QColor(255/6*((i)%7), 255/6*((i+4)%7), 255/6*((i+6)%7)));
        }
        if(i%3==2){
            color = (QColor(255/6*((i+4)%7), 255/6*((i+6)%7), 255/6*((i)%7)));
        }

        bubblegraph->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, QPen(color,1.5), QBrush(color),count[i]*5));
        bubblegraph->setPen(QPen(Qt::transparent,2));
        bubblegraph->setName(ylabels[i]);
        bubblegraph->addData(ticks[i],count[i]);

    }


    // set y axis label by text
    QSharedPointer<QCPAxisTickerText> tickerText(new QCPAxisTickerText);
    tickerText->addTicks(ticks,ylabels);
    bubbleChart->yAxis->setTicker(tickerText);

    // set y axis format
    bubbleChart->yAxis->setTickLabelPadding(1);
    bubbleChart->yAxis->setTickLength(0, 1);
    bubbleChart->yAxis->grid()->setVisible(true);
    bubbleChart->yAxis->setRange(0, bubbleSize+1);

    // if the count number as total, scale it if nessassry
    if(maxCount>1000000){
        maxCount = maxCount/1000000;
        bubbleChart->xAxis->setLabel("Total (in Millions)");
    }else if (maxCount>1000){
        maxCount = maxCount/1000;
        bubbleChart->xAxis->setLabel("Total (in Thousands)");
    }else{
        bubbleChart->xAxis->setLabel("Total");
    }

    // setup y Axis
    bubbleChart->xAxis->setRange(0,maxCount+(maxCount*.05));
    bubbleChart->xAxis->grid()->setSubGridVisible(true);

    // set grid lines
    QPen gridPen;
    gridPen.setStyle(Qt::SolidLine);
    gridPen.setColor(QColor(0, 0, 0, 25));
    bubbleChart->xAxis->grid()->setPen(gridPen);
    gridPen.setStyle(Qt::DotLine);
    bubbleChart->xAxis->grid()->setSubGridPen(gridPen);
    bubbleChart->legend->setVisible(false);

    // connect slot that ties some axis selections together (especially opposite axes):
    QObject::connect(bubbleChart, SIGNAL(selectionChangedByUser()), this, SLOT(selectionChanged()));
    // connect slots that takes care that when an axis is selected, only that direction can be dragged and zoomed:
    QObject::connect(bubbleChart, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(mousePress()));
    QObject::connect(bubbleChart, SIGNAL(mouseWheel(QWheelEvent*)), this, SLOT(mouseWheel()));

    // make bottom and left axes transfer their ranges to top and right axes:
    QObject::connect(bubbleChart->xAxis, SIGNAL(rangeChanged(QCPRange)), bubbleChart->xAxis2, SLOT(setRange(QCPRange)));
    QObject::connect(bubbleChart->yAxis, SIGNAL(rangeChanged(QCPRange)), bubbleChart->yAxis2, SLOT(setRange(QCPRange)));

}


void MainWindow::selectionChanged()
{

  // make top and bottom axes be selected synchronously, and handle axis and tick labels as one selectable object:
  if (ui->teachBarChart->xAxis->selectedParts().testFlag(QCPAxis::spAxis) || ui->teachBarChart->xAxis->selectedParts().testFlag(QCPAxis::spTickLabels) ||
      ui->teachBarChart->xAxis2->selectedParts().testFlag(QCPAxis::spAxis) || ui->teachBarChart->xAxis2->selectedParts().testFlag(QCPAxis::spTickLabels))
  {
    ui->teachBarChart->xAxis2->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
    ui->teachBarChart->xAxis->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
  }
  // make left and right axes be selected synchronously, and handle axis and tick labels as one selectable object:
  if (ui->teachBarChart->yAxis->selectedParts().testFlag(QCPAxis::spAxis) || ui->teachBarChart->yAxis->selectedParts().testFlag(QCPAxis::spTickLabels) ||
      ui->teachBarChart->yAxis2->selectedParts().testFlag(QCPAxis::spAxis) || ui->teachBarChart->yAxis2->selectedParts().testFlag(QCPAxis::spTickLabels))
  {
    ui->teachBarChart->yAxis2->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
    ui->teachBarChart->yAxis->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
  }
}

void MainWindow::mousePress()
{
  // if an axis is selected, only allow the direction of that axis to be dragged
  // if no axis is selected, both directions may be dragged

  if (ui->teachBarChart->xAxis->selectedParts().testFlag(QCPAxis::spAxis))
    ui->teachBarChart->axisRect()->setRangeDrag(ui->teachBarChart->xAxis->orientation());
  else if (ui->teachBarChart->yAxis->selectedParts().testFlag(QCPAxis::spAxis))
    ui->teachBarChart->axisRect()->setRangeDrag(ui->teachBarChart->yAxis->orientation());
  else
    ui->teachBarChart->axisRect()->setRangeDrag(Qt::Horizontal|Qt::Vertical);
}

void MainWindow::mouseWheel()
{
  // if an axis is selected, only allow the direction of that axis to be zoomed
  // if no axis is selected, both directions may be zoomed

  if (ui->teachBarChart->xAxis->selectedParts().testFlag(QCPAxis::spAxis))
    ui->teachBarChart->axisRect()->setRangeZoom(ui->teachBarChart->xAxis->orientation());
  else if (ui->teachBarChart->yAxis->selectedParts().testFlag(QCPAxis::spAxis))
    ui->teachBarChart->axisRect()->setRangeZoom(ui->teachBarChart->yAxis->orientation());
  else
    ui->teachBarChart->axisRect()->setRangeZoom(Qt::Horizontal|Qt::Vertical);
}

void MainWindow::on_teach_new_sort_clicked() {
    if (teachdb != NULL) {
        CustomSort* sortdialog = new CustomSort();
        sortdialog->setFields(TEACH_MANFIELDS);
        int ret = sortdialog->exec();
        if (ret) {
            QStringList newSortOrder = sortdialog->getSortFields();
            allTeachOrders << newSortOrder;
            ui->teach_sort->addItem(newSortOrder.at(0));

            // save the sort fields to file
            QSortListIO saveTeachSort(TEACHORDER_SAVE);
            saveTeachSort.saveList(allTeachOrders);
        }
        delete sortdialog;
    } else {
        QMessageBox::critical(this, "Missing File", "Please load a file first.");
    }
}

void MainWindow::on_pub_new_sort_clicked() {
    if (pubdb != NULL) {
        CustomSort* sortdialog = new CustomSort();
        sortdialog->setFields(PUBS_MANFIELDS);
        int ret = sortdialog->exec();
        if (ret) {
            QStringList newSortOrder = sortdialog->getSortFields();
            allPubOrders << newSortOrder;
            ui->pub_sort->addItem(newSortOrder.at(0));

            // save the sort fields to file
            QSortListIO savePubSort(PUBORDER_SAVE);
            savePubSort.saveList(allPubOrders);
        }
        delete sortdialog;
    } else {
        QMessageBox::critical(this, "Missing File", "Please load a file first.");
    }
}

void MainWindow::on_pres_new_sort_clicked() {
    if (presdb != NULL) {
        CustomSort* sortdialog = new CustomSort();
        sortdialog->setFields(PRES_MANFIELDS);
        int ret = sortdialog->exec();
        if (ret) {
            QStringList newSortOrder = sortdialog->getSortFields();
            allPresOrders << newSortOrder;
            ui->pres_sort->addItem(newSortOrder.at(0));

            // save the sort fields to file
            QSortListIO savePresSort(PRESORDER_SAVE);
            savePresSort.saveList(allPresOrders);
        }
        delete sortdialog;
    } else {
        QMessageBox::critical(this, "Missing File", "Please load a file first.");
    }
}

void MainWindow::on_fund_new_sort_clicked() {
    if (funddb != NULL) {
        CustomSort* sortdialog = new CustomSort();
        sortdialog->setFields(GRANTS_MANFIELDS);
        int ret = sortdialog->exec();
        if (ret) {
            QStringList newSortOrder = sortdialog->getSortFields();
            allFundOrders << newSortOrder;
            ui->fund_sort->addItem(newSortOrder.at(0));

            // save the sort fields to file
            QSortListIO saveFundSort(FUNDORDER_SAVE);
            saveFundSort.saveList(allFundOrders);
        }
        delete sortdialog;
    } else {
        QMessageBox::critical(this, "Missing File", "Please load a file first.");
    }
}

void MainWindow::on_teach_sort_currentIndexChanged(int index) {
    if(index != -1) {
        QStringList sortOrder = allTeachOrders[index];
        teachSortOrder.clear();
        for (int i = 1; i < sortOrder.size(); i++) {
            teachSortOrder.emplace_back(sortOrder[i].toStdString());
        }
        ui->teach_filter->setText(QString::fromStdString(teachSortOrder[0]));
        refresh(TEACH);
    }
}

void MainWindow::on_pub_sort_currentIndexChanged(int index) {
    if(index != -1) {
        QStringList sortOrder = allPubOrders[index];
        pubSortOrder.clear();
        for (int i = 1; i < sortOrder.size(); i++) {
            pubSortOrder.emplace_back(sortOrder[i].toStdString());
        }
        ui->pub_filter->setText(QString::fromStdString(pubSortOrder[0]));
        refresh(PUBLICATIONS);
    }
}

void MainWindow::on_pres_sort_currentIndexChanged(int index) {
    if(index != -1) {
        QStringList sortOrder = allPresOrders[index];
        presSortOrder.clear();
        for (int i = 1; i < sortOrder.size(); i++) {
            presSortOrder.emplace_back(sortOrder[i].toStdString());
        }
        ui->pres_filter->setText(QString::fromStdString(presSortOrder[0]));
        refresh(PRESENTATIONS);
    }
}

void MainWindow::on_fund_sort_currentIndexChanged(int index) {
    if(index != -1) {
        QStringList sortOrder = allFundOrders[index];
        fundSortOrder.clear();
        for (int i = 1; i < sortOrder.size(); i++) {
            fundSortOrder.emplace_back(sortOrder[i].toStdString());
        }
        ui->fund_filter->setText(QString::fromStdString(fundSortOrder[0]));
        refresh(FUNDING);
    }
}

void MainWindow::on_teach_delete_sort_clicked() {
    if (ui->teach_sort->currentIndex()!=0) {
        QMessageBox prompt;
        prompt.setText("Are you sure you want to delete " + ui->teach_sort->currentText() + "?");
        prompt.setStandardButtons(QMessageBox::Yes | QMessageBox::No);

        if (prompt.exec()==QMessageBox::Yes) {
            allTeachOrders.removeAt(ui->teach_sort->currentIndex());
            ui->teach_sort->removeItem(ui->teach_sort->currentIndex());

            QSortListIO saveTeachSort(TEACHORDER_SAVE);
            saveTeachSort.saveList(allTeachOrders);
        }
    } else {
        QMessageBox::critical(this, "", "Cannot delete Default");
    }
}

void MainWindow::on_pub_delete_sort_clicked() {
    if (ui->pub_sort->currentIndex()!=0) {
        QMessageBox prompt;
        prompt.setText("Are you sure you want to delete " + ui->pub_sort->currentText() + "?");
        prompt.setStandardButtons(QMessageBox::Yes | QMessageBox::No);

        if (prompt.exec()==QMessageBox::Yes) {
            allPubOrders.removeAt(ui->pub_sort->currentIndex());
            ui->pub_sort->removeItem(ui->pub_sort->currentIndex());

            QSortListIO savePubSort(PUBORDER_SAVE);
            savePubSort.saveList(allPubOrders);
        }
    } else {
        QMessageBox::critical(this, "", "Cannot delete Default");
    }
}

void MainWindow::on_pres_delete_sort_clicked() {
    if (ui->pres_sort->currentIndex()!=0) {
        QMessageBox prompt;
        prompt.setText("Are you sure you want to delete " + ui->pres_sort->currentText() + "?");
        prompt.setStandardButtons(QMessageBox::Yes | QMessageBox::No);

        if (prompt.exec()==QMessageBox::Yes) {
            allPresOrders.removeAt(ui->pres_sort->currentIndex());
            ui->pres_sort->removeItem(ui->pres_sort->currentIndex());

            QSortListIO savePresSort(PRESORDER_SAVE);
            savePresSort.saveList(allPresOrders);
        }
    } else {
        QMessageBox::critical(this, "", "Cannot delete Default");
    }
}

void MainWindow::on_fund_delete_sort_clicked() {
    if (ui->fund_sort->currentIndex()!=0) {
        QMessageBox prompt;
        prompt.setText("Are you sure you want to delete " + ui->fund_sort->currentText() + "?");
        prompt.setStandardButtons(QMessageBox::Yes | QMessageBox::No);

        if (prompt.exec()==QMessageBox::Yes) {
            allFundOrders.removeAt(ui->fund_sort->currentIndex());
            ui->fund_sort->removeItem(ui->fund_sort->currentIndex());

            QSortListIO saveFundSort(FUNDORDER_SAVE);
            saveFundSort.saveList(allFundOrders);
        }
    } else {
        QMessageBox::critical(this, "", "Cannot delete Default");
    }
}

// change pages in stack correspongding to the toggled chart button
void MainWindow::on_teach_bubble_button_toggled() { ui->teach_graph_stackedWidget->setCurrentIndex(3);}
void MainWindow::on_teach_line_button_toggled() { ui->teach_graph_stackedWidget->setCurrentIndex(2);}
void MainWindow::on_teach_bar_button_toggled() { ui->teach_graph_stackedWidget->setCurrentIndex(1);}
void MainWindow::on_teach_pie_button_toggled() { ui->teach_graph_stackedWidget->setCurrentIndex(0);}
void MainWindow::on_pub_bubble_button_toggled() { ui->pub_graph_stackedWidget->setCurrentIndex(3);}
void MainWindow::on_pub_line_button_toggled() { ui->pub_graph_stackedWidget->setCurrentIndex(2);}
void MainWindow::on_pub_bar_button_toggled() { ui->pub_graph_stackedWidget->setCurrentIndex(1);}
void MainWindow::on_pub_pie_button_toggled() { ui->pub_graph_stackedWidget->setCurrentIndex(0);}
void MainWindow::on_pres_bubble_button_toggled() { ui->pres_graph_stackedWidget->setCurrentIndex(3);}
void MainWindow::on_pres_line_button_toggled() { ui->pres_graph_stackedWidget->setCurrentIndex(2);}
void MainWindow::on_pres_bar_button_toggled() { ui->pres_graph_stackedWidget->setCurrentIndex(1);}
void MainWindow::on_pres_pie_button_toggled() { ui->pres_graph_stackedWidget->setCurrentIndex(0);}
void MainWindow::on_fund_bubble_button_toggled() { ui->fund_graph_stackedWidget->setCurrentIndex(3);}
void MainWindow::on_fund_line_button_toggled() { ui->fund_graph_stackedWidget->setCurrentIndex(2);}
void MainWindow::on_fund_bar_button_toggled() { ui->fund_graph_stackedWidget->setCurrentIndex(1);}
void MainWindow::on_fund_pie_button_toggled() { ui->fund_graph_stackedWidget->setCurrentIndex(0);}

void MainWindow::on_teach_load_file_clicked() {
    QString path = load_file();
    if (!path.isEmpty()) {
        load_teach(path);
    }
}

/*FOR TEST CASES
void MainWindow::teachLoadForTest(QString path) {
    if (!path.isEmpty()) {
        load_teach(path);
    }
}*/

bool MainWindow::load_teach(QString path, bool multi_file) {
    if (!checkFile(TEACH, path)) {
        // enable gui elements
        ui->teach_sort->setEnabled(true);
        ui->teach_delete_sort->setEnabled(true);
        ui->teach_new_sort->setEnabled(true);
        ui->teach_filter_from->setEnabled(true);
        ui->teach_filter_to->setEnabled(true);
        ui->teach_pie_button->setEnabled(true);
        ui->teach_bar_button->setEnabled(true);
        ui->teach_line_button->setEnabled(true);
        ui->teach_bubble_button->setEnabled(true);
        ui->teach_to_label->setEnabled(true);
        ui->teach_sort_label->setEnabled(true);
        ui->teach_filter->setEnabled(true);
        ui->teach_filter_label->setEnabled(true);

        // load save order
        QSortListIO teachSaveOrder(TEACHORDER_SAVE);
        allTeachOrders = teachSaveOrder.readList();
        ui->teach_sort->clear();
        for (int i = 0; i < allTeachOrders.size(); i++) {
            ui->teach_sort->addItem(allTeachOrders.at(i).at(0));
        }

        // create default sort order if none are loaded
        if (ui->teach_sort->currentIndex() < 0) {
            createDefaultSortOrder(TEACH);
            ui->teach_sort->addItem(allTeachOrders[0][0]);
        }

        // create the tree
        teachPath = path;
        //allows us to extract the file name from the path
        QFileInfo teachFile(path);
        QString teachFileName = teachFile.fileName();
        makeTree(TEACH);
        ui->teach_file_label->setText(teachFileName);

        return true;
    } else {
        if (!multi_file) {
            QMessageBox::critical(this, "Invalid File", "Not a valid teaching file.");
            on_teach_load_file_clicked();
        }
    }
    return false;
}

void MainWindow::on_pub_load_file_clicked() {
    QString path = load_file();
    if (!path.isEmpty()) {
        load_pub(path);
    }
}

/*FOR TEST CASES
void MainWindow::pubLoadForTest(QString path) {
    if (!path.isEmpty()) {
        load_pub(path);
    }
}*/

bool MainWindow::load_pub(QString path, bool multi_file) {
    if (!checkFile(PUBLICATIONS, path)) {
        // enable gui elements
        ui->pub_sort->setEnabled(true);
        ui->pub_delete_sort->setEnabled(true);
        ui->pub_new_sort->setEnabled(true);
        ui->pub_filter_from->setEnabled(true);
        ui->pub_filter_to->setEnabled(true);
        ui->pub_pie_button->setEnabled(true);
        ui->pub_bar_button->setEnabled(true);
        ui->pub_line_button->setEnabled(true);
        ui->pub_bubble_button->setEnabled(true);
        ui->pub_to_label->setEnabled(true);
        ui->pub_sort_label->setEnabled(true);
        ui->pub_filter->setEnabled(true);
        ui->pub_filter_label->setEnabled(true);

        // load save order
        QSortListIO pubSaveOrder(PUBORDER_SAVE);
        allPubOrders = pubSaveOrder.readList();
        ui->pub_sort->clear();
        for (int i = 0; i < allPubOrders.size(); i++) {
            ui->pub_sort->addItem(allPubOrders.at(i).at(0));
        }

        // create default sort order if none are loaded
        if (ui->pub_sort->currentIndex() < 0) {
            createDefaultSortOrder(PUBLICATIONS);
            ui->pub_sort->addItem(allPubOrders[0][0]);
        }

        // create the tree
        pubPath = path;

        //extract the file name from the path
        QFileInfo pubFile(path);
        QString pubFileName = pubFile.fileName();
        makeTree(PUBLICATIONS);
        ui->pub_file_label->setText(pubFileName);

        return true;
    } else {
        if (!multi_file) {
            QMessageBox::critical(this, "Invalid File", "Not a valid publications file.");
            on_pub_load_file_clicked();
        }
    }
    return false;
}

void MainWindow::on_pres_load_file_clicked() {
    QString path = load_file();
    if (!path.isEmpty()) {
        load_pres(path);
    }
}

/*FOR TEST CASES
void MainWindow::presLoadForTest(QString path) {
    if (!path.isEmpty()) {
        load_pres(path);
    }
}*/

bool MainWindow::load_pres(QString path, bool multi_file) {
    if (!checkFile(PRESENTATIONS, path)) {
        // enable gui elements
        ui->pres_sort->setEnabled(true);
        ui->pres_delete_sort->setEnabled(true);
        ui->pres_new_sort->setEnabled(true);
        ui->pres_filter_from->setEnabled(true);
        ui->pres_filter_to->setEnabled(true);
        ui->pres_pie_button->setEnabled(true);
        ui->pres_bar_button->setEnabled(true);
        ui->pres_line_button->setEnabled(true);
        ui->pres_bubble_button->setEnabled(true);
        ui->pres_to_label->setEnabled(true);
        ui->pres_sort_label->setEnabled(true);
        ui->pres_filter->setEnabled(true);
        ui->pres_filter_label->setEnabled(true);

        // load save order
        QSortListIO presSaveOrder(PRESORDER_SAVE);
        allPresOrders = presSaveOrder.readList();
        ui->pres_sort->clear();
        for (int i = 0; i < allPresOrders.size(); i++) {
            ui->pres_sort->addItem(allPresOrders.at(i).at(0));
        }

        // create default sort order if none are loaded
        if (ui->pres_sort->currentIndex() < 0) {
            createDefaultSortOrder(PRESENTATIONS);
            ui->pres_sort->addItem(allPresOrders[0][0]);
        }

        // create the tree
        presPath = path;

        //extract the file name from the path
        QFileInfo presFile(path);
        QString presFileName = presFile.fileName();
        makeTree(PRESENTATIONS);
        ui->pres_file_label->setText(presFileName);

        return true;
    } else {
        if (!multi_file) {
            QMessageBox::critical(this, "Invalid File", "Not a valid presentations file.");
            on_pres_load_file_clicked();
        }
    }
    return false;
}

void MainWindow::on_fund_load_file_clicked() {
    QString path = load_file();
    if (!path.isEmpty()) {
        load_fund(path);
    }
}
/*FOR TEST CASES
void MainWindow::fundLoadForTest(QString path) {
    if (!path.isEmpty()) {
        load_fund(path);
    }
}*/

bool MainWindow::load_fund(QString path, bool multi_file) {
    if (!checkFile(FUNDING, path)) {
        // enable gui elements
        ui->fund_sort->setEnabled(true);
        ui->fund_delete_sort->setEnabled(true);
        ui->fund_new_sort->setEnabled(true);
        ui->fund_filter_from->setEnabled(true);
        ui->fund_filter_to->setEnabled(true);
        ui->fund_pie_button->setEnabled(true);
        ui->fund_bar_button->setEnabled(true);
        ui->fund_line_button->setEnabled(true);
        ui->fund_bubble_button->setEnabled(true);
        ui->fund_to_label->setEnabled(true);
        ui->fund_sort_label->setEnabled(true);
        ui->fund_filter->setEnabled(true);
        ui->fund_filter_label->setEnabled(true);

        // load save order
        QSortListIO fundSaveOrder(FUNDORDER_SAVE);
        allFundOrders = fundSaveOrder.readList();
        ui->fund_sort->clear();
        for (int i = 0; i < allFundOrders.size(); i++) {
            ui->fund_sort->addItem(allFundOrders.at(i).at(0));
        }

        // create default sort order if none are loaded
        if (ui->fund_sort->currentIndex() < 0) {
            createDefaultSortOrder(FUNDING);
            ui->fund_sort->addItem(allFundOrders[0][0]);
        }

        // create the tree
        fundPath = path;
        //extracts the file name from the path
        QFileInfo fundFile(path);
        QString fundFileName = fundFile.fileName();
        makeTree(FUNDING);
        ui->fund_file_label->setText(fundFileName);

        return true;
    } else {
        if (!multi_file) {
            QMessageBox::critical(this, "Invalid File", "Not a valid grants and funding file.");
            on_fund_load_file_clicked();
        }
    }
    return false;
}

void MainWindow::on_FromDate_dateChanged(const QDate &date) {
    // set the member variable to the new date
    yearStart = date.year();

    // update end date spinbox to not fall below that year
    ui->ToDate->setMinimumDate(date);

    dateChanged = {true, true, true, true};

    // refresh the GUI
    refresh(ui->categoryTab->currentIndex());
}

void MainWindow::on_ToDate_dateChanged(const QDate &date) {
    // set the member variable to the new date
    yearEnd = date.year();

    // update end date spinbox to not fall below that year
    ui->ToDate->setMinimumDate(ui->FromDate->date());

    dateChanged = {true, true, true, true};

    // refresh the GUI
    refresh(ui->categoryTab->currentIndex());
}

void MainWindow::on_categoryTab_currentChanged() {
    if (dateChanged[ui->categoryTab->currentIndex()] == true) {
        refresh(ui->categoryTab->currentIndex());
        dateChanged[ui->categoryTab->currentIndex()] = false;
    }
}

void MainWindow::on_teachTreeView_clicked(const QModelIndex &index) {
    QString clickedName = index.data(Qt::DisplayRole).toString();
    teachModelIndex = index;
    if (clickedName==teachClickedName || index.column()!=0) { return;}

    std::vector<std::string> parentsList;
    QModelIndex current = index;
    QString name;
    while (true) {
        name = current.data(Qt::DisplayRole).toString();
        if(name!="") {
            auto it = parentsList.begin();
            it = parentsList.insert(it, name.toStdString());
        } else {
            break;
        }
        current = current.parent();
    }

    if (parentsList.size()!=teachSortOrder.size()) {
        teachClickedName = clickedName;
        std::vector<std::string> sortOrder(teachSortOrder.begin(), teachSortOrder.begin()+parentsList.size()+1);
        std::vector<std::pair <std::string, int>> list =
                teachdb->getCountTuple(yearStart, yearEnd, sortOrder, parentsList, getFilterStartChar(TEACH), getFilterEndChar(TEACH));
        std::vector<std::pair <std::string, double>> chartList;
        for (int i = 0; i < (int) list.size(); i++) {
            chartList.emplace_back(list[i].first, static_cast<double>(list[i].second));
        }

        if (!chartList.empty()) {// plotting chart if chart list is not empty
            // bar chart
            ui->teachBarChart->clearPlottables();
            setupBarChart(ui->teachBarChart, chartList);
            ui->teachBarChart->replot();

            // line chart
            ui->teachLineChart->clearPlottables();
            setupLineChart(ui->teachLineChart, chartList);
            ui->teachLineChart->replot();

            // bubble chart
            ui->teachBubbleChart->clearPlottables();
            setupBubbleChart(ui->teachBubbleChart, chartList);
            ui->teachBubbleChart->replot();

            // pie chart
            setupPieChart(ui->teachPieChart, ui->teachPieList, chartList);

            // set up chart name
            if (parentsList.size()>1) {
                ui->teachGraphTitle->setText("Total " + clickedName + " Teaching by " +
                                             QString::fromStdString(teachSortOrder[parentsList.size()]) + " for " + QString::fromStdString(parentsList[0]));
            } else {
                ui->teachGraphTitle->setText("Total Teaching by " + QString::fromStdString(parentsList[0]));
            }
            ui->teach_graph_stackedWidget->show();
        }
    } else { // if chart list is empty, clear page
        ui->teach_graph_stackedWidget->hide();
        ui->teachGraphTitle->clear();
        teachClickedName.clear();
    }
}

void MainWindow::on_pubTreeView_clicked(const QModelIndex &index) {
    QString clickedName = index.data(Qt::DisplayRole).toString();
    pubModelIndex = index;
    if (clickedName==pubClickedName || index.column()!=0) { return;}

    std::vector<std::string> parentsList;
    QModelIndex current = index;
    QString name;
    while (true) {
        name = current.data(Qt::DisplayRole).toString();
        if(name!="") {
            auto it = parentsList.begin();
            it = parentsList.insert(it, name.toStdString());
        } else {
            break;
        }
        current = current.parent();
    }

    if (parentsList.size()!=pubSortOrder.size()) {
        pubClickedName = clickedName;
        std::vector<std::string> sortOrder(pubSortOrder.begin(), pubSortOrder.begin()+parentsList.size()+1);
        std::vector<std::pair <std::string, int>> list =
                pubdb->getCountTuple(yearStart, yearEnd, sortOrder, parentsList, getFilterStartChar(PUBLICATIONS), getFilterEndChar(PUBLICATIONS));
        std::vector<std::pair <std::string, double>> chartList;
        for (int i = 0; i < (int) list.size(); i++) {
            chartList.emplace_back(list[i].first, static_cast<double>(list[i].second));
        }

        if (!chartList.empty()) {// plotting chart if chart list is not empty
            // bar chart
            ui->pubBarChart->clearPlottables();
            setupBarChart(ui->pubBarChart, chartList);
            ui->pubBarChart->replot();

            //line chart
            ui->pubLineChart->clearPlottables();
            setupLineChart(ui->pubLineChart, chartList);
            ui->pubLineChart->replot();

            // bubble chart
            ui->pubBubbleChart->clearPlottables();
            setupBubbleChart(ui->pubBubbleChart, chartList);
            ui->pubBubbleChart->replot();

            // pie chart
            setupPieChart(ui->pubPieChart, ui->pubPieList, chartList);

            // set up chart name
            if (parentsList.size()>1) {
                ui->pubGraphTitle->setText("Total " + clickedName + " Publications by " +
                                           QString::fromStdString(pubSortOrder[parentsList.size()]) + " for " + QString::fromStdString(parentsList[0]));
            } else {
                ui->pubGraphTitle->setText("Total Publications by " + QString::fromStdString(parentsList[0]));
            }
            ui->pub_graph_stackedWidget->show();
        }
    } else {// if chart list is empty, clear page
        ui->pub_graph_stackedWidget->hide();
        ui->pubGraphTitle->clear();
        pubClickedName.clear();
    }
}

void MainWindow::on_presTreeView_clicked(const QModelIndex &index) {
    QString clickedName = index.data(Qt::DisplayRole).toString();
    presModelIndex = index;
    if (clickedName==presClickedName || index.column()!=0) { return;}

    std::vector<std::string> parentsList;
    QModelIndex current = index;
    QString name;
    while (true) {
        name = current.data(Qt::DisplayRole).toString();
        if(name!="") {
            auto it = parentsList.begin();
            it = parentsList.insert(it, name.toStdString());
        } else {
            break;
        }
        current = current.parent();
    }

    if (parentsList.size()!=presSortOrder.size()) {
        presClickedName = clickedName;
        std::vector<std::string> sortOrder(presSortOrder.begin(), presSortOrder.begin()+parentsList.size()+1);
        std::vector<std::pair <std::string, int>> list =
                presdb->getCountTuple(yearStart, yearEnd, sortOrder, parentsList, getFilterStartChar(PRESENTATIONS), getFilterEndChar(PRESENTATIONS));
        std::vector<std::pair <std::string, double>> chartList;
        for (int i = 0; i < (int) list.size(); i++) {
            chartList.emplace_back(list[i].first, static_cast<double>(list[i].second));
        }

        if (!chartList.empty()) {// plotting chart if chart list is not empty
            // bar chart
            ui->presBarChart->clearPlottables();
            setupBarChart(ui->presBarChart, chartList);
            ui->presBarChart->replot();

            // line chart
            ui->presLineChart->clearPlottables();
            setupLineChart(ui->presLineChart, chartList);
            ui->presLineChart->replot();

            // bubble chat
            ui->presBubbleChart->clearPlottables();
            setupBubbleChart(ui->presBubbleChart, chartList);
            ui->presBubbleChart->replot();

            //pie chart
            setupPieChart(ui->presPieChart, ui->presPieList, chartList);

            // set up chart name
            if (parentsList.size()>1) {
                ui->presGraphTitle->setText("Total " + clickedName + " Presentations by " +
                                            QString::fromStdString(presSortOrder[parentsList.size()]) + " for " + QString::fromStdString(parentsList[0]));
            } else {
                ui->presGraphTitle->setText("Total Presentations by " + QString::fromStdString(parentsList[0]));
            }
            ui->pres_graph_stackedWidget->show();
        }
    } else {// if chart list is empty, clear page
        ui->pres_graph_stackedWidget->hide();
        ui->presGraphTitle->clear();
        presClickedName.clear();
    }
}

void MainWindow::on_fundTreeView_clicked(const QModelIndex &index) {
    QString clickedName = index.data(Qt::DisplayRole).toString();
    fundModelIndex = index;
    if (clickedName==fundClickedName || index.column()!=0) { return;}

    std::vector<std::string> parentsList;
    QModelIndex current = index;
    QString name;
    while (true) {
        name = current.data(Qt::DisplayRole).toString();
        if(name!="") {
            auto it = parentsList.begin();
            it = parentsList.insert(it, name.toStdString());
        } else {
            break;
        }
        current = current.parent();
    }

    if (parentsList.size()!=fundSortOrder.size()) {
        if (clickedName != fundClickedName) {
            fundClickedName = clickedName;
            std::vector<std::string> sortOrder(fundSortOrder.begin(), fundSortOrder.begin()+parentsList.size()+1);
            std::vector<std::pair <std::string, double>> chartList =
                    funddb->getTotalsTuple(yearStart, yearEnd, sortOrder, parentsList, "Total Amount", getFilterStartChar(FUNDING), getFilterEndChar(FUNDING));

            if (!chartList.empty()) {// plotting chart if chart list is not empty
                //bar chart
                ui->fundBarChart->clearPlottables();
                setupBarChart(ui->fundBarChart, chartList);
                ui->fundBarChart->replot();

                // line chart
                ui->fundLineChart->clearPlottables();
                setupLineChart(ui->fundLineChart, chartList);
                ui->fundLineChart->replot();

                //bubble chart
                ui->fundBubbleChart->clearPlottables();
                setupBubbleChart(ui->fundBubbleChart, chartList);
                ui->fundBubbleChart->replot();

                // pie chart
                setupPieChart(ui->fundPieChart, ui->fundPieList, chartList);

                // set up chart name
                if (parentsList.size()>1) {
                    ui->fundGraphTitle->setText("Total " + clickedName + " Grants & Funding by " +
                                                QString::fromStdString(fundSortOrder[parentsList.size()]) + " for " + QString::fromStdString(parentsList[0]));
                } else {
                    ui->fundGraphTitle->setText("Total Grants & Funding by " + QString::fromStdString(parentsList[0]));
                }
                ui->fund_graph_stackedWidget->show();
            }
        } else {// if chart list is empty, clear page
            ui->fund_graph_stackedWidget->hide();
            ui->fundGraphTitle->clear();
            fundClickedName.clear();
        }
    }
}

/*
 * User Selected List block
 *
 */

//TEACH

void MainWindow::on_customListAddTeach_clicked(){
    customListTeach.addModelIndex(teachModelIndex);
}

void MainWindow::on_customListRemoveTeach_clicked(){
    QModelIndex parent;
    customListTeach.removeModelIndex();
    ui->teachTreeView->setRowHidden(customListTeach.getLength(), parent, true);
    on_customListGraphTeach_clicked();
}

void MainWindow::on_customListClearTeach_clicked(){
    if (customListTeach.getLength() == 0){return;}
    customListTeach.clearModelIndex();
    QModelIndex parent;
    for(int i = 0; i < ui->teachTreeView->model()->rowCount(); i++){ //Hardcoded to 10000, need to find an appropriate variable here
        ui->teachTreeView->model()->rowCount();
        ui->teachTreeView->setRowHidden(i, parent, true);
    }
    on_customListGraphTeach_clicked();
}

void MainWindow::on_customListShowTeach_clicked(){
    if (customListTeach.getLength() == 0){return;}
        std::vector<int> rowsToAvoid;
        QModelIndex parent;
        for(int i = 0; i < customListTeach.getLength(); i++){
            QModelIndex temp = customListTeach.getModelIndex(i);
            parent = temp.parent();
            rowsToAvoid.push_back(temp.row());
        }
        // hide all rows
        for(int i = 0; i < ui->teachTreeView->model()->rowCount(); i++){ //Hardcoded to 10000, need to find an appropriate variable here
            ui->teachTreeView->model()->rowCount();
            ui->teachTreeView->setRowHidden(i, parent, true);
        }
        // unhide elements in list
        for(int j = 0; j < rowsToAvoid.size(); j++){
            ui->teachTreeView->setRowHidden(rowsToAvoid[j], parent, false);
        }
        //inefficient old code
       /* for(int i = 0; i < 10000; i++){ //Hardcoded to 10000, need to find an appropriate variable here
            bool check = true;
            for(int j = 0; j < rowsToAvoid.size(); j++){
                if(i == rowsToAvoid[j]){
                    check = false;
                }
            }
            if(check){
                currentView->setRowHidden(i, parent, true);
            }
        }*/
}
void MainWindow::on_defaultListShowTeach_clicked(){
    ui->teachTreeView->reset();
}


void MainWindow::on_customListGraphTeach_clicked(){

    std::vector<std::pair <std::string, double>> chartList;

    for(int i = 0; i < customListTeach.getLength(); i++){

        QModelIndex current = customListTeach.getModelIndex(i);
        QModelIndex totals = current.sibling(current.row(),current.column()+2);
        double children = totals.data(Qt::DisplayRole).toDouble();

        QString tempString = current.data(Qt::DisplayRole).toString();
        std::string name = tempString.toStdString();
        chartList.emplace_back(name, children);

    }

    if (!chartList.empty()) {// plotting chart if chart list is not empty
        // bar chart
        ui->teachBarChart->clearPlottables();
        setupBarChart(ui->teachBarChart, chartList);
        ui->teachBarChart->replot();

        //line chart
        ui->teachLineChart->clearPlottables();
        setupLineChart(ui->teachLineChart, chartList);
        ui->teachLineChart->replot();

        // bubble chart
        ui->teachBubbleChart->clearPlottables();
        setupBubbleChart(ui->teachBubbleChart, chartList);
        ui->teachBubbleChart->replot();

        // pie chart
        setupPieChart(ui->teachPieChart, ui->teachPieList, chartList);

        // set up chart name
        if (customListTeach.getLength()>=1) {
            ui->teachGraphTitle->setText("Total Teaching Hours by " + QString::fromStdString(teachSortOrder[0]) + " for your custom list");
        } else {
            ui->teachGraphTitle->setText("Total Teaching");
        }
        ui->teach_graph_stackedWidget->show();
        //}
    } else {// if chart list is empty, clear page
        ui->teach_graph_stackedWidget->hide();
        ui->teachGraphTitle->clear();
        teachClickedName.clear();
    }

}


//FUND

void MainWindow::on_customListAddFund_clicked(){
    customListFund.addModelIndex(fundModelIndex);
}

void MainWindow::on_customListRemoveFund_clicked(){
    QModelIndex parent;
    customListFund.removeModelIndex();
    ui->fundTreeView->setRowHidden(customListFund.getLength(), parent, true);
    on_customListGraphFund_clicked();

}

void MainWindow::on_customListClearFund_clicked(){
    if (customListFund.getLength() == 0){return;}
    customListFund.clearModelIndex();
    QModelIndex parent;
    for(int i = 0; i < ui->fundTreeView->model()->rowCount(); i++){ //Hardcoded to 10000, need to find an appropriate variable here
        ui->fundTreeView->model()->rowCount();
        ui->fundTreeView->setRowHidden(i, parent, true);
    }
    on_customListGraphFund_clicked();
}

void MainWindow::on_customListShowFund_clicked(){
    if (customListFund.getLength() == 0){return;}

        std::vector<int> rowsToAvoid;
        QModelIndex parent;
        for(int i = 0; i < customListFund.getLength(); i++){
            QModelIndex temp = customListFund.getModelIndex(i);
            parent = temp.parent();
            rowsToAvoid.push_back(temp.row());
        }
        // hide all rows
        for(int i = 0; i < ui->fundTreeView->model()->rowCount(); i++){ //Hardcoded to 10000, need to find an appropriate variable here
            ui->fundTreeView->setRowHidden(i, parent, true);
        }
        // unhide elements in list
        for(int j = 0; j < rowsToAvoid.size(); j++){
            ui->fundTreeView->setRowHidden(rowsToAvoid[j], parent, false);
        }
}
void MainWindow::on_defaultListShowFund_clicked(){
    ui->fundTreeView->reset();
}

void MainWindow::on_customListGraphFund_clicked(){

    std::vector<std::pair <std::string, double>> chartList;

    for(int i = 0; i < customListFund.getLength(); i++){

        QModelIndex current = customListFund.getModelIndex(i);
        QModelIndex totals = current.sibling(current.row(),current.column()+2);
        std::string totalsString = totals.data(Qt::DisplayRole).toString().toStdString();
        std::string newTotals;
        for(std::string::size_type i = 0; i < totalsString.size(); ++i) {
            if (totalsString[i] != '$' && totalsString[i] != ','){
                newTotals.push_back(totalsString[i]);
            }
        }
        double children = std::stod(newTotals);

        QString tempString = current.data(Qt::DisplayRole).toString();
        std::string name = tempString.toStdString();
        chartList.emplace_back(name, children);

    }

    if (!chartList.empty()) {// plotting chart if chart list is not empty
        // bar chart
        ui->fundBarChart->clearPlottables();
        setupBarChart(ui->fundBarChart, chartList);
        ui->fundBarChart->replot();

        //line chart
        ui->fundLineChart->clearPlottables();
        setupLineChart(ui->fundLineChart, chartList);
        ui->fundLineChart->replot();

        // bubble chart
        ui->fundBubbleChart->clearPlottables();
        setupBubbleChart(ui->fundBubbleChart, chartList);
        ui->fundBubbleChart->replot();

        // pie chart
        setupPieChart(ui->fundPieChart, ui->fundPieList, chartList);

        // set up chart name
        if (customListFund.getLength()>=1) {
            ui->fundGraphTitle->setText("Total Funding by " + QString::fromStdString(fundSortOrder[0]) + " for your custom list");
        } else {
            ui->fundGraphTitle->setText("Total Funding");
        }
        ui->fund_graph_stackedWidget->show();
        //}
    } else {// if chart list is empty, clear page
        ui->fund_graph_stackedWidget->hide();
        ui->fundGraphTitle->clear();
        fundClickedName.clear();
    }

}


//PUB


void MainWindow::on_customListAddPub_clicked(){
    customListPub.addModelIndex(pubModelIndex);
}

void MainWindow::on_customListRemovePub_clicked(){
    QModelIndex parent;
    customListPub.removeModelIndex();
    ui->pubTreeView->setRowHidden(customListPub.getLength(), parent, true);
    on_customListGraphPub_clicked();

}

void MainWindow::on_customListClearPub_clicked(){
    if (customListPub.getLength() == 0){return;}
    customListPub.clearModelIndex();
    QModelIndex parent;
    for(int i = 0; i < ui->pubTreeView->model()->rowCount(); i++){ //Hardcoded to 10000, need to find an appropriate variable here
        ui->pubTreeView->model()->rowCount();
        ui->pubTreeView->setRowHidden(i, parent, true);
    }
    on_customListGraphPub_clicked();
}

void MainWindow::on_customListShowPub_clicked(){
    if (customListPub.getLength() == 0){return;}
        std::vector<int> rowsToAvoid;
        QModelIndex parent;
        for(int i = 0; i < customListPub.getLength(); i++){
            QModelIndex temp = customListPub.getModelIndex(i);
            parent = temp.parent();
            rowsToAvoid.push_back(temp.row());
        }
        // hide all rows
        for(int i = 0; i < ui->pubTreeView->model()->rowCount(); i++){ //Hardcoded to 10000, need to find an appropriate variable here
            ui->pubTreeView->setRowHidden(i, parent, true);
        }
        // unhide elements in list
        for(int j = 0; j < rowsToAvoid.size(); j++){
            ui->pubTreeView->setRowHidden(rowsToAvoid[j], parent, false);
        }
}
void MainWindow::on_defaultListShowPub_clicked(){
    ui->pubTreeView->reset();
}


void MainWindow::on_customListGraphPub_clicked(){

    std::vector<std::pair <std::string, double>> chartList;

    for(int i = 0; i < customListPub.getLength(); i++){

        QModelIndex current = customListPub.getModelIndex(i);
        QModelIndex totals = current.sibling(current.row(),current.column()+1);
        double children = totals.data(Qt::DisplayRole).toDouble();

        QString tempString = current.data(Qt::DisplayRole).toString();
        std::string name = tempString.toStdString();
        chartList.emplace_back(name, children);

    }

    if (!chartList.empty()) {// plotting chart if chart list is not empty
        // bar chart
        ui->pubBarChart->clearPlottables();
        setupBarChart(ui->pubBarChart, chartList);
        ui->pubBarChart->replot();

        //line chart
        ui->pubLineChart->clearPlottables();
        setupLineChart(ui->pubLineChart, chartList);
        ui->pubLineChart->replot();

        // bubble chart
        ui->pubBubbleChart->clearPlottables();
        setupBubbleChart(ui->pubBubbleChart, chartList);
        ui->pubBubbleChart->replot();

        // pie chart
        setupPieChart(ui->pubPieChart, ui->pubPieList, chartList);

        // set up chart name
        if (customListPub.getLength()>=1) {
            ui->pubGraphTitle->setText("Total Publications by " + QString::fromStdString(pubSortOrder[0]) + " for your custom list");
        } else {
            ui->pubGraphTitle->setText("Total Publications");
        }
        ui->pub_graph_stackedWidget->show();
        //}
    } else {// if chart list is empty, clear page
        ui->pub_graph_stackedWidget->hide();
        ui->pubGraphTitle->clear();
        pubClickedName.clear();
    }

}

//PRES


void MainWindow::on_customListAddPres_clicked(){
    customListPres.addModelIndex(presModelIndex);
}

void MainWindow::on_customListRemovePres_clicked(){
    QModelIndex parent;
    customListPres.removeModelIndex();
    ui->presTreeView->setRowHidden(customListPres.getLength(), parent, true);
    on_customListGraphPres_clicked();

}

void MainWindow::on_customListClearPres_clicked(){
    if (customListPres.getLength() == 0){return;}
    customListPres.clearModelIndex();
    QModelIndex parent;
    for(int i = 0; i < ui->presTreeView->model()->rowCount(); i++){ //Hardcoded to 10000, need to find an appropriate variable here
        ui->presTreeView->model()->rowCount();
        ui->presTreeView->setRowHidden(i, parent, true);
    }
    on_customListGraphPres_clicked();
}

void MainWindow::on_customListShowPres_clicked(){
    if (customListPres.getLength() == 0){return;}
        std::vector<int> rowsToAvoid;
        QModelIndex parent;
        for(int i = 0; i < customListPres.getLength(); i++){
            QModelIndex temp = customListPres.getModelIndex(i);
            parent = temp.parent();
            rowsToAvoid.push_back(temp.row());
        }
        // hide all rows
        for(int i = 0; i < ui->presTreeView->model()->rowCount(); i++){ //Hardcoded to 10000, need to find an appropriate variable here
            ui->presTreeView->setRowHidden(i, parent, true);
        }
        // unhide elements in list
        for(int j = 0; j < rowsToAvoid.size(); j++){
            ui->presTreeView->setRowHidden(rowsToAvoid[j], parent, false);
        }
}
void MainWindow::on_defaultListShowPres_clicked(){
    ui->presTreeView->reset();
}

void MainWindow::on_customListGraphPres_clicked(){

    std::vector<std::pair <std::string, double>> chartList;

    for(int i = 0; i < customListPres.getLength(); i++){

        QModelIndex current = customListPres.getModelIndex(i);
        QModelIndex totals = current.sibling(current.row(),current.column()+1);
        double children = totals.data(Qt::DisplayRole).toDouble();

        QString tempString = current.data(Qt::DisplayRole).toString();
        std::string name = tempString.toStdString();
        chartList.emplace_back(name, children);

    }

    if (!chartList.empty()) {// plotting chart if chart list is not empty
        // bar chart
        ui->presBarChart->clearPlottables();
        setupBarChart(ui->presBarChart, chartList);
        ui->presBarChart->replot();

        //line chart
        ui->presLineChart->clearPlottables();
        setupLineChart(ui->presLineChart, chartList);
        ui->presLineChart->replot();

        // bubble chart
        ui->presBubbleChart->clearPlottables();
        setupBubbleChart(ui->presBubbleChart, chartList);
        ui->presBubbleChart->replot();

        // pie chart
        setupPieChart(ui->presPieChart, ui->presPieList, chartList);

        // set up chart name
        if (customListPres.getLength()>=1) {
            ui->presGraphTitle->setText("Total Presentations by " + QString::fromStdString(presSortOrder[0]) + " for your custom list");
        } else {
            ui->presGraphTitle->setText("Total Presentations");
        }
        ui->pres_graph_stackedWidget->show();
        //}
    } else {// if chart list is empty, clear page
        ui->pres_graph_stackedWidget->hide();
        ui->presGraphTitle->clear();
        presClickedName.clear();
    }

}


/*
 * User Selected List block
 *
 */
void MainWindow::on_teachPrintButton_clicked()
{
    QPrintDialog printDialog(printer, this);
    if (printDialog.exec() == QDialog::Accepted) {
        QCPPainter painter;
        painter.begin(printer);
        ui->teachChartFrame->render(&painter);
    }
}

void MainWindow::on_fundPrintButton_clicked()
{
    QPrintDialog printDialog(printer, this);
    if (printDialog.exec() == QDialog::Accepted) {
        QCPPainter painter;
        painter.begin(printer);
        ui->fundChartFrame->render(&painter);
    }
}

void MainWindow::on_presPrintButton_clicked()
{
    QPrintDialog printDialog(printer, this);
    if (printDialog.exec() == QDialog::Accepted) {
        QCPPainter painter;
        painter.begin(printer);
        ui->presChartFrame->render(&painter);
    }
}

void MainWindow::on_pubPrintButton_clicked()
{
    QPrintDialog printDialog(printer, this);
    if (printDialog.exec() == QDialog::Accepted) {
        QCPPainter painter;
        painter.begin(printer);
        ui->pubChartFrame->render(&painter);
    }
}

void MainWindow::on_teachExportButton_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Export File"),
                                                    QDir::homePath(),
                                                    tr("PDF (*.pdf)"));
    if (fileName.contains("") != 0) {
        QPdfWriter writer(fileName);
        writer.setPageOrientation(QPageLayout::Landscape);
        QPainter painter;
        painter.begin(&writer);
        painter.scale(10.0, 10.0);
        ui->teachChartFrame->render(&painter);
        /* Another option for bar chart since it is QCustom plot
        if (ui->teach_bar_button->isChecked()) {
            ui->teachBarChart->savePdf(fileName);
        } */
    }

}

void MainWindow::on_fundExportButton_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Export File"),
                                                    QDir::homePath(),
                                                    tr("PDF (*.pdf)"));
    if (fileName.contains("") != 0) {
        QPdfWriter writer(fileName);
        writer.setPageOrientation(QPageLayout::Landscape);
        QPainter painter;
        painter.begin(&writer);
        painter.scale(10.0, 10.0);
        ui->fundChartFrame->render(&painter);
    }
}

void MainWindow::on_presExportButton_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Export File"),
                                                    QDir::homePath(),
                                                    tr("PDF (*.pdf)"));
    if (fileName.contains("") != 0) {
        QPdfWriter writer(fileName);
        writer.setPageOrientation(QPageLayout::Landscape);
        QPainter painter;
        painter.begin(&writer);
        painter.scale(10.0, 10.0);
        ui->presChartFrame->render(&painter);
    }
}

void MainWindow::on_pubExportButton_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Export File"),
                                                    QDir::homePath(),
                                                    tr("PDF (*.pdf)"));
    if (fileName.contains("") != 0) {
        QPdfWriter writer(fileName);
        writer.setPageOrientation(QPageLayout::Landscape);
        QPainter painter;
        painter.begin(&writer);
        painter.scale(10.0, 10.0);
        ui->pubChartFrame->render(&painter);
    }
}


char MainWindow::getFilterStartChar(int type) {
    char charInField;

    // get char from the text field
    switch (type) {
    case FUNDING:
        charInField = ui->fund_filter_from->text().toStdString()[0];
        break;
    case PRESENTATIONS:
        charInField = ui->pres_filter_from->text().toStdString()[0];
        break;
    case PUBLICATIONS:
        charInField = ui->pub_filter_from->text().toStdString()[0];
        break;
    case TEACH:
        charInField = ui->teach_filter_from->text().toStdString()[0];
        break;
    }

    // convert the char to uppercase
    char uppercase = charInField & ~0x20;

    // if alphabetical, return that letter
    if ('A' <= uppercase && uppercase <= 'Z') {
        return uppercase;
    } else {
        // otherwise, default is '*'
        return '*';
    }
}

char MainWindow::getFilterEndChar(int type) {
    char charInField;

    // get char from the text field
    switch (type) {
    case FUNDING:
        charInField = ui->fund_filter_to->text().toStdString()[0];
        break;
    case PRESENTATIONS:
        charInField = ui->pres_filter_to->text().toStdString()[0];
        break;
    case PUBLICATIONS:
        charInField = ui->pub_filter_to->text().toStdString()[0];
        break;
    case TEACH:
        charInField = ui->teach_filter_to->text().toStdString()[0];
        break;
    }

    // convert the char to uppercase
    char uppercase = charInField & ~0x20;

    // if alphabetical, return that letter
    if ('A' <= uppercase && uppercase <= 'Z') {
        return uppercase;
    } else if (charInField == '*') {
        // otherwise, is it '*'?
        return charInField;
    } else {
        // otherwise, default is 'Z'
        return 'Z';
    }
}

/**
 * Handles the closing of the main window. Gives the user
 * a choice as to whether or not they wish to save the state
 * of the application.
 * @param event called when the user closes the main window
 */
void MainWindow::closeEvent (QCloseEvent *event){
    QMessageBox::StandardButton resBtn = QMessageBox::question( this, "Save Session?",
                                                                tr("Would you like to save your session progress?\n"),
                                                                QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes,
                                                                QMessageBox::Yes);

    if (resBtn == QMessageBox::Cancel) {
        event->ignore();

    } else if(resBtn == QMessageBox::No) {
        event->accept();
    }
    else{
        //save session state code
        this->saveState();
        qApp->quit();
    }
}

/**
 * Saves the session state and stores it in a file.
 *
 * @return file.fileName() a QString representing the file
 *                         that stores the save session
 */
QString MainWindow::saveState()
{
    QFile file(sessionName());
        if (file.open(QIODevice::WriteOnly))

        {
            QTextStream out(&file);
            out << this->previousTeachingFile << "\r\n";
            out << this->previousGrantsFile << "\r\n";
            out << this->previousPresentationsFile << "\r\n";
            out << this->previousPublicationsFile << "\r\n";

        }
        saveDate();

        return file.fileName();       
}

/**
 * Saves a session's user-selected date values.
 * @return file.fileName() a string representing the file
 *                         that stores the saved dates
 */
QString MainWindow::saveDate()
{
    QFile file(this->dateFile());
        if (file.open(QIODevice::WriteOnly))
        {
            QTextStream out(&file);
            out << this->getYearStart() << "\r\n";
            out << this->getYearEnd() << "\r\n";
        }

        return file.fileName();
}

/**
 * Restores the previous session's dates.
 */
void MainWindow::restoreDate()
{
    CSVReader reader;
    QFile file(this->dateFile());
    if (file.open(QIODevice::ReadOnly))
    {
        QTextStream in(&file);

        in >> this->yearStart;
        in >> this->yearEnd;
    }
    update();
}

/**
 * Restores the previous session's state by reading
 * from the session file.
 */
void MainWindow::restoreState()
{
    CSVReader reader;
    QFile file(this->sessionName());
       if (file.open(QIODevice::ReadOnly))
       {
           QMessageBox::StandardButton resBtn = QMessageBox::question( this, "Restore Session?",
                                                                       tr("Would you like to restore your previous session files?\n"),
                                                                       QMessageBox::No | QMessageBox::Yes,
                                                                       QMessageBox::Yes);

           if (resBtn == QMessageBox::No) {


           }else{
               //read the information into the perseusyGalaxySessionFiles file
               QTextStream in(&file);

               this->previousTeachingFile = in.readLine();
               this->previousGrantsFile = in.readLine();
               this->previousPresentationsFile = in.readLine();
               this->previousPublicationsFile = in.readLine();

               if(!this->previousTeachingFile.isEmpty()){
                   load_teach(this->previousTeachingFile);
                   makeTree(TEACH);

               }

               if(!this->previousPresentationsFile.isEmpty()){
                   load_pres(this->previousPresentationsFile);
                   makeTree(PRESENTATIONS);
               }


               if(!this->previousPublicationsFile.isEmpty()){
                   load_pub(this->previousPublicationsFile);
                   makeTree(PUBLICATIONS);
               }

               if(!this->previousGrantsFile.isEmpty()){
                   load_fund(this->previousGrantsFile);
                   makeTree(FUNDING);
               }
           }
       }
       update();

}

/**
 * Returns a file name that represents the file where the data .csv
 * files used by a user during their session are saved.
 * @return a string representing the filename
 */
QString MainWindow::sessionName() const
{
    return QDir::homePath() + "/.perseusGalaxySessionFiles";
}

/**
 * Returns a file name that represents the file where the date range
 * used by a user during their session is saved.
 * @return a string representing the filename
 */
QString MainWindow::dateFile() const
{
    return QDir::homePath() + "/.perseusGalaxySessionDates";
}

void MainWindow::on_teach_filter_from_textChanged() { refresh(TEACH);}
void MainWindow::on_teach_filter_to_textChanged() { refresh(TEACH);}
void MainWindow::on_pub_filter_from_textChanged() { refresh(PUBLICATIONS);}
void MainWindow::on_pub_filter_to_textChanged() { refresh(PUBLICATIONS);}
void MainWindow::on_pres_filter_from_textChanged() { refresh(PRESENTATIONS);}
void MainWindow::on_pres_filter_to_textChanged() { refresh(PRESENTATIONS);}
void MainWindow::on_fund_filter_from_textChanged() { refresh(FUNDING);}
void MainWindow::on_fund_filter_to_textChanged() { refresh(FUNDING);}


