#ifndef TASK_H
#define TASK_H

#include <QDateTime>

class Task
{
private:
    QString task_name;
    QTime task_time;
    QString task_place;
public:
    void set_name(const QString);
    void set_time(QTime);
    void set_place(const QString);
    QString get_name() const;
    QTime get_time() const;
    QString get_place() const;
    QString toString() const;
    friend bool operator== (const Task &t1, const Task &t2)
    {
        return ((t1.task_name == t2.task_name) && (t1.task_time == t2.task_time) && (t1.task_place == t2.task_place));
    }
    friend bool operator!= (const Task &t1, const Task &t2)
    {
        return (!(t1== t2));
    }
    Task();
    Task(const QString, QTime, const QString);
    Task(const Task&);
};

#endif // TASK_H
