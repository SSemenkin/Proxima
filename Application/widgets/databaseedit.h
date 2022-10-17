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
    explicit DatabaseEdit(int destination, int driver, const QString &hostname,
                          const QString &databaseName, const QString &username,
                          const QString &password, int port,
                          QWidget *parent = nullptr);

    ~DatabaseEdit();

    inline int destination() const {
        return m_destination;
    }
    [[nodiscard]] int port() const;
    [[nodiscard]] QString driver() const;
    [[nodiscard]] QString hostname() const;
    [[nodiscard]] QString databaseName() const;
    [[nodiscard]] QString username() const;
    [[nodiscard]] QString pasword() const;


    void setPort(int);
    void setDriver(int);
    void setDestination(int);
    void setHostname(const QString &hostname);
    void setDatabaseName(const QString &databaseName);
    void setUsername(const QString &username);
    void setPassword(const QString &password);

private:
    Ui::DatabaseEdit *m_ui;

    int m_destination;
};

#endif // DATABASEEDIT_H
