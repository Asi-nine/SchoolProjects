/*
 * UserList Class will store a custom user list in order to make a subset of the
 * given data.
 *
 */

#include "userlist.h"

UserList::UserList()
{
    customList;
    length = 0;
}



void UserList::addModelIndex(QModelIndex index){
    if(!customList.empty()){
        bool exists = false;
        for(QModelIndex n : customList){
            if(n == index)
                exists = true;
        }
        if(!exists){
            customList.push_back(index);
            length = length + 1;
        }
    }
    else{ customList.push_back(index); length = length + 1;}

}

void UserList::removeModelIndex(){
    if(!customList.empty()){
        customList.pop_back();
        length = length -1;
    }
}

void UserList::clearModelIndex(){
    customList.clear();
    length = 0;
}

bool UserList::isEmpty(){
    if(customList.empty()){
        return true;
    }
    return false;
}

int UserList::getLength(){
    return length;
}

QModelIndex UserList::getModelIndex(int position){
    return customList[position];
}

