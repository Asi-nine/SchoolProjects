/*
 * Written by: Peter Valovcik
 * Date: Oct.22, 2016
 *
 * See the cpp file for more information.
 *
 */

#ifndef DATAMANAGEMENT_H
#define DATAMANAGEMENT_H
#include "user.h"
#include "account.h"
#include "bank.h"
#include "tracer.h"

class DataManagement
{

public:


    DataManagement();

    void writeUser(User* user);

    User* readUser(int id);

    int verifyUser(User *user, int id, int pin);

    void writeBank(Bank* bank);

    Bank* readBank();

    string getDateTime();

    void writeToTrace(int id, string log);

    void deleteTrace(int id);

};

#endif // DATAMANAGEMENT_H
