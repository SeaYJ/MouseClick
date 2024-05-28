#include "clicker.h"

#include <QRandomGenerator>
#include <QThread>

#if defined(Q_OS_WIN)
#include <windows.h>
#endif

Clicker::Clicker(QObject* parent)
    : QObject{parent},
      _run(false),
      _btn_type(Qt::LeftButton),
      _interval(10),
      _random_interval_flag(false),
      _max_random_interval(20)
{}

Clicker::~Clicker()
{
}

Clicker& Clicker::initParameters(Qt::MouseButton btnType,
                                 int interval,
                                 bool randomIntervalFlag,
                                 int maxRandomInterval)
{
    _btn_type = btnType;
    _interval = interval;
    _random_interval_flag = randomIntervalFlag;
    _max_random_interval = maxRandomInterval;

    return (*this);
}

void Clicker::start()
{
    _run = true;

    switch(_btn_type) {
        case Qt::LeftButton: {
            if (_random_interval_flag) {
                leftRandomClick();
            } else {
                leftClick();
            }
        }
        break;
        case Qt::RightButton: {
            if (_random_interval_flag) {
                rightRandomClick();
            } else {
                rightClick();
            }
        }
        break;
        case Qt::MiddleButton: {
            if (_random_interval_flag) {
                middleRandomClick();
            } else {
                middleClick();
            }
        }
        break;
        default:
            break;
    }
}

void Clicker::stop()
{
    _run = false;
}

#if defined(Q_OS_WIN)
void Clicker::leftClick()
{
    POINT mouse_pos;

    while (_run) {
        GetCursorPos(&mouse_pos);
        mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, mouse_pos.x, mouse_pos.y, 0, 0);
        QThread::msleep(_interval);
    }
}

void Clicker::rightClick()
{
    POINT mouse_pos;

    while (_run) {
        GetCursorPos(&mouse_pos);
        mouse_event(MOUSEEVENTF_RIGHTDOWN | MOUSEEVENTF_RIGHTUP, mouse_pos.x, mouse_pos.y, 0, 0);
        QThread::msleep(_interval);
    }
}

void Clicker::middleClick()
{
    POINT mouse_pos;

    while (_run) {
        GetCursorPos(&mouse_pos);
        mouse_event(MOUSEEVENTF_MIDDLEDOWN | MOUSEEVENTF_MIDDLEUP, mouse_pos.x, mouse_pos.y, 0, 0);
        QThread::msleep(_interval);
    }
}

void Clicker::leftRandomClick()
{
    POINT mouse_pos;

    while (_run) {
        GetCursorPos(&mouse_pos);
        mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, mouse_pos.x, mouse_pos.y, 0, 0);
        QThread::msleep(QRandomGenerator::global()->bounded(0, _max_random_interval));
    }
}

void Clicker::rightRandomClick()
{
    POINT mouse_pos;

    while (_run) {
        GetCursorPos(&mouse_pos);
        mouse_event(MOUSEEVENTF_RIGHTDOWN | MOUSEEVENTF_RIGHTUP, mouse_pos.x, mouse_pos.y, 0, 0);
        QThread::msleep(QRandomGenerator::global()->bounded(0, _max_random_interval));
    }
}

void Clicker::middleRandomClick()
{
    POINT mouse_pos;

    while (_run) {
        GetCursorPos(&mouse_pos);
        mouse_event(MOUSEEVENTF_MIDDLEDOWN | MOUSEEVENTF_MIDDLEUP, mouse_pos.x, mouse_pos.y, 0, 0);
        QThread::msleep(QRandomGenerator::global()->bounded(0, _max_random_interval));
    }
}
#endif
