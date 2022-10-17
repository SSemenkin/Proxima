#include "datamodel.h"

DataModel::DataModel(QObject *parent)
    : QAbstractTableModel{parent}
{

}

int DataModel::columnCount(const QModelIndex &index) const
{
    return index.isValid() ? m_headers.size() : 0;
}

int DataModel::rowCount(const QModelIndex &index) const
{
    return index.isValid() ? m_data.size() : 0;
}

QVariant DataModel::data(const QModelIndex &index, int role) const
{
    return index.isValid() && role == Qt::DisplayRole ?
                m_data.at(index.row()).at(index.column()) : QVariant{};
}
