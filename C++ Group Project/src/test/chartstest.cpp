/*************************************************************************
** Tests for charts                                   **
** test1: pie chart is generated                                        **
** test2: pie chart paint event                                       **
*************************************************************************/

#include "chartstest.h"



void ChartsTest::test1()
{
    MainWindow* w = new MainWindow();
    PieChartWidget* piechartwidget = new PieChartWidget(w);
    bool result = false;
    if(piechartwidget){
        result = true;
    }
    QCOMPARE(result,true);
}
/*
void ChartsTest::test2()

{
    MainWindow* w = new MainWindow();
    PieChartWidget* piechartwidget = new PieChartWidget(w);
    
    bool result = false;
    if(piechartwidget){
        result = true;
    }
    //QPaintEvent *event = new QPaintEvent(w*);
    bool result = false;

    //if(event){
      //  result = true;
    //}

    QCOMPARE(result,true);
}*/

/*void ChartsTest::test3()
{
    bool result = false;
    if(barChart){
        result = true;
    }
    QCOMPARE(result,true);
}

/*void ChartsTest::test4()
{

}

/*void ChartsTest::test5()
{
    
}

void ChartsTest::test6()
{
    
}

void ChartsTest::test7()
{

}*/

