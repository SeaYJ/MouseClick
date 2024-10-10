#include "settingspage.h"

#include <QFile>
#include <QThread>
#include <QBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QRadioButton>

#include "../hotkeylineedit.h"

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

    page_content_layout->addWidget(hotkey_content);
    page_content_layout->addWidget(_hotkey_clean);
    page_content_layout->addWidget(theme_toggle_content);
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
}

SettingsPage::~SettingsPage()
{
    delete _hotkey_reader;
    delete _hotkey_clean;
}

QString& SettingsPage::getThemeFiles(Theme::ThemeMode theme)
{
    return SettingsPage::_theme_files[theme];
}
