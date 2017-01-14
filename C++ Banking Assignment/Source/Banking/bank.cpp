/*
 * Written by: Peter Valovcik
 * Date: Oct.22, 2016
 *
 * A Bank class that just holds some information about the bank system, mainly the tracing information
 * with its Tracer class element, and then the total balance of the bank (balance of all accounts + fees
 * payed when dipping across $1000 in chequing), and an index of total users + 1 used in giving unique
 * IDs to newly created users. Basic accessors and mutators as member functions. It also has a theme :)
 *
 */

#include "bank.h"

Bank::Bank()
{

}


Bank::Bank(double bal, int user, string newTheme, Tracer* tra){
    bankBalance = bal;
    userIndex = user;
    trace = tra;
    theme = newTheme;
}

Tracer* Bank::getTracer(){
    return trace;
}

void Bank::setTracer(Tracer* tra){
    trace = tra;
}

void Bank::setBalance(double bal){
    bankBalance = bal;
}

double Bank::getBalance(){
    return bankBalance;
}

void Bank::setUser(int user){
    userIndex = user;
}

int Bank::getUser(){

    return userIndex;
}

void Bank::setTheme(string newTheme){
    theme = newTheme;
}

string Bank::getTheme(){
    return theme;
}
