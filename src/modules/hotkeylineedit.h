#ifndef HOTKEYLINEEDIT_H
#define HOTKEYLINEEDIT_H

#include <QLineEdit>
#include <QWidget>
#include <QKeyEvent>
#include <QKeySequence>
#include <QMouseEvent>
#include <QHotkey>

class HotkeyLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit HotkeyLineEdit(QWidget* parent = nullptr);
    ~HotkeyLineEdit();

Q_SIGNALS:
    void hotkeyActivated();

protected:
    void mousePressEvent(QMouseEvent* event) override;

    void focusInEvent(QFocusEvent* event) override;

    void focusOutEvent(QFocusEvent* event) override;

    void keyPressEvent(QKeyEvent* event) override;

    void keyReleaseEvent(QKeyEvent* event) override;

private:
    QString _key_sequence;

    QSet<int> _pressed_keys;    // 当前被按下的所有按键

    QHotkey* _hotkey = nullptr;

    void registerGlobalHotkey();
    void unregisterGlobalHotkey();
};

#endif // HOTKEYLINEEDIT_H
