#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QFont>
#include <QFontDatabase>

int main(int argc, char* argv[])
{
    QGuiApplication::setAttribute(Qt::AA_DontCreateNativeWidgetSiblings);
    qputenv("QT_WIN_DEBUG_CONSOLE", "attach");
    qputenv("QSG_INFO", "1");

    QApplication app(argc, argv);

    // 国际化
    QTranslator translator;
    const QStringList ui_languages = QLocale::system().uiLanguages();
    for (const QString& locale : ui_languages) {
        const QString base_name = "MouseClick_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + base_name)) {
            app.installTranslator(&translator);
            break;
        }
    }

    // 设置字体
    int font_id = QFontDatabase::addApplicationFont(":/fonts/HarmonyOS_Sans_SC/HarmonyOS_Sans_SC_Regular.ttf");
    if (font_id != -1) {
        QStringList font_families = QFontDatabase::applicationFontFamilies(font_id);
        if (!font_families.empty()) {
            QFont font(font_families.at(0), 12);
            app.setFont(font);
        }
    }

    MainWindow window(nullptr);
    window.show();

    return app.exec();
}
