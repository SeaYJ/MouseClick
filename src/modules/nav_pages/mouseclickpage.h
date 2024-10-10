#ifndef MOUSECLICKPAGE_H
#define MOUSECLICKPAGE_H

#include <QWidget>

#include "navpage.h"
#include "settingspage.h"

class MouseClickPage : public NavPage
{
    Q_OBJECT
public:
    explicit MouseClickPage(const QString& title, SettingsPage& settings_page, QWidget* parent = nullptr);
    ~MouseClickPage();

private:
    Q_DISABLE_COPY(MouseClickPage)

    static QMap<Theme::ThemeMode, QString> _theme_files;

    QString& getThemeFiles(Theme::ThemeMode theme) override;
};

#endif // MOUSECLICKPAGE_H
