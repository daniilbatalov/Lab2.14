#include "link.h"
#include <iostream>
void Link::set_task(Task t)
{
    tsk = t;
}
void Link::set_cats(QStringList c)
{
    for(QString s : c)
    {
        this->cats.append(s);
    }
}
Task Link::get_task() const
{
    return tsk;
}
QStringList Link::get_cats()
{
    return cats;
}
QString Link::getCatAsString(bool mode)
{
    QString res = "";
    for (QString s : this->cats)
    {
        if (mode)
        {
            res.append(s + "; ");
        }
        else
        {
            res.append(s + ";");
        }
    }
    if (mode)
    {
        res.chop(2);
    }
    else
    {
        res.chop(1);
    }
    return res;
}
void Link::remove_cat(int toRemove)
{
    cats.remove(toRemove);
    cats.squeeze();

}
Link::Link(Task t, QStringList c)
{
    set_task(t);
    set_cats(c);
}
