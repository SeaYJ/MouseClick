#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "aboutinfo.h"
#include "easyclick.h"
#include "normalclick.h"
#include "cretoolbar.h"

#include <QMainWindow>
#include <QLabel>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include <windows.h>
#include <QMap>
#include <QTime>
#include <QTimer>
#include <QFile>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private:
    Ui::MainWindow *ui;

    int indexOfClickType = 0, indexOfQuickStart = 7;
    int clickTime = 10, randomClickTimeMax = 100;
    bool IS_CANSTART = false, IS_RANDOMCLICK = false;

    ATOM HTK_RUN;
    QMap<int, UINT> hotKeyCode;

    QLabel * authorName;
    QSystemTrayIcon * m_sysTrayIcon = nullptr;
    QMenu * m_menu;
    QAction * show_button;
    QAction * about_button;
    QAction * quit_button;
    AboutInfo * aboutInfo = new AboutInfo;
    QThread * easyThread;
    EasyClick * easyClick;
    QThread * normalThread;
    NormalClick * normalClick;
    CreToolBar * toolBar = new CreToolBar;

    void changeEvent(QEvent * e);
    bool createSysTray();
    bool nativeEvent(const QByteArray &eventType, void *message, long *result);
    void createEasyThread();
    void createNormalThread();
    void activedSysTray(QSystemTrayIcon::ActivationReason reason);
    bool showMainWindow();

private slots:
    void on_clickType_currentIndexChanged(int index);
    void on_quickStart_currentIndexChanged(int index);
    void on_valueChanged(double value);
    void on_randomClickTime_currentIndexChanged(const QString maxTime);
    void closeEasyThreadSlot();
    void closeNormalThreadSlot();
    void on_randomClick_stateChanged(int stateCode);
};
#endif // MAINWINDOW_H
