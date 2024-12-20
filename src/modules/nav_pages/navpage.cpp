#include "navpage.h"
#include "../shared.h"
#include "../settingsagent.h"

#include <QFile>
#include <QThread>

QMap<Theme::ThemeMode, QString> NavPage::_theme_files {};

Clicker* NavPage::_clicker = new Clicker();
QThread* NavPage::_clicker_thread = new QThread();
bool NavPage::_is_thread_initialized = false;

NavPage::NavPage(QWidget* parent)
    : QWidget{parent}
{
    disconnect(&SettingsAgent::instance(), &SettingsAgent::currentThemeChanged, this, &NavPage::LoadThemeStyleSheet);
    connect(&SettingsAgent::instance(), &SettingsAgent::currentThemeChanged, this, &NavPage::LoadThemeStyleSheet);

    // Thread initialization once
    if (!_is_thread_initialized) {
        NavPage::_clicker->moveToThread(NavPage::_clicker_thread);
        connect(NavPage::_clicker_thread, &QThread::started, NavPage::_clicker, &Clicker::start);
        _is_thread_initialized = true;
    }
}

NavPage::~NavPage()
{
}

void NavPage::LoadThemeStyleSheet(Theme::ThemeMode theme)
{
    QFile style_file(getThemeFiles(theme));
    if (style_file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        setStyleSheet(QString::fromUtf8(style_file.readAll()));
    }
}
