#include "styleagent.h"

StyleAgent::StyleAgent(QObject* parent) : QObject(parent), _current_theme(Theme::Light)
{
}

StyleAgent& StyleAgent::instance()
{
    static StyleAgent instance;
    return instance;
}

Theme::ThemeMode StyleAgent::currentTheme() const
{
    return _current_theme;
}

void StyleAgent::setCurrentTheme(Theme::ThemeMode theme)
{
    if (_current_theme != theme) {
        _current_theme = theme;
        emit currentThemeChanged(theme);
    }
}
