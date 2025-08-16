#include <QApplication>
#include <QLocale>
#include <QTranslator>

#include "model/room.h"
#include "core/tinychat_client.h"

int main(int argc, char *argv[]) {
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

    qRegisterMetaType<tcc::model::Room>();

    tcc::core::TinychatClient client;
    client.run();

    return a.exec();
}
