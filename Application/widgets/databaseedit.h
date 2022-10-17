#ifndef DATABASEEDIT_H
#define DATABASEEDIT_H

#include <QWidget>

namespace Ui {
class DatabaseEdit;
}

class DatabaseEdit : public QWidget
{
    Q_OBJECT

public:
    explicit DatabaseEdit(int destination, QWidget *parent = nullptr);
    ~DatabaseEdit();

    inline int destination() const {
        return m_destination;
    }

private:
    Ui::DatabaseEdit *m_ui;

    int m_destination;
};

#endif // DATABASEEDIT_H
