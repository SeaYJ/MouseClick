#include "languageagent.h"

#include <QCoreApplication>
#include <QFile>
#include <QSettings>

LanguageAgent& LanguageAgent::instance()
{
    static LanguageAgent instance;
    return instance;
}

const QString LanguageAgent::currentLanguage() const
{
    return _current_language;
}

void LanguageAgent::setCurrentLanguage(const QString &language_name)
{
    if (_current_language != language_name) {
        _current_language = language_name;
        emit currentLanguageChange(_current_language);  // 发送语言更改信号
    }
}

LanguageAgent::LanguageAgent(QObject *parent)
    : QObject{parent},
    _current_language("")
{
    QString settings_file_path = QCoreApplication::applicationDirPath() + "/config.ini";
    QFile settings_file(settings_file_path);
    if (settings_file.exists()) {
        QSettings settings(settings_file_path, QSettings::IniFormat);
        QString language = settings.value("Settings/language").toString();

        if (language.isEmpty()) {
            _current_language = _default_language;
        }
        else {
            _current_language = language;
        }
    }
    else {
        _current_language = _default_language;
    }

    saveLanguageConfig();                           // 保存配置

    connect(this, &LanguageAgent::currentLanguageChange, this, &LanguageAgent::saveLanguageConfig);
}

void LanguageAgent::saveLanguageConfig() const
{
    QString settings_file_path = QCoreApplication::applicationDirPath() + "/config.ini";
    QSettings settings(settings_file_path, QSettings::IniFormat);

    settings.beginGroup("Settings");
    settings.setValue("language", _current_language);
    settings.endGroup();
}
