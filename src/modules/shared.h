#ifndef SHARED_H
#define SHARED_H

// 重启程序
void restartApplication();

namespace Theme
{
    enum ThemeMode {
        Light,
        Dark
    };
    bool isValidThemeMode(const int value);
}

#endif // SHARED_H
