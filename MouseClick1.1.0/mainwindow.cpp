#include "mainwindow.h"
#include "ui_mainwindow.h"

#define MainWindowWidth 500
#define MainWindowHeight 300
#define MainWindowOpacity 0.95

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setFixedSize(MainWindowWidth, MainWindowHeight);
    setWindowTitle(QString("鼠标连点器（测试版）"));
    setWindowOpacity(MainWindowOpacity);
    setWindowIcon(QIcon(":/icon/logo.png"));

    // 关闭时彻底关闭窗口并释放内存
    setAttribute(Qt::WA_DeleteOnClose, true);

    // 禁用状态栏右下角默认的小三角
    ui->statusbar->setSizeGripEnabled(false);

    // 设置永久信息
    authorName = new QLabel(this);
    authorName->setText("<a href='https://www.cnblogs.com/seafever/'"
                        "style='color:#f05b72;text-decoration:none'>"
                        "作者:Astriver "
                        "</a>");
    authorName->setOpenExternalLinks(true); // 设置可以打开链接地址
    ui->statusbar->addPermanentWidget(authorName);

    // 部分控件的设置
    ui->howToUse->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//设置垂直滚动条不可见
    ui->howToUse->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//设置水平滚动条不可见
    ui->howToUse->setFocusPolicy(Qt::NoFocus);// 不接受任何聚焦
    ui->howToUse_adv->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//设置垂直滚动条不可见
    ui->howToUse_adv->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//设置水平滚动条不可见
    ui->howToUse_adv->setFocusPolicy(Qt::NoFocus);
    ui->clickType->setFocusPolicy(Qt::NoFocus);
    ui->quickStart->setFocusPolicy(Qt::NoFocus);
    ui->randomClickTime->setFocusPolicy(Qt::NoFocus);
    ui->clickTime->setSingleStep(0.01);
    ui->clickTime->setMaximum(60.00);
    ui->clickTime->setMinimum(0.01);
    ui->clickTime->setSuffix("秒");
    connect(ui->clickTime, static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), [=](double value){
        on_valueChanged(value);
    });
    ui->clickTime->setToolTip(QString("上限:  60.00秒\n"
                                      "下限:  0.01秒\n"
                                      "提示:可直接输入想要的值哦！"));
    ui->clickTimeText->setToolTip(QString("按住Ctrl后滑动鼠标滑轮\n"
                                          "可加快调整速度哦!\n"
                                          "(●'◡'●)"));
    ui->randomClickTime->setEnabled(IS_RANDOMCLICK);
    ui->randomClickTime->setToolTip(QString("启动“随机间隔时间”功能后\n"
                                            "会自动解锁，并自动锁定“间隔时间”。\n"
                                            "(关闭“随机间隔时间”功能后将自动恢复)"));
    ui->randomClick->setToolTip(QString("启动该功能后系统会自动根据\n"
                                        "所给“最大间隔时间”的值\n"
                                        "自动生成一个“间隔时间”。\n"
                                        "(每次点击时都会自动生成)"));

    // 创建系统托盘
    if (m_sysTrayIcon == nullptr) { createSysTray(); }

    // 设置默认快捷启动键为F8
    ui->quickStart->setCurrentIndex(7);

    // 注册快捷键快捷码
    hotKeyCode[0] = VK_F1;
    hotKeyCode[1] = VK_F2;
    hotKeyCode[2] = VK_F3;
    hotKeyCode[3] = VK_F4;
    hotKeyCode[4] = VK_F5;
    hotKeyCode[5] = VK_F6;
    hotKeyCode[6] = VK_F7;
    hotKeyCode[7] = VK_F8;
    hotKeyCode[8] = VK_F9;
    hotKeyCode[9] = VK_F10;
    hotKeyCode[10] = VK_F11;
    hotKeyCode[11] = VK_F12;

    // 1 获取热键标识
    HTK_RUN = GlobalAddAtomA("HTK_RUN");
    // 2 注册默认全局热键
    RegisterHotKey(HWND(this->winId()), HTK_RUN, MOD_CONTROL, hotKeyCode[indexOfQuickStart]);

    connect(ui->newCreate, &QPushButton::clicked, [=]{
        qDebug()<< "请求录制工具栏！";
        toolBar->show();
    });

    // 导入样式文件
    QFile file(":/mainStyle/mainStyle.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = tr(file.readAll());
    this->setStyleSheet(styleSheet);
    file.close();
}

MainWindow::~MainWindow()
{
    // 3 销毁全局热键
    UnregisterHotKey(HWND(this->winId()), HTK_RUN);
    // 4 释放热键标识
    GlobalDeleteAtom(HTK_RUN);

    delete ui;
}

void MainWindow::changeEvent(QEvent *e)
{
    if (e->type() != QEvent::WindowStateChange) return;
    if (this->windowState() == Qt::WindowMinimized)
    {
        this->hide();
        return;
    }
}

bool MainWindow::createSysTray()
{
    m_sysTrayIcon = new QSystemTrayIcon(this);
    m_sysTrayIcon->setIcon(QIcon(":/icon/logo.png"));

    m_menu = new QMenu(this);

    // 托盘显示按钮
    show_button = new QAction(m_menu);
    show_button->setText(QString("显示(S)"));
    connect(show_button, &QAction::triggered, [=]{
        showMainWindow();
    });

    // 托盘关于按钮
    about_button = new QAction(m_menu);
    about_button->setText(QString("关于(A)"));
    connect(about_button, &QAction::triggered, [=]{
        aboutInfo->show();
    });

    // 托盘退出按钮
    quit_button = new QAction(m_menu);
    quit_button->setText(QString("退出(Q)"));
    connect(quit_button, &QAction::triggered, [=]{
        close();
    });

    m_menu->addAction(show_button);
    m_menu->addAction(about_button);
    m_menu->addAction(quit_button);
    m_sysTrayIcon->setContextMenu(m_menu);
    m_sysTrayIcon->show();

    connect(m_sysTrayIcon, &QSystemTrayIcon::activated, this, &MainWindow::activedSysTray);

    return true;
}

void MainWindow::activedSysTray(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason) {
    case QSystemTrayIcon::DoubleClick:
        showMainWindow();
        break;
    default:break;
    }
}

// 时时更新“点击类型”的改变
void MainWindow::on_clickType_currentIndexChanged(int index)
{
    indexOfClickType = index;
}

// 时时更新“快捷键”切换
void MainWindow::on_quickStart_currentIndexChanged(int index)
{
    // 释放旧快捷键
    UnregisterHotKey(HWND(this->winId()), HTK_RUN);
    // 注册新快捷键
    indexOfQuickStart = index;
    RegisterHotKey(HWND(this->winId()), HTK_RUN, MOD_CONTROL, hotKeyCode[indexOfQuickStart]);
}

// 时时更新“间隔时间”的值
void MainWindow::on_valueChanged(double value)
{
    clickTime = int(value * 1000);
}

// 时时更新“随机时间最大值”的值
void MainWindow::on_randomClickTime_currentIndexChanged(const QString maxTime)
{
    randomClickTimeMax = int(maxTime.toDouble() * 1000);
}

bool MainWindow::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
    if(eventType == "windows_generic_MSG"){

        MSG* pMsg = reinterpret_cast<MSG*>(message);

        if(pMsg->message == WM_HOTKEY){

            if(pMsg->wParam == HTK_RUN){

                IS_CANSTART = !IS_CANSTART;

                if((IS_CANSTART) && (!IS_RANDOMCLICK)){

                    createEasyThread();
                    easyClick->setBasicValue(indexOfClickType, clickTime);
                    easyThread->start();   // 开启线程

                } else if ((IS_CANSTART) && (IS_RANDOMCLICK)) {

                    createNormalThread();
                    normalClick->setBasicValue(indexOfClickType, randomClickTimeMax);
                    normalThread->start();

                } else if ((!IS_CANSTART) && (easyThread->isRunning())) {

                    closeEasyThreadSlot(); // 关闭一号线程并回收相关资源

                } else if ((!IS_CANSTART) && (normalThread->isRunning())) {

                    closeNormalThreadSlot(); // 关闭二号线程并回收相关资源

                }
            }
        }
    }

    return QWidget::nativeEvent(eventType,message,result);
}

// 彻底关闭一号线程并释放资源
void MainWindow::closeEasyThreadSlot()
{
    easyClick->closeThread();
    easyThread->quit();
    easyThread->wait();
}

// 彻底关闭二号线程并释放资源
void MainWindow::closeNormalThreadSlot()
{
    normalClick->closeThread();
    normalThread->quit();
    normalThread->wait();
}

// 创建一号线程
void MainWindow::createEasyThread()
{
    easyThread = new QThread;
    easyClick = new EasyClick;
    easyClick->moveToThread(easyThread);

    connect(easyThread, SIGNAL(finished()), easyClick, SLOT(deleteLater()));      // 在线程退出时，销毁该线程和相关资源
    connect(easyThread, SIGNAL(started()), easyClick, SLOT(startThreadSlot()));
}

// 创建二号线程
void MainWindow::createNormalThread()
{
    normalThread = new QThread;
    normalClick = new NormalClick;
    normalClick->moveToThread(normalThread);

    connect(normalThread, SIGNAL(finished()), normalClick, SLOT(deleteLater()));
    connect(normalThread, SIGNAL(started()), normalClick, SLOT(startThreadSlot()));
}

// 显示窗口函数：在最顶层显示窗口
bool MainWindow::showMainWindow()
{
    this->setWindowState(Qt::WindowActive);
    this->show();
    this->setWindowState(windowState() & ~Qt::WindowActive);

    return (this->windowState() == Qt::WindowActive);
}

// 随机间隔时间点击处理函数
void MainWindow::on_randomClick_stateChanged(int stateCode)
{

    (stateCode == Qt::Checked) ? (IS_RANDOMCLICK = true) : (IS_RANDOMCLICK = false);

    ui->randomClickTime->setEnabled(IS_RANDOMCLICK);
    ui->clickTime->setEnabled(!IS_RANDOMCLICK);
}
