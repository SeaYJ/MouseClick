#ifndef SETTINGSAGENT_H
#define SETTINGSAGENT_H

#include "shared.h"
#include <QFile>
#include <QMap>
#include <QObject>
#include <QSettings>

class SettingsAgent : public QObject
{
    Q_OBJECT
public:
    // 接口
    static SettingsAgent& instance();

    /***** 相关的 getter 与 settter *****/
    Theme::ThemeMode ThemeMode() const;
    void setThemeMode(Theme::ThemeMode& theme_mode);

    Qt::WindowStates WindowState() const;
    void setWindowSate(Qt::WindowStates& window_state);

    QString Hotkey() const;
    void setHotkey(const QString& hotkey);

    QString Language() const;
    void setLanguage(const QString& language);
    /***********************************/

signals:
    void currentThemeChanged(Theme::ThemeMode current_theme);
    void currentLanguageChanged(const QString current_language);

private:
    explicit SettingsAgent(QObject *parent = nullptr);
    ~SettingsAgent();
    Q_DISABLE_COPY(SettingsAgent);

    // 所有配置以键值对形式存储
    QMap<QString, QVariant> _config;

    // 配置文件完整文件路径
    QString _settings_file_path;

    // 默认主题设置
    const Theme::ThemeMode _DEFAULT_THEMEMODE = Theme::Light;

    // 默认语言设置
    const QString _DEFAULT_LANGUAGE = "en_US";
    // 支持语言列表
    const QStringList _language_support_list = {
        "en_US",
        "zh_CN",
        "zh_TW"
    };
};

#endif // SETTINGSAGENT_H
