#ifndef NAVPAGE_H
#define NAVPAGE_H

#include <QPushButton>
#include <QWidget>

#include "../styleagent.h"
#include "../hotkeylineedit.h"
#include "../../utils/clicker.h"

class NavPage : public QWidget
{
    Q_OBJECT
public:
    explicit NavPage(QWidget* parent = nullptr);
    ~NavPage();

Q_SIGNALS:
    void ThemeChanged();

protected:
    StyleAgent& _style_agent;
    static QMap<Theme::ThemeMode, QString> _theme_files;

    static Clicker* _clicker;
    static QThread* _clicker_thread;
    static bool _is_thread_initialized;

    virtual QString& getThemeFiles(Theme::ThemeMode theme) = 0;
    void LoadThemeStyleSheet(Theme::ThemeMode theme);
};

#endif // NAVPAGE_H
