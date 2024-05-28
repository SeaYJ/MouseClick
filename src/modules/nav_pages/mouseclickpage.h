#ifndef MOUSECLICKPAGE_H
#define MOUSECLICKPAGE_H

#include <QWidget>

#include "../styleagent.h"
#include "../../utils/clicker.h"

class MouseClickPage : public QWidget
{
    Q_OBJECT
public:
    explicit MouseClickPage(const QString& title, QWidget* parent = nullptr);
    ~MouseClickPage();

Q_SIGNALS:
    void ThemeChanged();

private:
    Q_DISABLE_COPY(MouseClickPage)

    StyleAgent& _style_agent;
    static QMap<Theme::ThemeMode, QString> _theme_files;
    Clicker* _clicker;
    QThread* _clicker_thread;

    void LoadThemeStyelSheet(Theme::ThemeMode theme);
};

#endif // MOUSECLICKPAGE_H
