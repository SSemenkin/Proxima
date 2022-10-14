#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>
#include <QHash>
#include <memory>

class QSqlDatabase;
class SqlQueryExecutor;

#define get_shared_executor(destination, query) DatabaseManager::instanse()->createExecutor(destination, query)

class DatabaseManager : public QObject
{
    Q_OBJECT
public:
    enum class DatabaseDestination
    {
        CDR,
        EDR
    };

    static DatabaseManager *instance();

    explicit DatabaseManager(QObject *parent = nullptr);
    ~DatabaseManager();

    [[nodiscard]] QSqlDatabase database(DatabaseDestination destination) const;
    void setDatabase(DatabaseDestination destination, QSqlDatabase database);

    bool testConnection(DatabaseDestination destination);

    std::shared_ptr<SqlQueryExecutor> createExecutor(DatabaseDestination destination,
                                     const QString &query) const;

signals:
private:
    void loadDatabases();
    void saveDatabases();
private:
    QHash<DatabaseDestination, QSqlDatabase> m_databases;
    static DatabaseManager *s_instance;
};

#endif // DATABASEMANAGER_H
