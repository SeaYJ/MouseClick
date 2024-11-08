#ifndef STYLEAGENT_H
#define STYLEAGENT_H

#include "qtmetamacros.h"

#include <QObject>

namespace Theme
{
    enum ThemeMode {
        Light,
        Dark
    };
}

class StyleAgent : public QObject
{
    Q_OBJECT
public:
    static StyleAgent& instance();

    Theme::ThemeMode currentTheme() const;
    void setCurrentTheme(Theme::ThemeMode theme);

Q_SIGNALS:
    void currentThemeChanged(Theme::ThemeMode current_theme);

private:
    explicit StyleAgent(QObject* parent = nullptr);
    StyleAgent(const StyleAgent&) = delete;
    StyleAgent& operator=(const StyleAgent&) = delete;

    Theme::ThemeMode _current_theme;
};

#endif // STYLEAGENT_H
