#ifndef LANGUAGEAGENT_H
#define LANGUAGEAGENT_H

#include <QObject>

class LanguageAgent : public QObject
{
    Q_OBJECT
public:
    static LanguageAgent& instance();

    const QString currentLanguage() const;
    void setCurrentLanguage(const QString& language_name);

Q_SIGNALS:
    void currentLanguageChange(const QString current_language);

private:
    explicit LanguageAgent(QObject *parent = nullptr);
    Q_DISABLE_COPY(LanguageAgent);

    QString _current_language;
    const QString _default_language = "en_US";

    // 将语言信息配置保存到 config.ini 文件
    void saveLanguageConfig() const;
};

#endif // LANGUAGEAGENT_H
