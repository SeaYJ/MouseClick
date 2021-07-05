#include "aboutinfo.h"
#include "ui_aboutinfo.h"

#define InfoWidth 421
#define InfoHeight 261
#define InfoOpacity 0.9
#define InfoBackgroundColor "background-color:#afdfe4"

#include <QDebug>

AboutInfo::AboutInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AboutInfo)
{
    ui->setupUi(this);

    // 居中显示
    QDesktopWidget * desktop = QApplication::desktop();
    move((desktop->width() - this->width())/2,(desktop->height() - this->height())/2);

    setWindowTitle(QString("关于Astriver鼠标连点器"));
    setFixedSize(InfoWidth, InfoHeight);
    setWindowOpacity(InfoOpacity);
    setStyleSheet(InfoBackgroundColor);

    // 设置窗口无标题栏、无任务栏、窗口置顶
    setWindowFlags(Qt::FramelessWindowHint | Qt::SubWindow | Qt::WindowStaysOnTopHint);

    ui->textBrowser->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//设置垂直滚动条不可见
    ui->textBrowser->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//设置水平滚动条不可见
    ui->textBrowser->setFocusPolicy(Qt::NoFocus);// 不接受任何聚焦
}

AboutInfo::~AboutInfo()
{
    delete ui;
}


// 点击窗口之外的位置即关闭窗口
bool AboutInfo::event(QEvent *e)
{
    if (e->type() == QEvent::ActivationChange)
    {
        if(QApplication::activeWindow() != this)
        {
            this->close();
        }
    }

    return QWidget::event(e);
}
