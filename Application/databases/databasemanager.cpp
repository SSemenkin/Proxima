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

bool DatabaseManager::testConnection(DatabaseDestination destination)
{
    return m_databases[destination].open();
}

std::shared_ptr<SqlQueryExecutor> DatabaseManager::createExecutor(DatabaseDestination destination, const QString &query) const
{
    return std::make_shared<SqlQueryExecutor>(database(destination), query);
}

void DatabaseManager::saveDatabases()
{
    QVector<DatabaseParams> databasesParams;

    for (auto it = m_databases.begin(); it != m_databases.end(); ++it) {
        const auto& db = it.value();
        databasesParams.push_back(DatabaseParams(db.driverName(), db.hostName(), db.userName(), db.password(),
                                                 db.databaseName(), db.port(), static_cast<int>(it.key())));
    }

    Settings::instance()->setDatabasesParams(databasesParams);
}

void DatabaseManager::loadDatabases()
{
    const QVector<DatabaseParams> databasesParams = Settings::instance()->getDatabasesParams();

    for (const DatabaseParams &params : databasesParams) {
        QSqlDatabase db = QSqlDatabase::addDatabase(params.driver);
        db.setDatabaseName(params.databaseName);
        db.setHostName(params.hostname);
        db.setUserName(params.username);
        db.setPassword(params.password);
        db.setPort(params.port);

        m_databases[static_cast<DatabaseDestination>(params.destination)] = db;
    }
}
