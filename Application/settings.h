#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>
#include <QObject>

#include "utils/singleton.h"

struct DatabaseParams
{
    DatabaseParams(const QString &driver, const QString &hostname, const QString &username,
                   const QString &password, const QString &databaseName, int port, int destination)
        : driver(driver)
        , hostname(hostname)
        , username(username)
        , password(password)
        , databaseName(databaseName)
        , port(port)
        , destination(destination)
    {

    }
    QString driver;
    QString hostname;
    QString username;
    QString password;
    QString databaseName;
    int port;
    int destination;
};

class Settings : protected QSettings, public Singleton<Settings>
{
    Q_OBJECT
public:
    [[nodiscard]] QVector<DatabaseParams> getDatabasesParams() const;
    void setDatabasesParams(const QVector<DatabaseParams> &databasesParams);
protected:
    explicit Settings(QObject *parent = nullptr);

private:
    static QString encode(const QString &souce, const QString &key);
    static QString decode(const QString &source, const QString &key);
};

#endif // SETTINGS_H
