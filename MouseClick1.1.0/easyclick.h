#ifndef EASYCLICK_H
#define EASYCLICK_H

#include <QObject>
#include <QThread>
#include <QCursor>
#include <windows.h>
#include <QString>

class EasyClick : public QObject
{
    Q_OBJECT
public:
    explicit EasyClick(QObject *parent = nullptr);

    void closeThread();
    void setBasicValue(int indexOfClickTypeCode, int clickTimeValue);

private:

    int clickPos_X = 0, clickPos_Y = 0;
    int indexOfClickType;
    int clickTime;
    volatile bool isCanRun;

    void mouseLeft_click();
    void mouseMiddle_click();
    void mouseRight_click();

private slots:

    void startThreadSlot();

};

#endif // EASYCLICK_H
