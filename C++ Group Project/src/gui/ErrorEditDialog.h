#ifndef ERROREDITDIALOG_H
#define ERROREDITDIALOG_H

#include <QDialog>
#include <vector>
#include <string>
#include <iostream>
#include <QtDebug>
#include <sstream>

class QAbstractButton;

namespace Ui {
    class ErrorEditDialog;
}

class ErrorEditDialog : public QDialog
{
    Q_OBJECT

public:
     ErrorEditDialog(QWidget *parent,
                     std::vector<std::vector<std::string>*>& errors,
                     std::vector<std::string>& headers,
                     std::vector<std::string>& mandatory);
    ~ErrorEditDialog();

private slots:
     void on_save_clicked();
     void on_cancel_clicked();
     void on_next_clicked();
     void on_previous_clicked();
     void on_enter_clicked();

private:
    std::vector<std::vector<std::string>*> errorList;
    std::vector<std::string> headerList;
    std::vector<std::string> mandatoryList;
    Ui::ErrorEditDialog *ui;


    void saveData();

    void refresh();

};

struct errorPos{
    int row;
    int col;
    bool edit;
};

#endif // ERROREDITDIALOG_H
