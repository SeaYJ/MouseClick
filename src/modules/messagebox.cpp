#include "messagebox.h"

#include <QFile>

QMap<Theme::ThemeMode, QString> MessageBox::_theme_files {
    {Theme::Light, (":/qss/modules/light-messagebox.qss")},
    {Theme::Dark, (":/qss/modules/dark-messagebox.qss")}
};

MessageBox::MessageBox(QWidget* parent)
    : QMessageBox{parent},
      _style_agent(StyleAgent::instance())
{
    LoadThemeStyelSheet(_style_agent.currentTheme());
}

MessageBox::~MessageBox()
{

}

void MessageBox::setIcon(Icon icon)
{
    QString styleSheet;
    switch (icon) {
        case QMessageBox::Information:
            styleSheet = "QMessageBox QLabel#qt_msgbox_label { color: #0099CC; }";
            break;
        case QMessageBox::Warning:
            styleSheet = "QMessageBox QLabel#qt_msgbox_label { color: #E6A23C; }";
            break;
        case QMessageBox::Critical:
            styleSheet = "QMessageBox QLabel#qt_msgbox_label { color: #F56C6C; }";
            break;
        case QMessageBox::Question:
            styleSheet = "QMessageBox QLabel#qt_msgbox_label { color: #409EFF; }";
            break;
        default:
            styleSheet = "";
            break;
    }
    this->setStyleSheet(styleSheet);
    QMessageBox::setIcon(icon);
}

void MessageBox::LoadThemeStyelSheet(Theme::ThemeMode theme)
{
    QFile style_file(_theme_files[theme]);
    if (style_file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        setStyleSheet(QString::fromUtf8(style_file.readAll()));
    }
}
