#ifndef SETTINGSPAGE_H
#define SETTINGSPAGE_H

#include <QWidget>

#include "navpage.h"
#include "../styleagent.h"

class SettingsPage : public NavPage
{
    friend class MouseClickPage;

    Q_OBJECT
public:
    explicit SettingsPage(const QString& title, QWidget* parent = nullptr);
    ~SettingsPage();

private:
    Q_DISABLE_COPY(SettingsPage)

    StyleAgent& _style_agent;
    static QMap<Theme::ThemeMode, QString> _theme_files;
    HotkeyLineEdit* _hotkey_reader;
    QPushButton* _hotkey_clean;

    QString& getThemeFiles(Theme::ThemeMode theme) override;
};

#endif // SETTINGSPAGE_H
