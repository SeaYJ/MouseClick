#include "cretoolbar.h"
#include "ui_cretoolbar.h"

CreToolBar::CreToolBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CreToolBar)
{
    ui->setupUi(this);

    setWindowTitle(QString("CreToolBar"));
    //setWindowFlags(Qt::FramelessWindowHint);
    setFixedSize(QSize(400, 300));

    this->setAttribute(Qt::WA_QuitOnClose,false);//保证子窗口同主窗口一同关闭
}

CreToolBar::~CreToolBar()
{
    delete ui;
}
