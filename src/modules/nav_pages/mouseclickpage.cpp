#include "mouseclickpage.h"

#include <QComboBox>
#include <QDoubleSpinBox>
#include <QFile>
#include <QLabel>
#include <QLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QRadioButton>
#include <QThread>

#include "../../utils/clicker.h"

QMap<Theme::ThemeMode, QString> MouseClickPage::_theme_files {
    {Theme::Light, (":/qss/modules/light-mouseclickpage.qss")},
    {Theme::Dark, (":/qss/modules/dark-mouseclickpage.qss")}
};

MouseClickPage::MouseClickPage(const QString& title, SettingsPage& settings_page, QWidget* parent)
    : NavPage{parent}
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

    QWidget* click_type_content = new QWidget(page_content);
    click_type_content->setFixedHeight(pageContentUniformHeight);

    QHBoxLayout* click_type_content_layout = new QHBoxLayout(click_type_content);
    click_type_content_layout->setSpacing(0);
    click_type_content_layout->setContentsMargins(QMargins());

    QLabel* click_type_desc = new QLabel(click_type_content);
    click_type_desc->setObjectName(QStringLiteral("click-type-desc"));
    click_type_desc->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    click_type_desc->setFocusPolicy(Qt::NoFocus);
    click_type_desc->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    click_type_desc->setText(tr("Click Type"));

    QComboBox* click_type_list = new QComboBox(click_type_content);
    click_type_list->setObjectName(QStringLiteral("click-type-list"));
    click_type_list->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    click_type_list->addItem(QIcon(":/svg/mouse-left.svg"), tr("Left Mouse Button"));
    click_type_list->addItem(QIcon(":/svg/mouse-right.svg"), tr("Right Mouse Button"));
    click_type_list->addItem(QIcon(":/svg/mouse-middle.svg"), tr("Middle Mouse Button"));

    click_type_content_layout->addWidget(click_type_desc);
    click_type_content_layout->addWidget(click_type_list);
    click_type_content->setLayout(click_type_content_layout);

    /********************/

    QWidget* interval_time_content = new QWidget(page_content);
    interval_time_content->setFixedHeight(pageContentUniformHeight);

    QHBoxLayout* interval_time_content_layout = new QHBoxLayout(interval_time_content);
    interval_time_content_layout->setSpacing(0);
    interval_time_content_layout->setContentsMargins(QMargins());

    QLabel* interval_time_desc = new QLabel(interval_time_content);
    interval_time_desc->setObjectName(QStringLiteral("interval-time-desc"));
    interval_time_desc->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    interval_time_desc->setFocusPolicy(Qt::NoFocus);
    interval_time_desc->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    interval_time_desc->setText(tr("Interval Time"));

    QDoubleSpinBox* interval_time = new QDoubleSpinBox(interval_time_content);
    interval_time->setObjectName(QStringLiteral("interval-time"));
    interval_time->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    interval_time->setDecimals(2);
    interval_time->setMaximum(100.00);
    interval_time->setMinimum(0.01);
    interval_time->setSingleStep(0.01);
    interval_time->setValue(0.01);

    interval_time_content_layout->addWidget(interval_time_desc);
    interval_time_content_layout->addWidget(interval_time);
    interval_time_content->setLayout(interval_time_content_layout);

    /********************/

    QWidget* random_interval_toggle_content = new QWidget(page_content);
    random_interval_toggle_content->setFixedHeight(pageContentUniformHeight);

    QHBoxLayout* random_interval_toggle_content_layout = new QHBoxLayout(random_interval_toggle_content);
    random_interval_toggle_content_layout->setSpacing(0);
    random_interval_toggle_content_layout->setContentsMargins(QMargins());

    QLabel* random_interval_toggle_desc = new QLabel(random_interval_toggle_content);
    random_interval_toggle_desc->setObjectName(QStringLiteral("random-interval-toggle-desc"));
    random_interval_toggle_desc->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    random_interval_toggle_desc->setFocusPolicy(Qt::NoFocus);
    random_interval_toggle_desc->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    random_interval_toggle_desc->setText(tr("Random Start Interval"));

    QRadioButton* random_interval_toggle_btn = new QRadioButton(random_interval_toggle_content);
    random_interval_toggle_btn->setObjectName(QStringLiteral("random-interval-toggle-btn"));
    random_interval_toggle_btn->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    random_interval_toggle_btn->setChecked(false);

    random_interval_toggle_content_layout->addWidget(random_interval_toggle_desc);
    random_interval_toggle_content_layout->addWidget(random_interval_toggle_btn);
    random_interval_toggle_content->setLayout(random_interval_toggle_content_layout);

    /********************/

    QWidget* random_interval_time_content = new QWidget(page_content);
    random_interval_time_content->setFixedHeight(pageContentUniformHeight);

    QHBoxLayout* random_interval_time_content_layout = new QHBoxLayout(random_interval_time_content);
    random_interval_time_content_layout->setSpacing(0);
    random_interval_time_content_layout->setContentsMargins(QMargins());

    QLabel* random_interval_time_desc = new QLabel(random_interval_time_content);
    random_interval_time_desc->setObjectName(QStringLiteral("random-interval-time-desc"));
    random_interval_time_desc->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    random_interval_time_desc->setFocusPolicy(Qt::NoFocus);
    random_interval_time_desc->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    random_interval_time_desc->setText(tr("Set Max Random Interval"));

    QDoubleSpinBox* random_interval_time = new QDoubleSpinBox(random_interval_time_content);
    random_interval_time->setObjectName(QStringLiteral("random-interval-time"));
    random_interval_time->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    random_interval_time->setDecimals(2);
    random_interval_time->setMaximum(100.00);
    random_interval_time->setMinimum(0.02);
    random_interval_time->setSingleStep(0.01);
    random_interval_time->setEnabled(false);

    random_interval_time_content_layout->addWidget(random_interval_time_desc);
    random_interval_time_content_layout->addWidget(random_interval_time);
    random_interval_time_content->setLayout(random_interval_time_content_layout);

    /********************/

    page_content_layout->addWidget(click_type_content);
    page_content_layout->addWidget(interval_time_content);
    page_content_layout->addWidget(random_interval_toggle_content);
    page_content_layout->addWidget(random_interval_time_content);
    page_content_layout->addStretch();

    central_layout->addWidget(page_title);
    central_layout->addWidget(page_content);

    setLayout(central_layout);

    /********************/

    connect(random_interval_toggle_btn, &QRadioButton::toggled, random_interval_time,[random_interval_time, interval_time](bool checked) {
        random_interval_time->setEnabled(checked);
        interval_time->setEnabled(!checked);
    });

    // hotkey event
    connect(settings_page._hotkey_reader, &HotkeyLineEdit::hotkeyActivated, this, [=, &settings_page]() {
        if (NavPage::_clicker_thread->isRunning()) {
            NavPage::_clicker->stop();
            NavPage::_clicker_thread->quit();
            NavPage::_clicker_thread->wait();

            click_type_list->setEnabled(true);
            interval_time->setEnabled(!random_interval_toggle_btn->isChecked());
            random_interval_toggle_btn->setEnabled(true);
            random_interval_time->setEnabled(random_interval_toggle_btn->isChecked());
        } else {
            Qt::MouseButton btn_type;
            if (click_type_list->currentIndex() == 0) {
                btn_type = Qt::LeftButton;
            } else if (click_type_list->currentIndex() == 1) {
                btn_type = Qt::RightButton;
            } else if (click_type_list->currentIndex() == 2) {
                btn_type = Qt::MiddleButton;
            } else {
                btn_type = Qt::LeftButton;
            }

            int interval = static_cast<int>(interval_time->value() * 1000);                     // 转为毫秒值
            bool random_interval_flag = random_interval_toggle_btn->isChecked();
            int max_random_interval = static_cast<int>(random_interval_time->value() * 1000);   // 转为毫秒值

            NavPage::_clicker->initParameters(btn_type, interval, random_interval_flag, max_random_interval);
            NavPage::_clicker_thread->start();   // Note: This should be initiated through a sub-thread.

            click_type_list->setEnabled(false);
            interval_time->setEnabled(false);
            random_interval_toggle_btn->setEnabled(false);
            random_interval_time->setEnabled(false);
        }
    });
}

MouseClickPage::~MouseClickPage()
{
    // There is a possibility that the user hasn't stopped clicking when closing the program.
    if (NavPage::_clicker_thread->isRunning()) {
        NavPage::_clicker->stop();
        NavPage::_clicker_thread->quit();
        NavPage::_clicker_thread->wait();
    }
}

QString& MouseClickPage::getThemeFiles(Theme::ThemeMode theme)
{
    return MouseClickPage::_theme_files[theme];
}
