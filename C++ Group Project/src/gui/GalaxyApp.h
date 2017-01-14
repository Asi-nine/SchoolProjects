#ifndef GALAXYAPP_H
#define GALAXYAPP_H

#include <QObject>
#include <QApplication>
#include <QSessionManager>
#include "mainwindow.h"

/**
 * A class to allow for the saving of session state.
 * It reimplements the commitData and saveState functions
 * from QApplication. It is adapted from:
 * http://www.informit.com/articles/article.aspx?p=1405560&seqNum=3
 */
class GalaxyApp: public QApplication
{
public:
    GalaxyApp(int &argc, char *argv[]);

    void setMainWindow(MainWindow *mainWindow);
    void saveState(QSessionManager &manager);
    void commitData(QSessionManager &manager);

private:

    MainWindow *mainWindow;
};

#endif // GALAXYAPP_H
