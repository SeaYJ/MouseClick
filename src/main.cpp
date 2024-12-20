#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QFont>
#include <QFontDatabase>
#include <QSettings>
#include <QFile>

#include "modules/settingsagent.h"

int main(int argc, char* argv[])
{
    QGuiApplication::setAttribute(Qt::AA_DontCreateNativeWidgetSiblings);
    qputenv("QT_WIN_DEBUG_CONSOLE", "attach");
    qputenv("QSG_INFO", "1");

    QApplication app(argc, argv);

    // 国际化
    SettingsAgent& app_settings = SettingsAgent::instance(); // 全局第一次初始化
    QTranslator translator;
    const QString base_name = "MouseClick_" + app_settings.Language();
    if (translator.load(":/i18n/" + base_name)) {
        app.installTranslator(&translator);
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

    MainWindow window;
    window.show();

    return app.exec();
}
