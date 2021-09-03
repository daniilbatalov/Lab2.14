#include "task.h"

void Task::set_name(const QString name)
{
    task_name = name;
};
void Task::set_time(QTime time)
{
    task_time = time;
};
void Task::set_place(const QString place)
{
    task_place = place;
};
QString Task::get_name() const
{
    return task_name;
};
QTime Task::get_time() const
{
    return task_time;
};
QString Task::get_place() const
{
    return task_place;
};
QString Task::toString() const
{
    return (task_name + "; " + task_time.toString("hh:mm") + "; " + task_place);
}
Task::Task()
{
    set_name("");
    set_time(QTime(0, 0, 0, 0));
    set_place("");
}
Task::Task(const QString name, QTime time, const QString place)
{
    set_name(name);
    set_time(time);
    set_place(place);
}
Task::Task(const Task& t1)
{
    set_name(t1.get_name());
    set_time(t1.get_time());
    set_place(t1.get_place());
}
