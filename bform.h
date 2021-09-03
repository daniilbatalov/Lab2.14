#ifndef BFORM_H
#define BFORM_H

#include <QWidget>
#include <QFileDialog>
#include <QRegularExpression>
#include "form.h"
#include "task.h"
namespace Ui {
class BForm;
}

class BForm : public Form
{
    Q_OBJECT

public:
    QString catToPush;
    QStringList category;
    explicit BForm(QWidget *parent = nullptr);
    ~BForm();

private slots:
    void on_addButton_clicked();
    void on_txtImportButton_clicked();

    void on_csvImportButton_clicked();

    void on_binImportButton_clicked();

signals:
    void categoriesAddedS(QStringList);
private:
    Ui::BForm *ui;
};

#endif // BFORM_H
