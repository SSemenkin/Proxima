#include "mainwindow.h"
#include "databases/databasemanager.h"
#include "settings.h"
#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QSqlDatabase>

void clearSqlConnections()
{
    for (const QString &connectionName : QSqlDatabase::connectionNames()) {
        QSqlDatabase::removeDatabase(connectionName);
    }
}

bool testChipper()
{
    QString source = "veryLongStringForTestCase1234567890";
    QByteArray crypted = Settings::instance()->encode(source);
    return source == Settings::instance()->decode(crypted);
}

int main(int argc, char *argv[])
{
    int retCode;
    {
        QApplication a(argc, argv);
        a.setApplicationName("Proxima");
        Q_ASSERT(testChipper());
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
        retCode =  a.exec();
    }
    clearSqlConnections();
    return retCode;
}
