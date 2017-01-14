/*
 * Written by: Peter Valovcik
 * Date: Oct.22, 2016
 *
 * Tracer class is a class that allows toggling of a boolean to determine whether or not
 * to follow the actions of a user with any chosen ID. Member functions are accessors and mutators.
 *
 */


#include "tracer.h"

Tracer::Tracer()
{

}

Tracer::Tracer(bool tra, int id){
    trace = tra;
    ID = id;
}

void Tracer::setTrace(bool tra){
    trace = tra;
}

bool Tracer::getTrace(){
    return trace;
}

void Tracer::setID(int id){
    ID = id;
}

int Tracer::getID(){
    return ID;
}
