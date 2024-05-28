#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "modules/styleagent.h"

namespace QWK
{
    class WidgetWindowAgent;
}

class MainWindow;
class QMainWindow;
class QWidget;
template <class Key, class T> class QMap;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private:
    Q_DISABLE_COPY(MainWindow)

    QWK::WidgetWindowAgent* _window_agent;
    StyleAgent& _style_agent;
    static QMap<Theme::ThemeMode, QString> _theme_files;

    void windowInit(const QString& title, const QIcon& icon);
    void loadSettings();
    void loadThemeStyelSheet(Theme::ThemeMode theme);
    void UIWidgetInit();
    void connectInit();

};
#endif // MAINWINDOW_H
