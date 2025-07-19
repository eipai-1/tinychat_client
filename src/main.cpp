#include <QApplication>
#include <QLocale>
#include <QTranslator>

#include "core/app_controller.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "tinychat_client_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }

    tcc::core::AppController controller;
    controller.run();

    return a.exec();
}
