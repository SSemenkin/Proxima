#include "settings.h"
#include "chiper/qaesencryption.h"
#include <QStandardPaths>
#include <QApplication>

QHash<DatabaseManager::DatabaseDestination, DatabaseParams> Settings::getDatabasesParams()
{
    QHash<DatabaseManager::DatabaseDestination, DatabaseParams> result;

    int size = beginReadArray("databases");

    DatabaseParams temporary;
    for (int i = 0; i < size; ++i) {
        setArrayIndex(i);
        temporary.databaseName = decode(value("databaseName").toByteArray());
        temporary.hostname = decode(value("hostname").toByteArray());
        temporary.username = decode(value("username").toByteArray());
        temporary.driver = decode(value("driver").toByteArray());
        temporary.password = decode(value("password").toByteArray());
        temporary.port = value("port").toInt();
        result.insert(static_cast<DatabaseManager::DatabaseDestination>(value("destination").toInt()), temporary);
    }
    endArray();

    return result;
}

void Settings::setDatabasesParams(const QHash<DatabaseManager::DatabaseDestination, DatabaseParams> &databasesParams)
{
    beginWriteArray("databases", databasesParams.size());

    int count {0};
    for (auto it = databasesParams.begin(); it != databasesParams.end(); ++it) {
        const DatabaseParams &args = it.value();
        setArrayIndex(count++);
        setValue("driver", encode(args.driver));
        setValue("hostname", encode(args.hostname));
        setValue("databaseName", encode(args.databaseName));
        setValue("username", encode(args.username));
        setValue("password", encode(args.password));
        setValue("port", args.port);
        setValue("destination", static_cast<int>(it.key()));
    }

    endArray();
}

Settings::Settings(QObject *parent) :
    QSettings(
        QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation) + "/config.ini"
        , QSettings::IniFormat
        , parent)
{
}

//static
QByteArray Settings::encode(const QString &source, const QString &key)
{
    return QAESEncryption::Crypt(QAESEncryption::AES_128,
                                 QAESEncryption::ECB,
                                 source.toUtf8(), key.toUtf8());
}
// static
QString Settings::decode(const QByteArray &source, const QString &key)
{
    QString result = QString::fromUtf8(QAESEncryption::Decrypt(QAESEncryption::AES_128,
                                  QAESEncryption::ECB,
                                  source, key.toUtf8()));
    return result.left(result.length() - 1);
}
