/*
 * Written by: Peter Valovcik
 * Date: Oct.22, 2016
 *
 * See the cpp file for more information.
 *
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <iostream>
#include <fstream>
#include <time.h>
#include "account.h"
#include "user.h"
#include "stdlib.h"
#include "datamanagement.h"
#include "bank.h"
#include "tracer.h"

class MainWindow
{
public:
    MainWindow();


    void startLoop();
};

#endif // MAINWINDOW_H
