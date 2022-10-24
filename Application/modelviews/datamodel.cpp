#include "datamodel.h"

#include "databases/databasemanager.h"

DataModel::DataModel(int destination, QObject *parent)
    : QAbstractTableModel{parent}
    , m_destination(destination)
{

}

int DataModel::columnCount(const QModelIndex &index) const
{
    (void) index;
    return m_queryResult.headers.size();
}

int DataModel::rowCount(const QModelIndex &index) const
{
    (void) index;
    return m_queryResult.data.size();
}

QVariant DataModel::data(const QModelIndex &index, int role) const
{
    return index.isValid() && role == Qt::DisplayRole ?
                m_queryResult.data.at(index.row()).at(index.column()) : QVariant{};
}

QVariant DataModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        return m_queryResult.headers.at(section);
    } else return QAbstractTableModel::headerData(section, orientation, role);
}

void DataModel::setQueryResult(const SqlQueryExecutor::QueryResult &queryResult)
{
    if (queryResult != m_queryResult) {
        beginResetModel();
        m_queryResult = queryResult;
        endResetModel();
    }
}

void DataModel::updateData(const QString &param)
{
    if (m_executor.get() == nullptr || (!m_executor->isBusy())) {
        const QString query = QString("select * from mss where callingpartynumber = '%1'").arg(param);
        m_executor = get_shared_executor(static_cast<DatabaseManager::DatabaseDestination>(m_destination), query);
        connect(m_executor.get(), &SqlQueryExecutor::finished, this, &DataModel::setQueryResult);
        connect(m_executor.get(), &SqlQueryExecutor::failed, this, &DataModel::error);
    } else {
        emit inProgress();
    }
}
