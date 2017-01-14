/*
 * Written by: Peter Valovcik
 * Date: Oct.22, 2016
 *
 * See the cpp file for more information.
 *
 */
#ifndef ACCOUNT_H
#define ACCOUNT_H
#include <iostream>
using namespace std;

class Account
{
private:
    string accountType;
    double accountBalance;

public:
    Account();

    Account(string type, double bal);

    void CloseAccount();

    void setAccountType(string type);

    string getAccountType();

    void deposit(double money);

    int withdraw(double money);

    double getBalance();

    int transfer(double money, Account* destination);


};

#endif // ACCOUNT_H
