#ifndef DATAMODEL_H
#define DATAMODEL_H

#include <QAbstractTableModel>
#include <QObject>

class DataModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit DataModel(QObject *parent = nullptr);

    int columnCount(const QModelIndex &index) const override;
    int rowCount(const QModelIndex &index) const override;
    QVariant data(const QModelIndex &index, int role) const override;

private:
    QStringList m_headers;
    QVector<QVector<QString>> m_data;
};

#endif // DATAMODEL_H
