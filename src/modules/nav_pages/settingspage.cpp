#include "settingspage.h"

#include <QFile>
#include <QThread>
#include <QBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QRadioButton>
#include <QApplication>
#include <QComboBox>
#include <QDir>
#include <QTranslator>
#include <QProcess>
#include <QSettings>

#include "../hotkeylineedit.h"
#include "../languageagent.h"

QMap<Theme::ThemeMode, QString> SettingsPage::_theme_files {
    {Theme::Light, (":/qss/modules/light-settingspage.qss")},
    {Theme::Dark, (":/qss/modules/dark-settingspage.qss")}
};

SettingsPage::SettingsPage(const QString& title, QWidget* parent)
    : NavPage{parent},
      _style_agent(StyleAgent::instance()),
      _hotkey_reader(nullptr),
      _hotkey_clean(nullptr)
{
    LoadThemeStyleSheet(_style_agent.currentTheme());

    QVBoxLayout* central_layout = new QVBoxLayout(this);
    central_layout->setSpacing(0);
    central_layout->setContentsMargins(QMargins());

    QLabel* page_title = new QLabel(this);
    page_title->setObjectName(QStringLiteral("page-title"));
    page_title->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    page_title->setFocusPolicy(Qt::NoFocus);
    page_title->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    page_title->setText(title);
    page_title->setMaximumHeight(36);

    QWidget* page_content = new QWidget(this);
    page_content->setObjectName(QStringLiteral("page-content"));
    page_content->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    QVBoxLayout* page_content_layout = new QVBoxLayout(page_content);
    page_content_layout->setSpacing(12);
    page_content_layout->setContentsMargins(QMargins(0, 8, 0, 8));

    const int pageContentUniformHeight = 32;    // 统一控件高度

    /********************/

    QWidget* hotkey_content = new QWidget(page_content);
    hotkey_content->setFixedHeight(pageContentUniformHeight);

    QHBoxLayout* hotkey_content_layout = new QHBoxLayout(hotkey_content);
    hotkey_content_layout->setSpacing(0);
    hotkey_content_layout->setContentsMargins(QMargins());

    QLabel* hotkey_desc = new QLabel(hotkey_content);
    hotkey_desc->setObjectName(QStringLiteral("hotkey-desc"));
    hotkey_desc->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    hotkey_desc->setFocusPolicy(Qt::NoFocus);
    hotkey_desc->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    hotkey_desc->setText(tr("Start/End Hotkey"));

    _hotkey_reader = new HotkeyLineEdit(hotkey_content);
    _hotkey_reader->setObjectName(QStringLiteral("hotkey-reader"));
    _hotkey_reader->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    // 设置保存的快捷键（上一次使用）
    QString settings_file_path = QCoreApplication::applicationDirPath() + "/config.ini";
    QFile settings_file(settings_file_path);
    QSettings settings(settings_file_path, QSettings::IniFormat);
    settings.beginGroup("Settings");
    const QString pre_hotkey = settings.value("Hotkey").toString();
    if (pre_hotkey.isEmpty()) {
        _hotkey_reader->setHotkey("Ctrl+F2");   // 默认快捷键
    }
    else {
        _hotkey_reader->setHotkey(pre_hotkey);  // 上一次使用的快捷键
    }
    settings.endGroup();

    hotkey_content_layout->addWidget(hotkey_desc);
    hotkey_content_layout->addWidget(_hotkey_reader);
    hotkey_content->setLayout(hotkey_content_layout);

    /********************/

    _hotkey_clean = new QPushButton(page_content);
    _hotkey_clean->setObjectName(QStringLiteral("hotkey-clean-btn"));
    _hotkey_clean->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    _hotkey_clean->setFixedHeight(pageContentUniformHeight);
    _hotkey_clean->setText(tr("Hotkey Clean"));

    /********************/

    QWidget* theme_toggle_content = new QWidget(page_content);
    theme_toggle_content->setFixedHeight(pageContentUniformHeight);

    QHBoxLayout* theme_toggle_content_layout = new QHBoxLayout(theme_toggle_content);
    theme_toggle_content_layout->setSpacing(0);
    theme_toggle_content_layout->setContentsMargins(QMargins());

    QLabel* theme_toggle_desc = new QLabel(theme_toggle_content);
    theme_toggle_desc->setObjectName(QStringLiteral("theme-toggle-desc"));
    theme_toggle_desc->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    theme_toggle_desc->setFocusPolicy(Qt::NoFocus);
    theme_toggle_desc->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    theme_toggle_desc->setText(tr("Dark Theme"));

    QRadioButton* theme_toggle_btn = new QRadioButton(theme_toggle_content);
    theme_toggle_btn->setObjectName(QStringLiteral("theme-toggle-btn"));
    theme_toggle_btn->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    theme_toggle_btn->setChecked(static_cast<bool>(_style_agent.currentTheme()));

    theme_toggle_content_layout->addWidget(theme_toggle_desc);
    theme_toggle_content_layout->addWidget(theme_toggle_btn);
    theme_toggle_content->setLayout(theme_toggle_content_layout);

    /********************/

    QWidget* language_switch_content = new QWidget(page_content);
    language_switch_content->setFixedHeight(pageContentUniformHeight);

    QHBoxLayout* language_switch_content_layout = new QHBoxLayout(language_switch_content);
    language_switch_content_layout->setSpacing(0);
    language_switch_content_layout->setContentsMargins(QMargins());

    QLabel* language_switch_desc = new QLabel(language_switch_content);
    language_switch_desc->setObjectName(QStringLiteral("language-switch-desc"));
    language_switch_desc->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    language_switch_desc->setFocusPolicy(Qt::NoFocus);
    language_switch_desc->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    language_switch_desc->setText(tr("Language"));

    QComboBox* language_list = new QComboBox(language_switch_content);
    language_list->setObjectName(QStringLiteral("language-list"));
    language_list->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    language_list->addItem(tr("English(United States)"), QVariant("en_US"));
    language_list->addItem(tr("Chinese(Simplified)"), QVariant("zh_CN"));
    language_list->addItem(tr("Chinese(Traditional)"), QVariant("zh_TW"));

    // 确定当前的语言
    LanguageAgent& language_agent = LanguageAgent::instance();
    QString current_language = language_agent.currentLanguage();

    // 遍历 QComboBox 项目，找到对应的选项并设置为选中状态
    for (int i = 0; i < language_list->count(); ++i) {
        QVariant item_data = language_list->itemData(i);
        if (item_data.toString() == current_language) {
            language_list->setCurrentIndex(i);
            break;
        }
    }

    language_switch_content_layout->addWidget(language_switch_desc);
    language_switch_content_layout->addWidget(language_list);
    language_switch_content->setLayout(language_switch_content_layout);

    /********************/

    page_content_layout->addWidget(hotkey_content);
    page_content_layout->addWidget(_hotkey_clean);
    page_content_layout->addWidget(theme_toggle_content);
    page_content_layout->addWidget(language_switch_content);
    page_content_layout->addStretch();

    central_layout->addWidget(page_title);
    central_layout->addWidget(page_content);

    setLayout(central_layout);

    /********************/

    connect(_hotkey_clean, &QPushButton::clicked, this, [this]() {
        _hotkey_reader->cleanHotKey();
    });

    connect(theme_toggle_btn, &QRadioButton::toggled, this, [this](bool checked) {
        _style_agent.setCurrentTheme(static_cast<Theme::ThemeMode>(checked));
    });

    connect(_hotkey_reader, &HotkeyLineEdit::hotkeyActivated, this, [=]() {
        if (NavPage::_clicker_thread->isRunning()) {
            _hotkey_reader->setEnabled(true);
            _hotkey_clean->setEnabled(true);
        } else {
            _hotkey_reader->setEnabled(false);
            _hotkey_clean->setEnabled(false);
        }
    });

    connect(language_list, &QComboBox::currentIndexChanged, this, [=](int index) {
        LanguageAgent& language_agent = LanguageAgent::instance();  // 必须重新获取才能使用接口
        QString selected_language = language_list->itemData(index).toString();

        // 判断选择的语言是否和当前语言相同，不同则进行切换
        if (selected_language != language_agent.currentLanguage()) {
            language_agent.setCurrentLanguage(selected_language);

            // 重新启动应用程序以应用新语言
            QCoreApplication::exit(0);
            QStringList args = QCoreApplication::arguments();
            QProcess::startDetached(QCoreApplication::applicationFilePath(), args);
        }
    });
}

SettingsPage::~SettingsPage()
{
    QString settings_file_path = QCoreApplication::applicationDirPath() + "/config.ini";
    QSettings settings(settings_file_path, QSettings::IniFormat);

    settings.beginGroup("Settings");
    settings.setValue("Hotkey", _hotkey_reader->getHotkey());
    settings.endGroup();

    /************************/

    delete _hotkey_reader;
    delete _hotkey_clean;
}

QString& SettingsPage::getThemeFiles(Theme::ThemeMode theme)
{
    return SettingsPage::_theme_files[theme];
}
