#ifndef CHARTSTEST_H
#define CHARTSTEST_H
#include <QtTest/QtTest>
#include <iostream>
#include <stdio.h>
#include "gui/mainwindow.h"
#include "gui/piechartwidget.h"
#include "gui/qcustomplot.h"
class ChartsTest: public QObject
{
    Q_OBJECT

private slots:
    void test1();
   // void test2();
   /* void test3();
    void test4();
    void test5();
    void test6();
    void test7();*/
};
#endif
