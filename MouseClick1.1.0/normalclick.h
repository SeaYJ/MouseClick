#ifndef NORMALCLICK_H
#define NORMALCLICK_H

#include <QObject>
#include <QThread>
#include <QCursor>
#include <windows.h>
#include <QString>
#include <QTime>

class NormalClick : public QObject
{
    Q_OBJECT
public:
    explicit NormalClick(QObject *parent = nullptr);

    void closeThread();
    void setBasicValue(int indexOfClickTypeCode, int randomClickTimeMaxValue);

private:

    int clickPos_X = 0, clickPos_Y = 0;
    int indexOfClickType;
    int randomClickTimeMax;
    volatile bool isCanRun;

    QTime randomSeed;

    void mouseLeft_click();
    void mouseMiddle_click();
    void mouseRight_click();
    int getRandomTime();

private slots:

    void startThreadSlot();
};

#endif // NORMALCLICK_H
