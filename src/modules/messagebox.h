#ifndef MESSAGEBOX_H
#define MESSAGEBOX_H

#include <QMessageBox>

#include "styleagent.h"

class MessageBox : public QMessageBox
{
    Q_OBJECT
public:
    explicit MessageBox(QWidget* parent = nullptr);
    ~MessageBox();

    void setIcon(Icon icon);

Q_SIGNALS:
    void ThemeChanged();

private:
    Q_DISABLE_COPY(MessageBox)

    StyleAgent& _style_agent;
    static QMap<Theme::ThemeMode, QString> _theme_files;

    void LoadThemeStyelSheet(Theme::ThemeMode theme);
};

#endif // MESSAGEBOX_H
