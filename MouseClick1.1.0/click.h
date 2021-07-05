#ifndef EASYCLICK_H
#define EASYCLICK_H

#include <QObject>
#include <QThread>
#include <QCursor>
#include <windows.h>
#include <QString>

class StartClick : public QObject
{
    Q_OBJECT
public:
    explicit StartClick(QObject *parent = nullptr);

    void closeThread();
    void setBasicValue(int indexOfClickTypeCode, int clickTimeValue);

private:

    int clickPos_X = 0, clickPos_Y = 0;
    int indexOfClickType;
    int clickTime;

    volatile bool isStop;

    void mouseLeft_click(int x, int y, double clickTime);
    void mouseMiddle_click(int x, int y, double clickTime);
    void mouseRight_click(int x, int y, double clickTime);

signals:

public slots:

    void startThreadSlot();

};

#endif // STARTCLICK_H
