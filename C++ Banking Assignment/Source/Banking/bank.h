/*
 * Written by: Peter Valovcik
 * Date: Oct.22, 2016
 *
 * See the cpp file for more information.
 *
 */

#ifndef BANK_H
#define BANK_H
#include "tracer.h"
#include "account.h"

class Bank
{
private:
    double bankBalance;
    int userIndex;
    string theme;
    Tracer* trace;
public:
    Bank();

    Bank(double bal, int user, string newTheme, Tracer* tra);

    Tracer* getTracer();

    void setTracer(Tracer *tra);

    void setBalance(double bal);

    double getBalance();

    void setUser(int user);

    int getUser();

    void setTheme(string theme);

    string getTheme();

};

#endif // BANK_H
