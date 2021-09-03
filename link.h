#ifndef LINK_H
#define LINK_H

#include "task.h"

class Link
{
private:
    Task tsk;
    QStringList cats = QStringList();
public:
    void set_task(Task);
    void set_cats(QStringList);
    Task get_task() const;
    QStringList get_cats();
    QString getCatAsString(bool);
    void remove_cat(int);
    friend bool operator== (const Link &l1, const Link &l2)
    {
        return ((l1.tsk == l2.tsk) && (l1.cats == l2.cats));
    }
    friend bool operator!= (const Link &l1, const Link &l2)
    {
        return (!(l1== l2));
    }
    Link(Task, QStringList);


};

#endif // LINK_H
