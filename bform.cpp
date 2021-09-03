#include "bform.h"
#include "ui_bform.h"

BForm::BForm(QWidget *parent) :
    Form(parent),
    ui(new Ui::BForm)
{
    ui->setupUi(this);
}

BForm::~BForm()
{
    delete ui;
}

void BForm::on_addButton_clicked()
{
    catToPush = ui->catLineEdit->text();
    category.append(catToPush);
    ui->catLineEdit->clear();
    ui->addButton->setText("Done!");
    ui->addButton->setStyleSheet("QPushButton { color : green; }");
    pause();
    ui->addButton->setText("Add");
    ui->addButton->setStyleSheet("QPushButton { color : black; }");
    emit categoriesAddedS(category);
    category.clear();
}

void BForm::on_txtImportButton_clicked()
{
    QFileDialog dialog = QFileDialog();
    QString fname = dialog.getOpenFileName(this, "Import txt file", "../Lab14/data", "*.txt");
    QFile inputFile(fname);
    QTextStream out(stdout);
    if (inputFile.open(QIODevice::ReadOnly))
    {
       QTextStream in(&inputFile);
       while (!in.atEnd())
       {
          catToPush = in.readLine();
          category.push_back(catToPush);
       }
       inputFile.close();
     }
       emit categoriesAddedS(category);
       category.clear();
}

void BForm::on_csvImportButton_clicked()
{
    QFileDialog dialog = QFileDialog();
    QString fname = dialog.getOpenFileName(this, "Import csv file", "../Lab14/data", "*.csv");
    QFile inputFile(fname);
    QTextStream out(stdout);
    if (inputFile.open(QIODevice::ReadOnly))
    {
       QTextStream in(&inputFile);
       while (!in.atEnd())
       {
          catToPush = in.readLine();
          category.push_back(catToPush);
       }
       inputFile.close();
     }
       emit categoriesAddedS(category);
       category.clear();
}

void BForm::on_binImportButton_clicked()
{
    QFileDialog dialog = QFileDialog();
    QString fname = dialog.getOpenFileName(this, "Import bin file", "../Lab14/data", "*.categories;;*.dat");
    QFile inputFile(fname);
    QTextStream out(stdout);
    if (inputFile.open(QIODevice::ReadOnly))
    {
       QDataStream in(&inputFile);
       while (!in.atEnd())
       {
          in >> catToPush;
          category.push_back(catToPush);
       }
       inputFile.close();
    }
    emit categoriesAddedS(category);
    category.clear();
}
