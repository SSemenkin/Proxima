#include "databasemanager.h"
#include <QSqlDatabase>
#include "settings.h"
#include "sqlqueryexecutor.h"

DatabaseManager* DatabaseManager::s_instance {nullptr};

DatabaseManager *DatabaseManager::instance()
{
    return s_instance;
}

DatabaseManager::DatabaseManager(QObject *parent)
    : QObject{parent}
{
    Q_ASSERT(s_instance == nullptr);
    s_instance = this;
    loadDatabases();
}

DatabaseManager::~DatabaseManager()
{
    saveDatabases();
    s_instance = nullptr;
}

QSqlDatabase DatabaseManager::database(DatabaseDestination destination) const
{
    return m_databases.value(destination);
}

void DatabaseManager::setDatabase(DatabaseDestination destination, QSqlDatabase database)
{
    m_databases[destination] = database;
}

bool DatabaseManager::testConnection(DatabaseDestination destination) const
{
    QSqlDatabase database = m_databases.value(destination);
    return database.open();
}

std::shared_ptr<SqlQueryExecutor> DatabaseManager::createExecutor(DatabaseDestination destination, const QString &query) const
{
    return std::make_shared<SqlQueryExecutor>(database(destination), query);
}

void DatabaseManager::saveDatabases()
{
    QHash<DatabaseManager::DatabaseDestination, DatabaseParams> data;
    DatabaseParams params;

    for (auto it = m_databases.begin(); it != m_databases.end(); ++it) {
        params.databaseName = it.value().databaseName();
        params.hostname = it.value().hostName();
        params.username = it.value().userName();
        params.password = it.value().password();
        params.driver = it.value().driverName();
        params.port = it.value().port();
        data[it.key()] = params;
    }

    Settings::instance()->setDatabasesParams(data);
}

 void DatabaseManager::loadDatabases()
{
    QHash<DatabaseManager::DatabaseDestination, DatabaseParams> data = Settings::instance()->getDatabasesParams();

    for (auto it = data.begin(); it != data.end(); ++it) {
        const DatabaseParams &args = it.value();
        QSqlDatabase db = QSqlDatabase::addDatabase(args.driver);
        db.setDatabaseName(args.databaseName);
        db.setHostName(args.hostname);
        db.setUserName(args.username);
        db.setPassword(args.password);
        db.setPort(args.port);
        m_databases[it.key()] = db;
    }
}
