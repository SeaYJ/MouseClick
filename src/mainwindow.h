#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "modules/shared.h"

#include <QMainWindow>

namespace QWK
{
    class WidgetWindowAgent;
}

template <class Key, class T> class QMap;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

protected:
    bool event(QEvent *event) override;

signals:
    void windowStateChanged(Qt::WindowStates newState);

private:
    Q_DISABLE_COPY(MainWindow)

    QWK::WidgetWindowAgent* _window_agent;
    static QMap<Theme::ThemeMode, QString> _theme_files;

    void windowInit(const QString& title, const QIcon& icon);
    void loadThemeStyelSheet(Theme::ThemeMode theme);
    void UIWidgetInit();
    void connectInit();

};
#endif // MAINWINDOW_H
