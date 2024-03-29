#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>
#include <QHash>
#include <memory>
#include <QDebug>

class QSqlDatabase;
class SqlQueryExecutor;

#define get_shared_executor(destination, query) DatabaseManager::instance()->createExecutor(destination, query)

class DatabaseManager : public QObject
{
    Q_OBJECT
public:
    enum class DatabaseDestination : int32_t {
        CDR,
        EDR
    };

    static DatabaseManager *instance(); // valid until main loop is running, othewise instance == nullptr

    explicit DatabaseManager(QObject *parent = nullptr);
    ~DatabaseManager();

    [[nodiscard]] QSqlDatabase database(DatabaseDestination destination) const;
    void setDatabase(DatabaseDestination destination, QSqlDatabase database);

    [[nodiscard]] bool testConnection(DatabaseDestination destination) const;

    [[nodiscard]] std::shared_ptr<SqlQueryExecutor> createExecutor(DatabaseDestination destination,
                                     const QString &query) const;

signals:
private:
    void loadDatabases();
    void saveDatabases();
private:
    QHash<DatabaseDestination, QSqlDatabase> m_databases;
    static DatabaseManager *s_instance;
};

inline uint qHash(const DatabaseManager::DatabaseDestination &destination) {
    return qHash(static_cast<int>(destination));
}

inline QDebug operator << (QDebug debug, DatabaseManager::DatabaseDestination destination) {
    return debug << static_cast<int>(destination);
}

#endif // DATABASEMANAGER_H
