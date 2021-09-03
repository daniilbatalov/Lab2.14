#ifndef AFORM_H
#define AFORM_H

#include <QWidget>
#include <QFileDialog>
#include "form.h"
#include "task.h"
namespace Ui {
class AForm;
}

class AForm : public Form
{
    Q_OBJECT

public:
    QList<Task> task;
    QTime timeToPush = QTime(0, 0, 0, 0);
    QString nameToPush;
    QString placeToPush;
    explicit AForm(QWidget *parent = nullptr);
    ~AForm();

private slots:
    void on_addButton_clicked();

    void on_timeEdit_timeChanged(const QTime &time);

    void on_txtImportButton_clicked();

    void on_csvImportButton_clicked();

    void on_binImportButton_clicked();

signals:
    void tasksAddedS(QList<Task>);
private:
    Ui::AForm *ui;
};

#endif // AFORM_H
