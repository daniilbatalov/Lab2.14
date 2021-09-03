#include "aform.h"
#include "ui_aform.h"


AForm::AForm(QWidget *parent) :
    Form(parent),
    ui(new Ui::AForm)
{
    ui->setupUi(this);
}

AForm::~AForm()
{
    delete ui;
}

void AForm::on_addButton_clicked()
{
    nameToPush = ui->descLineEdit->text();
    placeToPush = ui->placeLineEdit->text();
    task.append(Task(nameToPush, timeToPush, placeToPush));
    ui->descLineEdit->clear();
    ui->placeLineEdit->clear();
    ui->timeEdit->setTime(QTime(0, 0, 0, 0));
    ui->addButton->setText("Done!");
    ui->addButton->setStyleSheet("QPushButton { color : green; }");
    pause();
    ui->addButton->setText("Add");
    ui->addButton->setStyleSheet("QPushButton { color : black; }");
    emit tasksAddedS(task);
    task.clear();
}

void AForm::on_timeEdit_timeChanged(const QTime &time)
{
    timeToPush = time;
}




void AForm::on_txtImportButton_clicked()
{
    QRegularExpression rx("[.!?;:,]");
    QFileDialog dialog = QFileDialog();
    QString fname = dialog.getOpenFileName(this, "Import txt file", "../Lab14/data", "*.txt");
    QFile inputFile(fname);
    QTextStream out(stdout);
    if (inputFile.open(QIODevice::ReadOnly))
    {
       QTextStream in(&inputFile);
       while (!in.atEnd())
       {
          QString data = in.readLine();
          QStringList list = data.split(rx, Qt::SkipEmptyParts);
          nameToPush = list.at(0);
          timeToPush = QTime(list.at(1).toInt(), list.at(2).toInt());
          placeToPush = list.at(3);
          task.push_back(Task(nameToPush, timeToPush, placeToPush));
       }
       inputFile.close();
     }
       emit tasksAddedS(task);
       task.clear();

}

void AForm::on_csvImportButton_clicked()
{
    QRegularExpression rx("[.!?;:,]");
    QFileDialog dialog = QFileDialog();
    QString fname = dialog.getOpenFileName(this, "Import csv file", "../Lab14/data", "*.csv");
    QFile inputFile(fname);
    QTextStream out(stdout);
    if (inputFile.open(QIODevice::ReadOnly))
    {
       QTextStream in(&inputFile);
       while (!in.atEnd())
       {
          QString data = in.readLine();
          QStringList list = data.split(rx, Qt::SkipEmptyParts);
          nameToPush = list.at(0);
          timeToPush = QTime(list.at(1).toInt(), list.at(2).toInt());
          placeToPush = list.at(3);
          task.push_back(Task(nameToPush, timeToPush, placeToPush));
       }
       inputFile.close();
     }
       emit tasksAddedS(task);
       task.clear();
}

void AForm::on_binImportButton_clicked()
{
    QRegularExpression rx("[.!?;:,\n]");
    QFileDialog dialog = QFileDialog();
    QString fname = dialog.getOpenFileName(this, "Import bin file", "../Lab14/data", "*.tasks;;*.dat");
    QFile inputFile(fname);
    QTextStream out(stdout);
    if (inputFile.open(QIODevice::ReadOnly))
    {
       QDataStream in(&inputFile);
       while (!in.atEnd())
       {
          QString data;
          in >> data;
          QStringList list = data.split(rx, Qt::SkipEmptyParts);
          nameToPush = list.at(0);
          timeToPush = QTime(list.at(1).toInt(), list.at(2).toInt());
          placeToPush = list.at(3);
          task.push_back(Task(nameToPush, timeToPush, placeToPush));
       }
       inputFile.close();
    }
    emit tasksAddedS(task);
    task.clear();

}
