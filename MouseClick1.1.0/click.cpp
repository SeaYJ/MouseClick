#include "click.h"

#include <QDebug>

StartClick::StartClick(QObject *parent) : QObject(parent)
{
    isStop = false;
}

void StartClick::closeThread()
{
    isStop = true;
}

void StartClick::startThreadSlot()
{
    clickPos_Y = QCursor::pos().x();
    clickPos_X = QCursor::pos().x();

    switch (indexOfClickType) {
        case 0:mouseLeft_click(clickPos_X, clickPos_Y, clickTime);break;
        case 1:mouseMiddle_click(clickPos_X, clickPos_Y, clickTime);break;
        case 2:mouseRight_click(clickPos_X, clickPos_Y, clickTime);break;
        default:throw QString("点击类型不存在！/n错误点击类型简码:/t%1").arg(indexOfClickType);
    }
}

void StartClick::mouseLeft_click(int x, int y, double clickTime)
{
    while (true) {
        if (isStop) { return; }
        clickPos_Y = QCursor::pos().x();
        clickPos_X = QCursor::pos().x();
        mouse_event(MOUSEEVENTF_LEFTDOWN, x, y, 0, 0);
        mouse_event(MOUSEEVENTF_LEFTUP, x, y, 0, 0);
        Sleep(clickTime);
        qDebug()<<"clickTime="<<clickTime;
    }
}

void StartClick::mouseMiddle_click(int x, int y, double clickTime)
{
    while (true) {
        if (isStop) { return; }
        clickPos_Y = QCursor::pos().x();
        clickPos_X = QCursor::pos().x();
        mouse_event(MOUSEEVENTF_MIDDLEDOWN, x, y, 0, 0);
        mouse_event(MOUSEEVENTF_MIDDLEUP, x, y, 0, 0);
        Sleep(clickTime);
    }
}


void StartClick::mouseRight_click(int x, int y, double clickTime)
{
    while (true) {
        if (isStop) { return; }
        clickPos_Y = QCursor::pos().x();
        clickPos_X = QCursor::pos().x();
        mouse_event(MOUSEEVENTF_RIGHTDOWN, x, y, 0, 0);
        mouse_event(MOUSEEVENTF_RIGHTUP, x, y, 0, 0);
        Sleep(clickTime);
    }
}

void StartClick::setBasicValue(int indexOfClickTypeCode, int clickTimeValue)
{
    indexOfClickType = indexOfClickTypeCode;
    clickTime = clickTimeValue;
}
