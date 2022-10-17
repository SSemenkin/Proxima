#include "settings.h"
#include "chiper/qaesencryption.h"
#include <QStandardPaths>
#include <QApplication>

QVector<DatabaseParams> Settings::getDatabasesParams()
{
    QVector<DatabaseParams> result;

    int size = beginReadArray("databases");

    DatabaseParams temporary;
    for (int i = 0; i < size; ++i) {
        setArrayIndex(i);
        temporary.databaseName = decode(value("databaseName").toByteArray());
        temporary.hostname = decode(value("hostname").toByteArray());
        temporary.username = decode(value("username").toByteArray());
        temporary.destination = value("destination").toInt();
        temporary.driver = decode(value("driver").toByteArray());
        temporary.password = decode(value("password").toByteArray());
        temporary.port = value("port").toInt();
        result.push_back(temporary);
    }
    endArray();

    return result;
}

void Settings::setDatabasesParams(const QVector<DatabaseParams> &databasesParams)
{
    beginWriteArray("databases", databasesParams.size());

    for (int i = 0; i < databasesParams.size(); ++i) {
        const DatabaseParams &args = databasesParams.at(i);
        setArrayIndex(i);
        setValue("driver", encode(args.driver));
        setValue("hostname", encode(args.hostname));
        setValue("databaseName", encode(args.databaseName));
        setValue("username", encode(args.username));
        setValue("password", encode(args.password));
        setValue("port", args.port);
        setValue("destination", args.destination);
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
