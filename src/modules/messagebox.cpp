#include "messagebox.h"

#include <QFile>

MessageBox::MessageBox(QWidget* parent)
    : QMessageBox{parent}
{
    QFile style_file(":/qss/modules/messagebox.qss");

    if (style_file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        setStyleSheet(QString::fromUtf8(style_file.readAll()));
    }
}

MessageBox::~MessageBox() {}

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
