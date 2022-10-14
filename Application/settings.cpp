#include "settings.h"
#include "chiper/qaesencryption.h"

QVector<DatabaseParams> Settings::getDatabasesParams() const
{
    QVector<DatabaseParams> result;
    return result;
}

void Settings::setDatabasesParams(const QVector<DatabaseParams> &databasesParams)
{

}

Settings::Settings(QObject *parent) : QSettings(parent)
{

}

//static
QString Settings::encode(const QString &source, const QString &key)
{
    return QAESEncryption::Crypt(QAESEncryption::AES_128,
                                 QAESEncryption::ECB,
                                 source.toUtf8(), key.toUtf8());
}
// static
QString Settings::decode(const QString &source, const QString &key)
{
    return QAESEncryption::Decrypt(QAESEncryption::AES_128,
                                  QAESEncryption::ECB,
                                  source.toUtf8(), key.toUtf8());
}
