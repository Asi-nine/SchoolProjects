#ifndef USERLIST_H
#define USERLIST_H

#include <QModelIndex>

class UserList
{
public:
    UserList();


    void addModelIndex(QModelIndex index);
    void removeModelIndex();
    void clearModelIndex();
    bool isEmpty();
    int getLength();
    QModelIndex getModelIndex(int position);


private:
    std::vector<QModelIndex> customList;
    int length;
};


#endif // USERLIST_H
