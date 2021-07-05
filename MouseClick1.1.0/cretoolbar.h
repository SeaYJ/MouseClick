#ifndef CRETOOLBAR_H
#define CRETOOLBAR_H

#include <QWidget>
#include <QString>

namespace Ui {
class CreToolBar;
}

class CreToolBar : public QWidget
{
    Q_OBJECT

public:
    explicit CreToolBar(QWidget *parent = nullptr);
    ~CreToolBar();

private:
    Ui::CreToolBar *ui;
};

#endif // CRETOOLBAR_H
