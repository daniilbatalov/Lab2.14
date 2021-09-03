#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::redraw_task(QTableWidget* table)
{
    table->setRowCount(0);
    for(Task a : tasks)
    {
        table->setRowCount(table->rowCount() + 1);
        table->setItem(table->rowCount() - 1, 0, new QTableWidgetItem(a.get_name()));
        table->setItem(table->rowCount() - 1, 1, new QTableWidgetItem(a.get_time().toString("hh:mm")));
        table->setItem(table->rowCount() - 1, 2, new QTableWidgetItem(a.get_place()));

    }
}
void MainWindow::redraw_cat(QTableWidget* table)
{
    table->setRowCount(0);
    for(QString a : categories)
    {
        table->setRowCount(table->rowCount() + 1);
        table->setItem(table->rowCount() - 1, 0, new QTableWidgetItem(a));
    }
}
void MainWindow::redraw_link(QTableWidget* table)
{

    QVector<int> toClean;
    for(int i = links.length() - 1; i >=0 ; i--)
    {
        if(links[i].get_cats().isEmpty())
        {
            toClean.append(i);
        }
    }
    for(int td : toClean)
    {
        links.remove(td);
        links.squeeze();
    }
    table->setRowCount(0);
    for(Link a : links)
    {
        table->setRowCount(table->rowCount() + 1);
        table->setItem(table->rowCount() - 1, 0, new QTableWidgetItem(a.get_task().toString()));
        table->setItem(table->rowCount() - 1, 1, new QTableWidgetItem(a.getCatAsString(true)));
    }
}
void MainWindow::on_Tasks_Added(QList<Task> tsk)
{
    tasks.append(tsk);
    redraw_task(ui->aTable);
}
void MainWindow::on_Cats_Added(QStringList ctgr)
{
    categories.append(ctgr);
    redraw_cat(ui->bTable);
}
void MainWindow::on_addAButton_clicked()
{
    AForm* a = new AForm();
    a->show();
    QObject::connect(a, &AForm::tasksAddedS, this, &MainWindow::on_Tasks_Added);

}
template<typename T>
void MainWindow::deleteFromTable(QTableWidget* table, QList<T> list, int mode)
{
    QSet<int> rowsToDeleteSet;
    QVector<int> rowsToDelete;
    for (auto item : table->selectedItems())
    {
        rowsToDeleteSet.insert(item->row());
    }
    for (int i : rowsToDeleteSet)
    {
        rowsToDelete.append(i);
    }
    std::sort(rowsToDelete.begin(), rowsToDelete.end(), std::greater<int>());
    for (int rtd : rowsToDelete)
    {
        list.remove(rtd);
        list.squeeze();
    }
    switch (mode)
    {
    case 0:
    {
        redraw_task(table);
    }
    case 1:
    {
        redraw_link(table);
    }
    case 2:
    {
        redraw_cat(table);
    }
    }
    table->setRowCount(list.length());
}

void MainWindow::on_deleteAButton_clicked()
{
    QSet<int> rowsToDeleteSet;
    QVector<int> rowsToDelete;
    for (auto item : ui->aTable->selectedItems())
    {
        rowsToDeleteSet.insert(item->row());
    }
    for (int i : rowsToDeleteSet)
    {
        rowsToDelete.append(i);
    }
    rowsToDeleteSet.clear();
    std::sort(rowsToDelete.begin(), rowsToDelete.end(), std::greater<int>());
    for (int rtd : rowsToDelete)
    {
        for(int i = 0; i < links.length(); i++)
        {
            if (links.at(i).get_task() == tasks[rtd])
            {
                rowsToDeleteSet.insert(i);
            }
        }
        tasks.remove(rtd);
        tasks.squeeze();
    }
    rowsToDelete.clear();
    for (int i : rowsToDeleteSet)
    {
        rowsToDelete.append(i);
    }
    std::sort(rowsToDelete.begin(), rowsToDelete.end(), std::greater<int>());
    for (int rtd : rowsToDelete)
    {
        links.remove(rtd);
        links.squeeze();
    }
    redraw_task(ui->aTable);
    redraw_link(ui->linkTable);
    ui->aTable->setRowCount(tasks.length());
    ui->linkTable->setRowCount(links.length());

}

void MainWindow::on_addBButton_clicked()
{
    BForm* b = new BForm();
    b->show();
    QObject::connect(b, &BForm::categoriesAddedS, this, &MainWindow::on_Cats_Added);
}

void MainWindow::on_deleteBButton_clicked()
{
    QSet<int> rowsToDeleteSet;
    QVector<int> rowsToDelete;
    QVector<int> rowsToDelete_c;
    for (auto item : ui->bTable->selectedItems())
    {
        rowsToDeleteSet.insert(item->row());
    }
    for (int i : rowsToDeleteSet)
    {
        rowsToDelete.append(i);
    }
    rowsToDeleteSet.clear();
    std::sort(rowsToDelete.begin(), rowsToDelete.end(), std::greater<int>());
    for (int rtd : rowsToDelete)
    {
        for(int j = 0; j < links.length(); j++)
        {
            for(int i = 0; i < links[j].get_cats().length(); i++)
            {
                if (links[j].get_cats().at(i) == categories[rtd])
                {
                    rowsToDeleteSet.insert(i);
                }
            }
            for (int i : rowsToDeleteSet)
            {
                rowsToDelete_c.append(i);
            }
            rowsToDeleteSet.clear();
            std::sort(rowsToDelete_c.begin(), rowsToDelete_c.end(), std::greater<int>());
            for(int rtdc : rowsToDelete_c)
            {
                links[j].remove_cat(rtdc);
            }
            rowsToDelete_c.clear();

        }
        categories.remove(rtd);
        categories.squeeze();
    }
    redraw_cat(ui->bTable);
    redraw_link(ui->linkTable);
    ui->bTable->setRowCount(categories.length());
}

void MainWindow::on_addLinkButton_clicked()
{

    QSet<int> taskRowsToAddSet;
    QSet<int> catsRowsToAddSet;
    QStringList resCategory;
    for (auto item : ui->aTable->selectedItems())
    {
        taskRowsToAddSet.insert(item->row());
    }
    for (auto item : ui->bTable->selectedItems())
    {
        catsRowsToAddSet.insert(item->row());
    }
    for(int i : catsRowsToAddSet)
    {
        resCategory.append(categories.at(i));
    }
    for(int i : taskRowsToAddSet)
    {
        bool flag = false;
        if(links.isEmpty())
        {
            links.append(Link(tasks.at(i), resCategory));
        }
        else
        {
            for(int j = 0; j < links.length(); j++)
            {
                if (links[j].get_task() == tasks.at(i))
                {
                    links[j].set_cats(resCategory);
                    flag = true;
                    break;
                }

            }
            if(!flag)
            {
                links.append(Link(tasks.at(i), resCategory));
            }
        }
    }
    redraw_link(ui->linkTable);

}

void MainWindow::on_deleteLinkButton_clicked()
{
    QSet<int> rowsToDeleteSet;
    QVector<int> rowsToDelete;
    for (auto item : ui->linkTable->selectedItems())
    {
        rowsToDeleteSet.insert(item->row());
    }
    for (int i : rowsToDeleteSet)
    {
        rowsToDelete.append(i);
    }
    std::sort(rowsToDelete.begin(), rowsToDelete.end(), std::greater<int>());
    for (int rtd : rowsToDelete)
    {
        links.remove(rtd);
        links.squeeze();
    }
    redraw_link(ui->linkTable);
    ui->linkTable->setRowCount(links.length());
}


void MainWindow::on_showAssocAButton_clicked()
{

    QSet<int> rowsPickedSet;
    QSet<int> linksSet;
    QSet<int> catsSet;
    QSet<int> rowsToShowSet;
    for (auto item : ui->aTable->selectedItems())
    {
        rowsPickedSet.insert(item->row());
    }
    ui->bTable->clearSelection();
    ui->bTable->setSelectionMode(QAbstractItemView::MultiSelection);
    for(int r : rowsPickedSet)
    {
        for(int i = 0; i < links.length(); i++)
        {
            if(links[i].get_task() == tasks[r])
                linksSet.insert(i);
        }
    }
    for(int l: linksSet)
    {
        for (int j = 0; j < categories.length(); j++ )
        {
            if(links[l].get_cats().contains(categories[j]))
                catsSet.insert(j);
        }
    }
    for(int c : catsSet)
    {
        ui->bTable->selectRow(c);
    }
    ui->bTable->setSelectionMode(QAbstractItemView::ExtendedSelection);
}

void MainWindow::on_showAssocBButton_clicked()
{
    QSet<int> rowsPickedSet;
    QSet<int> linksSet;
    QSet<int> tasksSet;
    QSet<int> rowsToShowSet;
    for (auto item : ui->bTable->selectedItems())
    {
        rowsPickedSet.insert(item->row());
    }
    ui->aTable->clearSelection();
    ui->aTable->setSelectionMode(QAbstractItemView::MultiSelection);
    for(int r : rowsPickedSet)
    {
        for (int j = 0; j < links.length(); j++ )
        {
            if(links[j].get_cats().contains(categories[r]))
                linksSet.insert(j);
        }
    }
    for(int l: linksSet)
    {
        for(int i = 0; i < tasks.length(); i++)
        {
            if(links[l].get_task() == tasks[i])
                tasksSet.insert(i);
        }
    }
    for(int t : tasksSet)
    {
        ui->aTable->selectRow(t);
    }
    ui->aTable->setSelectionMode(QAbstractItemView::ExtendedSelection);
}

void MainWindow::on_importLinksButton_clicked()
{

    QTime timeToPush = QTime(0, 0, 0, 0);
    QString nameToPush;
    QString placeToPush;
    QString catToPush;
    QRegularExpression rx("[.!?;:,\n]");
    QRegularExpression rx_2("[\n]");
    QFileDialog dialog = QFileDialog();
    QString fname = dialog.getOpenFileName(this, "Import bin file", "../Lab14/data", "*.data;;*.dat");
    QFile inputFile(fname);
    QTextStream out(stdout);
    if (inputFile.open(QIODevice::ReadOnly))
    {
       QDataStream in(&inputFile);
       QString ie;
       in >> ie;
       for(int i = 0; i < ie.toInt(); i++)
       {
           QString data;
           in >> data;
           QStringList list = data.split(rx, Qt::SkipEmptyParts);
           nameToPush = list.at(0);
           timeToPush = QTime(list.at(1).toInt(), list.at(2).toInt());
           placeToPush = list.at(3);
           tasks.push_back(Task(nameToPush, timeToPush, placeToPush));
       }
       QString io;
       in >> io;
       for(int i = 0; i < io.toInt(); i++)
       {
           QString data;
           in >> data;
           QStringList list = data.split(rx_2, Qt::SkipEmptyParts);
           categories.push_back(list.at(0));
       }
       QString iq;
       in >> iq;
       for(int i = 0; i < iq.toInt(); i++)
       {
           QString data;
           in >> data;
           QStringList list = data.split(rx, Qt::SkipEmptyParts);
           links.append(Link(tasks.at(list.at(0).toInt()), list.mid(1)));
       }

    inputFile.close();
    }
    redraw_task(ui->aTable);
    redraw_cat(ui->bTable);
    redraw_link(ui->linkTable);
}

void MainWindow::on_exportButton_clicked()
{
    QFileDialog dialog = QFileDialog();
    QString fname = dialog.getSaveFileName(this, "Save dat file", "../Lab14/data", "*.data");
    QFile outputFile(fname);
    if (outputFile.open(QIODevice::WriteOnly))
    {
       QDataStream out(&outputFile);
       out << QString::number(tasks.length()) + "\n";
       for (Task s : tasks)
       {
           QString str = s.get_name() + ";" + s.get_time().toString("hh;mm")  + ";" + s.get_place() + "\n";
           out << str;
       }
       out << QString::number(categories.length()) + "\n";
       for(QString s : categories)
       {
          out << s;
       }
       out << QString::number(links.length()) + "\n";
       for(Link l : links)
       {
           int i = tasks.indexOf(l.get_task());
           out << QString::number(i) + ";" + l.getCatAsString(false) + "\n";
       }
       outputFile.close();
    }
}
