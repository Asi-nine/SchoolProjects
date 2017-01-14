#include <QSessionManager>
#include <QMessageBox>
#include <QString>
#include <QStringList>
#include "GalaxyApp.h"

/**
 * Default constructor.
 */
GalaxyApp::GalaxyApp(int &argc, char *argv[]): QApplication(argc, argv)
{

}

/**
 * Makes GalaxyApp aware of the MainWindow widget.
 * @param mainWindow a pointer to the gui
 */
void GalaxyApp::setMainWindow(MainWindow *mainWindow)
{
    this->mainWindow = mainWindow;
}

/**
 * Called when the session manager wants to save
 * the session.
 * @param manager a QSessionManager object
 */
void GalaxyApp::saveState(QSessionManager &manager)
{
    //contains the session information
    QString fileName = mainWindow->saveState();

    //ensures that currently stored session information
    //is deleted
    QStringList discardCommand;
    discardCommand << "rm" << fileName;
    manager.setDiscardCommand(discardCommand);
}

/**
 * Called when the user logs out. Ensures that all session data
 * is correctly stored.
 * @param manager
 */
void GalaxyApp::commitData(QSessionManager &manager)
{
    if (manager.allowsInteraction()) {
            int r = QMessageBox::warning(mainWindow, tr("Peachy Galaxy"),
                            tr("Do you really want to quit?\n"),
                            QMessageBox::Yes | QMessageBox::No);
            if (r == QMessageBox::Yes) {
                manager.release();
            } else {
                manager.cancel();
            }
        }
}
