#include "shared.h"

#include <QCoreApplication>
#include <QFile>
#include <QProcess>

void restartApplication()
{
    // 获取当前应用路径和参数
    QString appPath = QCoreApplication::applicationFilePath();
    QStringList args = QCoreApplication::arguments();
    QString currentPid = QString::number(QCoreApplication::applicationPid());

    // 根据平台生成脚本路径
    QString scriptPath;
#ifdef Q_OS_WIN
    scriptPath = QCoreApplication::applicationDirPath() + "/restart.bat";

    // 创建 Windows 重启脚本
    QFile scriptFile(scriptPath);
    if (!scriptFile.exists()) {
        scriptFile.open(QIODevice::WriteOnly);
        scriptFile.write(
            "@echo off\n"
            ":wait\n"
            "tasklist | find /i \"%1\" >nul\n"
            "if not errorlevel 1 (\n"
            "    timeout /t 1 >nul\n"
            "    goto wait\n"
            ")\n"
            "start \"\" \"%2\"\n"
            );
        scriptFile.close();
    }

    // 使用脚本重启程序
    QProcess::startDetached("cmd", {"/c", scriptPath, currentPid, appPath});
#else
    scriptPath = QCoreApplication::applicationDirPath() + "/restart.sh";

    // 创建 Linux 重启脚本
    QFile scriptFile(scriptPath);
    if (!scriptFile.exists()) {
        scriptFile.open(QIODevice::WriteOnly);
        scriptFile.write(
            "#!/bin/bash\n"
            "while ps -p \"$1\" > /dev/null; do\n"
            "    sleep 1\n"
            "done\n"
            "\"$2\" \"$@\" &\n"
            );
        scriptFile.close();

        // 添加执行权限
        QFile::Permissions permissions = scriptFile.permissions();
        scriptFile.setPermissions(permissions | QFile::ExeOwner | QFile::ExeGroup | QFile::ExeOther);
    }

    // 使用脚本重启程序
    QProcess::startDetached("/bin/bash", {scriptPath, currentPid, appPath});
#endif

    // 退出当前应用
    QCoreApplication::quit();
}

bool Theme::isValidThemeMode(const int value)
{
    switch (value) {
    case Theme::Light:
    case Theme::Dark:
        return true;
    default:
        return false;
    }
}
