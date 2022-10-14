#include "settings.h"
#include "chiper/qaesencryption.h"
#include <QStandardPaths>
#include <QApplication>

QVector<DatabaseParams> Settings::getDatabasesParams() const
{
    QVector<DatabaseParams> result;
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
