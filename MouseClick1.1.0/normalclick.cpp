#include "normalclick.h"

#include <QDebug>

NormalClick::NormalClick(QObject *parent) : QObject(parent)
{
    isCanRun = true;
}

void NormalClick::closeThread()
{
    isCanRun = false;
}

void NormalClick::startThreadSlot()
{
    switch (indexOfClickType) {
        case 0:mouseLeft_click();break;
        case 1:mouseMiddle_click();break;
        case 2:mouseRight_click();break;
        default:throw QString("点击类型不存在！/n错误点击类型简码:/t%1").arg(indexOfClickType);
    }
}


void NormalClick::mouseLeft_click()
{
    while (true) {
        if (!isCanRun) { return; }
        clickPos_Y = QCursor::pos().x();
        clickPos_X = QCursor::pos().x();
        mouse_event(MOUSEEVENTF_LEFTDOWN, clickPos_X, clickPos_Y, 0, 0);
        mouse_event(MOUSEEVENTF_LEFTUP, clickPos_X, clickPos_Y, 0, 0);
        Sleep(getRandomTime());
    }
}

void NormalClick::mouseMiddle_click()
{
    while (true) {
        if (!isCanRun) { return; }
        clickPos_Y = QCursor::pos().x();
        clickPos_X = QCursor::pos().x();
        mouse_event(MOUSEEVENTF_MIDDLEDOWN, clickPos_X, clickPos_Y, 0, 0);
        mouse_event(MOUSEEVENTF_MIDDLEUP, clickPos_X, clickPos_Y, 0, 0);
        Sleep(getRandomTime());
    }
}


void NormalClick::mouseRight_click()
{
    while (true) {
        if (!isCanRun) { return; }
        clickPos_Y = QCursor::pos().x();
        clickPos_X = QCursor::pos().x();
        mouse_event(MOUSEEVENTF_RIGHTDOWN, clickPos_X, clickPos_Y, 0, 0);
        mouse_event(MOUSEEVENTF_RIGHTUP, clickPos_X, clickPos_Y, 0, 0);
        Sleep(getRandomTime());
    }
}

void NormalClick::setBasicValue(int indexOfClickTypeCode, int clickTimeMaxValue)
{
    indexOfClickType = indexOfClickTypeCode;
    randomClickTimeMax = clickTimeMaxValue;
}

int NormalClick::getRandomTime()
{
    randomSeed = QTime::currentTime();
    qsrand(randomSeed.msec()+randomSeed.second()*1000);
    return (10+ qrand() % (randomClickTimeMax - 9));
}
