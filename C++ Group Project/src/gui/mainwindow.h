#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <string>
#include <QMainWindow>
#include <vector>
#include "qcustomplot.h"
#include <QCloseEvent>
#include <stdio.h>
#include "userlist.h"


class RecordsManager;
class CSVReader;
class TreeModel;
class CustomSort;
class PieChartWidget;
class QListWidget;
class QTreeView;
class QCustomPlot;
class QPrinter;
class QPainter;

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QString saveState();
    QString saveDate();

    //getters for date information
    int getYearStart(){ return yearStart; }
    int getYearEnd(){ return yearEnd; }

private slots:
    QString load_file();

    //removed for bubble chart
    //void axisLabelDoubleClick(QCPAxis *axis, QCPAxis::SelectablePart part);
    //void legendDoubleClick(QCPLegend *legend, QCPAbstractLegendItem *item);
    // functions for chart interactions
    void selectionChanged();
    void mousePress();
    void mouseWheel();

    void on_pres_load_file_clicked();
    void on_pub_load_file_clicked();
    void on_fund_load_file_clicked();
    void on_teach_load_file_clicked();


    void on_teach_new_sort_clicked();
    void on_pub_new_sort_clicked();
    void on_pres_new_sort_clicked();
    void on_fund_new_sort_clicked();

    void on_actionLoad_file_triggered();

    void on_FromDate_dateChanged(const QDate &date);
    void on_ToDate_dateChanged(const QDate &date);

    void refresh(int tabIndex);

    void on_teach_sort_currentIndexChanged(int index);
    void on_pub_sort_currentIndexChanged(int index);
    void on_pres_sort_currentIndexChanged(int index);
    void on_fund_sort_currentIndexChanged(int index);

    void on_teach_delete_sort_clicked();
    void on_pub_delete_sort_clicked();
    void on_pres_delete_sort_clicked();
    void on_fund_delete_sort_clicked();

    // functions for chart button
    void on_teach_pie_button_toggled();
    void on_teach_bar_button_toggled();
    void on_teach_line_button_toggled();
    void on_teach_bubble_button_toggled();
    void on_pub_pie_button_toggled();
    void on_pub_bar_button_toggled();
    void on_pub_line_button_toggled();
    void on_pub_bubble_button_toggled();
    void on_pres_pie_button_toggled();
    void on_pres_bar_button_toggled();
    void on_pres_line_button_toggled();
    void on_pres_bubble_button_toggled();
    void on_fund_pie_button_toggled();
    void on_fund_bar_button_toggled();
    void on_fund_line_button_toggled();
    void on_fund_bubble_button_toggled();

    void on_teachTreeView_clicked(const QModelIndex &index);
    void on_pubTreeView_clicked(const QModelIndex &index);
    void on_presTreeView_clicked(const QModelIndex &index);
    void on_fundTreeView_clicked(const QModelIndex &index);

    void on_categoryTab_currentChanged();

    void on_teach_filter_from_textChanged();
    void on_teach_filter_to_textChanged();
    void on_pub_filter_from_textChanged();
    void on_pub_filter_to_textChanged();
    void on_pres_filter_from_textChanged();
    void on_pres_filter_to_textChanged();
    void on_fund_filter_from_textChanged();
    void on_fund_filter_to_textChanged();

    void on_customListAddTeach_clicked();

    void on_customListRemoveTeach_clicked();

    void on_customListClearTeach_clicked();

    void on_customListShowTeach_clicked();

    void on_defaultListShowTeach_clicked();

    void on_customListGraphTeach_clicked();

    void on_customListAddFund_clicked();

    void on_customListRemoveFund_clicked();

    void on_customListClearFund_clicked();

    void on_customListShowFund_clicked();

    void on_defaultListShowFund_clicked();

    void on_customListGraphFund_clicked();

    void on_customListAddPub_clicked();

    void on_customListRemovePub_clicked();

    void on_customListClearPub_clicked();

    void on_customListShowPub_clicked();

    void on_defaultListShowPub_clicked();

    void on_customListGraphPub_clicked();

    void on_customListAddPres_clicked();

    void on_customListRemovePres_clicked();

    void on_customListClearPres_clicked();

    void on_customListShowPres_clicked();

    void on_defaultListShowPres_clicked();

    void on_customListGraphPres_clicked();

    void on_teachPrintButton_clicked();

    void on_fundPrintButton_clicked();

    void on_presPrintButton_clicked();

    void on_pubPrintButton_clicked();

    void on_teachExportButton_clicked();

    void on_fundExportButton_clicked();

    void on_presExportButton_clicked();

    void on_pubExportButton_clicked();

protected:

    //this method is protected so we can override it, if necessary
    void closeEvent (QCloseEvent *event);

private:

    QSettings *appSettings;
    QCPAxis *axis;
    QCPAxis::SelectablePart part;
    QCPLegend *legend;
    QCPAbstractLegendItem *item;
    QPoint pos;
    QCPAbstractPlottable *plottable;
    int dataIndex;

    static std::vector<std::string> GRANTS_MANFIELDS, PRES_MANFIELDS, PUBS_MANFIELDS, TEACH_MANFIELDS;

    enum TABS {
        TEACH, PUBLICATIONS, PRESENTATIONS, FUNDING
    };

    struct field_error;

    Ui::MainWindow* ui;
    QPrinter* printer;



    QList<QStringList> allTeachOrders, allPubOrders, allPresOrders, allFundOrders;
    QString teachPath, pubPath, presPath, fundPath;
    TreeModel *fundTree, *presTree, *pubTree, *teachTree;
    RecordsManager *funddb, *presdb, *pubdb, *teachdb;
    std::vector<std::vector<std::string>> fundData, presData, pubData, teachData;

    std::vector<std::string> teachSortOrder, pubSortOrder, presSortOrder, fundSortOrder;
    TreeModel* currentTree;
    RecordsManager* currentdb;
    QTreeView* currentView;
    QString teachClickedName, pubClickedName, presClickedName, fundClickedName;

    QModelIndex teachModelIndex, fundModelIndex, pubModelIndex, presModelIndex;
    UserList customListTeach, customListFund, customListPub, customListPres;

    QList<bool> dateChanged;

    std::vector<std::string> getParentsList(QModelIndex &index);
    char getFilterStartChar(int type);
    char getFilterEndChar(int type);


    int yearStart = 0;
    int yearEnd = 0;

    int checkFile(int index, QString filePath);
    //std::vector<std::string> getSelectedSortOrder(int tabIndex);
    void createDefaultSortOrder(int tabIndex);
    void makeTree(int tabIndex);

    // chart set up
    void setupPieChart(PieChartWidget *pieChart, QListWidget *pieListWidget, std::vector<std::pair<std::string, double> > pieChartList);
    void setupBarChart(QCustomPlot *barChart, std::vector<std::pair<std::string, double> > barChartList);
    void setupLineChart(QCustomPlot *lineChart, std::vector<std::pair<std::string, double> > lineChartList);
    void setupBubbleChart(QCustomPlot *bubbleChart, std::vector<std::pair<std::string, double> > bubbleChartList);



    bool handle_field_errors(std::vector<std::vector<std::string>*>& errors,
                             std::vector<std::string>& headers,
                             std::vector<std::string>& mandatory);
    bool load_fund(QString path, bool multi_file = false);
    bool load_pub(QString path, bool multi_file = false);
    bool load_teach(QString path, bool multi_file = false);
    bool load_pres(QString path, bool multi_file = false);


    //session management
    QSessionManager* manager;
    QString sessionName() const;
    QString dateFile() const;
    void restoreState();
    void restoreDate();
    QString previousTeachingFile = "";
    QString previousPublicationsFile = "";
    QString previousGrantsFile = "";
    QString previousPresentationsFile = "";


};

#endif // MAINWINDOW_H
