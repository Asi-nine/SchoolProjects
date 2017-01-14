/*
 * Written by: Peter Valovcik
 * Date: Oct.22, 2016
 *
 * Main to start the bank.
 *
 */
#include "mainwindow.h"


using namespace std;



int main(int argc, char *argv[])
{


    //start menu loop
    MainWindow* mainWindow = new MainWindow;
    mainWindow->startLoop();

    return 0;
}

