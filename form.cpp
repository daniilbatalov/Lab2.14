#include "form.h"
#include "ui_form.h"

Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
}
void Form::pause()
{
    QEventLoop el;
    QTimer t;
    connect(&t, SIGNAL(timeout()), &el, SLOT(quit()));
    t.start(2500);
    el.exec();
    return;
}
Form::~Form()
{
    delete ui;
}
