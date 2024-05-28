#ifndef CLICKER_H
#define CLICKER_H

#include <QObject>
#include <QDebug>

class Clicker : public QObject
{
    Q_OBJECT
public:
    explicit Clicker(QObject* parent = nullptr);
    ~Clicker();
    Clicker& initParameters(Qt::MouseButton btnType,
                            int interval,
                            bool randomIntervalFlag,
                            int maxRandomInterval);

public Q_SLOTS:
    void start();
    void stop();

private:
    bool _run;
    Qt::MouseButton _btn_type;
    int _interval;
    bool _random_interval_flag;
    int _max_random_interval;

    void leftClick();
    void rightClick();
    void middleClick();

    void leftRandomClick();
    void rightRandomClick();
    void middleRandomClick();
};

#endif // CLICKER_H
