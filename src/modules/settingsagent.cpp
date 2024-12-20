#include "settingsagent.h"

#include "messagebox.h"

#include <QCoreApplication>
#include <QDesktopServices>
#include <QFile>
#include <QPushButton>
#include <QSettings>
#include <QTimer>
#include <QUrl>

SettingsAgent &SettingsAgent::instance()
{
    static SettingsAgent instance;
    return instance;
}

Theme::ThemeMode SettingsAgent::ThemeMode() const
{
    return static_cast<Theme::ThemeMode>(_config["ThemeMode"].toInt());
}

void SettingsAgent::setThemeMode(Theme::ThemeMode &theme_mode)
{
    if (_config["ThemeMode"].toInt() != static_cast<int>(theme_mode)) {
        _config["ThemeMode"] = theme_mode;
        emit currentThemeChanged(theme_mode);
    }
}

Qt::WindowStates SettingsAgent::WindowState() const
{
    return static_cast<Qt::WindowStates>(_config["WindowState"].toInt());
}

void SettingsAgent::setWindowSate(Qt::WindowStates &window_state)
{
    _config["WindowState"] = window_state.toInt();
}

QString SettingsAgent::Hotkey() const
{
    return _config["Hotkey"].toString();
}

void SettingsAgent::setHotkey(const QString &hotkey)
{
    _config["Hotkey"] = hotkey;
}

QString SettingsAgent::Language() const
{
    return _config["Language"].toString();
}

void SettingsAgent::setLanguage(const QString& language)
{
    if (_config["Language"].toString() != language) {
        _config["Language"] = language;
        emit currentLanguageChanged(language);
    }
}

SettingsAgent::SettingsAgent(QObject *parent)
    : QObject{parent}
{
    _settings_file_path = QCoreApplication::applicationDirPath() + "/config.ini";
    QFile settings_file(_settings_file_path);
    if (!settings_file.exists()) {
        MessageBox file_missing_msg;
        file_missing_msg.setWindowIcon(QIcon(":/svg/favicon.svg"));
        file_missing_msg.setIcon(QMessageBox::Warning);
        file_missing_msg.setText(tr("WARNING"));
        file_missing_msg.setInformativeText(tr("The configuration file 'condig.ini' was not found. The program may have been modified. It is recommended to reinstall the program, which may resolve this issue."));

        QPushButton* ignore_btn = file_missing_msg.addButton(tr("Ignore"), QMessageBox::NoRole);
        QPushButton* reinstall_btn = file_missing_msg.addButton(tr("Reinstall"), QMessageBox::YesRole);
        file_missing_msg.setDefaultButton(ignore_btn);

        file_missing_msg.exec();

        if (file_missing_msg.clickedButton() == reinstall_btn) {
            QDesktopServices::openUrl(QUrl("https://seayj.github.io/MouseClick/"));
        } else if (file_missing_msg.clickedButton() == ignore_btn) {
            // nothing to do
        } else {
            // nothing to do
        }
    }

    QSettings settings(_settings_file_path, QSettings::IniFormat);

    settings.beginGroup("MainWindow");
    _config["ThemeMode"] = settings.value("ThemeMode");
    _config["WindowState"] = settings.value("WindowState");
    settings.endGroup();

    settings.beginGroup("Settings");
    _config["Language"] = settings.value("Language");
    _config["Hotkey"] = settings.value("Hotkey");
    settings.endGroup();

    // 主题的特殊检查
    if (!Theme::isValidThemeMode(_config["ThemeMode"].toInt())) {
        _config["ThemeMode"] = _DEFAULT_THEMEMODE;
        QTimer::singleShot(0, this, [this](){   // 延迟发送，确保在对象初始化完成后发送信号
            emit currentThemeChanged(_DEFAULT_THEMEMODE);
        });
    }

    // 语言的特殊检查（必须确保可用）
    const QString language = _config["Language"].toString();
    if (language.isEmpty() || !_language_support_list.contains(language)) {
        _config["Language"] = _DEFAULT_LANGUAGE;
        QTimer::singleShot(0, this, [this]() {  // 延迟发送，确保在对象初始化完成后发送信号
            emit currentLanguageChanged(_DEFAULT_LANGUAGE);
        });
    }
}

SettingsAgent::~SettingsAgent()
{
    QSettings settings(_settings_file_path, QSettings::IniFormat);

    settings.beginGroup("MainWindow");
    settings.setValue("ThemeMode", _config["ThemeMode"]);
    settings.setValue("WindowState", _config["WindowState"]);
    settings.endGroup();

    settings.beginGroup("Settings");
    settings.setValue("Language", _config["Language"]);
    settings.setValue("Hotkey", _config["Hotkey"]);
    settings.endGroup();
}
