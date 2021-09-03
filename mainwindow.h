#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include "aform.h"
#include "bform.h"
#include "task.h"
#include "link.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QList<Task> tasks;
    QStringList categories;
    QList<Link> links;
    void redraw_task(QTableWidget*);
    void redraw_cat(QTableWidget*);
    void redraw_link(QTableWidget*);
    template<typename T>
    void deleteFromTable(QTableWidget*, QList<T>, int);
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void on_Tasks_Added(QList<Task>);
    void on_Cats_Added(QStringList);
private slots:
    void on_addAButton_clicked();

    void on_deleteAButton_clicked();

    void on_addBButton_clicked();

    void on_deleteBButton_clicked();

    void on_addLinkButton_clicked();

    void on_deleteLinkButton_clicked();

    void on_showAssocAButton_clicked();

    void on_showAssocBButton_clicked();

    void on_importLinksButton_clicked();

    void on_exportButton_clicked();

private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
