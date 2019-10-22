#include "Task.h"
#include <QDebug>

Task::Task(const WorkerData& data)
{
}

void Task::run()
{
    qDebug() << "\t Task::run() then is sender.send()";
    _sender.send({"Cracovia", "najlepsza", "jest"});
}
