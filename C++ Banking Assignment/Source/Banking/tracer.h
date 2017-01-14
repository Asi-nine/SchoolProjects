/*
 * Written by: Peter Valovcik
 * Date: Oct.22, 2016
 *
 * See the cpp file for more information.
 *
 */

#ifndef TRACER_H
#define TRACER_H


class Tracer
{
private:
    bool trace;
    int ID;
public:
    Tracer();

    Tracer(bool tra, int id);

    void setTrace(bool tra);

    bool getTrace();

    void setID(int id);

    int getID();
};

#endif // TRACER_H
