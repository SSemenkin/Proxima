#include "mainwindow.h"
#include "databases/databasemanager.h"
#include <QApplication>
#include <QLocale>
#include <QTranslator>

int main(int argc, char *argv[])
{
    int retCode {EXIT_SUCCESS};
    {

        QApplication a(argc, argv);
        DatabaseManager databaseManager;
        QTranslator translator;
        const QStringList uiLanguages = QLocale::system().uiLanguages();
        for (const QString &locale : uiLanguages) {
            const QString baseName = "Application_" + QLocale(locale).name();
            if (translator.load(":/i18n/" + baseName)) {
                a.installTranslator(&translator);
                break;
            }
        }
        MainWindow w;
        w.show();
        retCode = a.exec();
    }

    return retCode;
}
