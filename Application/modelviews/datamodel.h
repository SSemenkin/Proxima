#ifndef DATAMODEL_H
#define DATAMODEL_H

#include <QAbstractTableModel>
#include <QObject>
#include <QSharedPointer>

#include "sqlqueryexecutor.h"

class DataModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit DataModel(int destination, QObject *parent = nullptr);

    int columnCount(const QModelIndex &index) const override;
    int rowCount(const QModelIndex &index) const override;
    QVariant data(const QModelIndex &index, int role) const override;

    void setQueryResult(const SqlQueryExecutor::QueryResult &queryResult);
    void updateData(const QString &param);

signals:
    void inProgress();
    void error(const QString &description);

private:
    std::shared_ptr<SqlQueryExecutor> m_executor;
    SqlQueryExecutor::QueryResult m_queryResult;
    int m_destination;
};

#endif // DATAMODEL_H
