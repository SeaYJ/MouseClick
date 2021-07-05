#ifndef ABOUTINFO_H
#define ABOUTINFO_H

#include <QWidget>
#include <QDesktopWidget>

namespace Ui {
class AboutInfo;
}

class AboutInfo : public QWidget
{
    Q_OBJECT

public:
    explicit AboutInfo(QWidget *parent = nullptr);
    ~AboutInfo();

private:
    Ui::AboutInfo *ui;
    int desktopWidth, desktopHeight;
    bool event(QEvent * e);
};

#endif // ABOUTINFO_H
