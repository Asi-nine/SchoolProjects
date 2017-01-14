#include "ui_ErrorEditDialog.h"
#include "ErrorEditDialog.h"

#include <QTableWidgetItem>
#include <QStringList>
#include <QDebug>
#include <QBrush>
#include <QColor>
#include <QAbstractButton>
#include <QMessageBox>
#include <QModelIndex>
#include <QAbstractItemModel>
#include <QLineEdit>
#include <QLCDNumber>

int row;
int col;
int preRow;
int preCol;
std::vector<errorPos> error;
int current;
int changed;
QString s;
bool next;
bool previous;

/*
 * Load data contained in the errors vector into a QWidgetTable
 * Fields will be marked red and editable if they are a mandatory field
 * and editable.  Otherwise all other fields will not be editable.
 * Clicking Save in the dialog will return the corrected entries to the main
 * program through the errors parameter.  If not all marked fields are edited
 * then a warning message will be displayed.  If cancel is clicked all errors
 * are discarded.
 */
ErrorEditDialog::ErrorEditDialog(QWidget *parent,
                                 std::vector<std::vector<std::string>*>& errors,
                                 std::vector<std::string>& headers,
                                 std::vector<std::string>& mandatory) :
    QDialog(parent, Qt::WindowTitleHint | Qt::WindowCloseButtonHint),
    errorList(errors),
    headerList(headers),
    mandatoryList(mandatory),
    ui(new Ui::ErrorEditDialog)
{

    row = 0;
    col = 0;
    preRow = -1;
    preCol = -1;
    error.clear(); // clear the error list every time load file
    current = 0;
    changed = 0;
    s = "";
    next = false;
    previous = false;


    ui->setupUi(this);
    ui->tableWidget->setRowCount((int) errors.size());
    ui->tableWidget->setColumnCount((int) headers.size());

    QStringList listHeaders;
    for (int i = 0; i < (int) headers.size(); i++) {
        listHeaders << headers[i].c_str();
    }

    ui->tableWidget->setHorizontalHeaderLabels(listHeaders);
    QTableWidgetItem* item;
    QBrush brush(QColor(255, 0, 0, 100));
    std::vector<std::vector<std::string>*>::iterator it;
    int row = 0;
    for (it = errors.begin(); it != errors.end(); it++) {
        for (int col = 0; col < (int) headers.size() && col < (int) (*it)->size(); col++) {
            item = new QTableWidgetItem();
            Qt::ItemFlags flag = item->flags();
            item->setFlags(Qt::ItemIsSelectable);
            item->setText((*it)->at(col).c_str());
            for (int i = 0; i < (int) mandatory.size(); i++) {
                if (mandatory[i].compare(headers.at(col)) == 0
                        && (*it)->at(col).compare("") == 0) {
                    item->setBackground(brush);
                    //write all error position by order in a vector called error
                    errorPos position;
                    position.col = col;
                    position.row = row;
                    position.edit = false;
                    error.push_back(position);
                    item->setFlags(flag);
                }
            }
            ui->tableWidget->setItem(row, col, item);
        }
        row++;
    }
    //highlight the current number of errors
    ui->number->setPalette(Qt::red);
    ui->number->display((int)error.size());

    //ui->next->setEnabled(false);//test


}

//Clean up allocated memory for the table items
ErrorEditDialog::~ErrorEditDialog()
{
    for (int i = 0; i < ui->tableWidget->rowCount(); i++) {
        for (int j = 0; j < ui->tableWidget->columnCount(); j++) {
            delete ui->tableWidget->item(i,j);
        }
    }
    delete ui;
}

//Save the new data entered by the user via the error reference var
void ErrorEditDialog::saveData() {
    for (int row = 0; row < ui->tableWidget->rowCount(); row++) {
        for (int col = 0; col < ui->tableWidget->columnCount() && col < (int) errorList[row]->size(); col++) {
            std::vector<std::string>::iterator it = errorList[row]->begin()+col;
            if (errorList[row]->at(col).compare("") == 0) {
                it = errorList[row]->erase(it);
                errorList[row]->insert(it, ui->tableWidget->item(row, col)->text().toStdString());
            }
        }
    }
    //accept();
}

void ErrorEditDialog::on_save_clicked()
{

    bool search = true;
         //check if mandatory fields have been filled
         for (int row = 0; row < ui->tableWidget->rowCount() && search; row++) {
             for (int j = 0; j < (int) mandatoryList.size() && search; j++) {
                 std::vector<std::string>::iterator it = std::find(headerList.begin(), headerList.end(), mandatoryList[j]);
                 int col = it - headerList.begin();
                 QTableWidgetItem* item = ui->tableWidget->item(row, col);
                 if (item->text().compare("") == 0) {
                     QMessageBox::critical(this, "Error", "Mandatory fields are still empty.");
                     search = false;
                 }
             }
         }
         if (search) {
             saveData();
             accept();//test
         }
}

void ErrorEditDialog::on_cancel_clicked()
{
    reject();
}


// if the error is edited, the highlight of the error would be disabled
void ErrorEditDialog::refresh()
{
    QLineEdit* edit = ui->lineEdit;
    s = edit->text();
    QTableWidgetItem* item = ui->tableWidget->item(row,col);

    QBrush brush(QColor(0, 0, 0, 0));

    item->setText(s);

    if (item->text().toStdString().compare("") != 0) {
        item->setBackground(brush);
        //error.erase(error.begin() + current);
        error.erase(error.begin() + changed);
        // set the find buttons disabled when all the errors are edited
        if((int)error.size() == 0){
            ui->next->setEnabled(false);
            ui->previous->setEnabled(false);
            ui->enter->setEnabled(false);

        }
    }

    edit->clear();
    //test to fix the bug
    current = current - 1;

}

// to find the next error
void ErrorEditDialog::on_next_clicked()
{
    QBrush brush(QColor(0, 255, 255, 100));
    QBrush brushErr(QColor(255, 0, 0, 100));
    next = true;
    if(previous == false){
        if(preRow == -1 || preCol == -1){
            current = 0;
        }
        else{
            QTableWidgetItem* item = ui->tableWidget->item(preRow,preCol);
            if(item->backgroundColor() == QColor(0, 255, 255, 100)){
                ui->tableWidget->item(preRow,preCol)->setBackground(brushErr);
            }
        }
        col = error[current].col;
        row = error[current].row;
        QModelIndex table_index = ui->tableWidget->model()->index(row,col);
        ui->tableWidget->scrollTo(table_index);
        ui->tableWidget->item(row,col)->setBackground(brush);
        changed = current;
        current = (current + 1) % error.size();
        preRow = row;
        preCol = col;
    }
    else{
        QTableWidgetItem* item = ui->tableWidget->item(preRow,preCol);
        if(item->backgroundColor() == QColor(0, 255, 255, 100)){
            ui->tableWidget->item(preRow,preCol)->setBackground(brushErr);
        }
        current = current + 1;
        if(current > (int)error.size()){
            current = 0;
        }
        col = error[current].col;
        row = error[current].row;
        QModelIndex table_index = ui->tableWidget->model()->index(row,col);
        ui->tableWidget->scrollTo(table_index);
        ui->tableWidget->item(row,col)->setBackground(brush);
        changed = current;
        current = (current + 1) % error.size();
        preRow = row;
        preCol = col;
        previous = false;
    }

    ui->enter->setEnabled(true);
}


// to find the previous error
void ErrorEditDialog::on_previous_clicked()
{
    QBrush brushHigh(QColor(0, 255, 255, 100));
    QBrush brushErr(QColor(255, 0, 0, 100));
    previous = true;
    if(next == false){
        if(preRow == -1 || preCol == -1){
            current = (int)error.size();
        }
        else{
            QTableWidgetItem* item = ui->tableWidget->item(preRow,preCol);
            if(item->backgroundColor() == QColor(0, 255, 255, 100)){
                ui->tableWidget->item(preRow,preCol)->setBackground(brushErr);
            }
        }

        /*std::stringstream r;
        r << current;
        QString QStr3 = QString::fromStdString(r.str());
        qDebug() << QStr3;*/

        if(current <= 0){
            current = (int)error.size();
        }
        col = error[(current - 1) % error.size()].col;
        row = error[(current - 1) % error.size()].row;

        QModelIndex table_index = ui->tableWidget->model()->index(row,col);
        //ui->tableWidget->setCurrentIndex(table_index);
        ui->tableWidget->scrollTo(table_index);
        ui->tableWidget->item(row,col)->setBackground(brushHigh);
        current = (current - 1) % error.size();
        changed = current;
        preRow = row;
        preCol = col;
        std::stringstream s,t;
        s << col;
        t << row;
        QString QStr1 = QString::fromStdString(s.str());
        QString QStr2 = QString::fromStdString(t.str());
        qDebug() << QStr1;
        qDebug() << QStr2;
    }
    else{
        QTableWidgetItem* item = ui->tableWidget->item(preRow,preCol);
        if(item->backgroundColor() == QColor(0, 255, 255, 100)){
            ui->tableWidget->item(preRow,preCol)->setBackground(brushErr);
        }
        current = current - 1;
        if(current <= 0){
            current = (int)error.size();
        }
        col = error[(current - 1) % error.size()].col;
        row = error[(current - 1) % error.size()].row;
        /*std::stringstream s,t;
        s << col;
        t << row;
        QString QStr1 = QString::fromStdString(s.str());
        QString QStr2 = QString::fromStdString(t.str());
        qDebug() << QStr1;
        qDebug() << QStr2;*/

        QModelIndex table_index = ui->tableWidget->model()->index(row,col);
        //ui->tableWidget->setCurrentIndex(table_index);
        ui->tableWidget->scrollTo(table_index);
        ui->tableWidget->item(row,col)->setBackground(brushHigh);
        current = (current - 1) % error.size();
        changed = current;
        preRow = row;
        preCol = col;
        next = false;
    }
    ui->enter->setEnabled(true);
}

// edit the error
void ErrorEditDialog::on_enter_clicked()
{
    //edit->setEnabled(true);
    ErrorEditDialog::refresh();
    //edit->clear();
    ui->number->display((int)error.size());
    ui->enter->setEnabled(false);
}


