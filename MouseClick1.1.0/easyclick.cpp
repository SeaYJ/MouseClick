#include "easyclick.h"

#include <QDebug>

EasyClick::EasyClick(QObject *parent) : QObject(parent)
{
    isCanRun = true;
}

void EasyClick::closeThread()
{
    isCanRun = false;
}

void EasyClick::startThreadSlot()
{
    switch (indexOfClickType) {
        case 0:mouseLeft_click();break;
        case 1:mouseMiddle_click();break;
        case 2:mouseRight_click();break;
        default:throw QString("点击类型不存在！/n错误点击类型简码:/t%1").arg(indexOfClickType);
    }
}

void EasyClick::mouseLeft_click()
{
    while (true) {
        if (!isCanRun) { return; }
        clickPos_Y = QCursor::pos().x();
        clickPos_X = QCursor::pos().x();
        mouse_event(MOUSEEVENTF_LEFTDOWN, clickPos_X, clickPos_Y, 0, 0);
        mouse_event(MOUSEEVENTF_LEFTUP, clickPos_X, clickPos_Y, 0, 0);
        Sleep(clickTime);
    }
}

void EasyClick::mouseMiddle_click()
{
    while (true) {
        if (!isCanRun) { return; }
        clickPos_Y = QCursor::pos().x();
        clickPos_X = QCursor::pos().x();
        mouse_event(MOUSEEVENTF_MIDDLEDOWN, clickPos_X, clickPos_Y, 0, 0);
        mouse_event(MOUSEEVENTF_MIDDLEUP, clickPos_X, clickPos_Y, 0, 0);
        Sleep(clickTime);
    }
}


void EasyClick::mouseRight_click()
{
    while (true) {
        if (!isCanRun) { return; }
        clickPos_Y = QCursor::pos().x();
        clickPos_X = QCursor::pos().x();
        mouse_event(MOUSEEVENTF_RIGHTDOWN, clickPos_X, clickPos_Y, 0, 0);
        mouse_event(MOUSEEVENTF_RIGHTUP, clickPos_X, clickPos_Y, 0, 0);
        Sleep(clickTime);
    }
}

void EasyClick::setBasicValue(int indexOfClickTypeCode, int clickTimeValue)
{
    indexOfClickType = indexOfClickTypeCode;
    clickTime = clickTimeValue;
}
