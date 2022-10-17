#include "databaseedit.h"
#include "ui_databaseedit.h"

DatabaseEdit::DatabaseEdit(int destination,QWidget *parent) :
    QWidget(parent)
  , m_ui(new Ui::DatabaseEdit)
  , m_destination(destination)
{
    m_ui->setupUi(this);
}

DatabaseEdit::DatabaseEdit(int destination, int driver,
                           const QString &hostname, const QString &databaseName,
                           const QString &username, const QString &password,
                           int port, QWidget *parent) :
    QWidget(parent)
  , m_ui(new Ui::DatabaseEdit)
  , m_destination(destination)
{
    setHostname(hostname);
    setDatabaseName(databaseName);
    setUsername(username);
    setPassword(password);
    setDriver(driver);
    setPort(port);
}

DatabaseEdit::~DatabaseEdit()
{
    delete m_ui;
}

int DatabaseEdit::port() const
{
    bool ok;
    int port = m_ui->port->text().toInt(&ok);
    Q_ASSERT(ok);
    return port;
}

QString DatabaseEdit::driver() const
{
    return m_ui->driver->currentText();
}

QString DatabaseEdit::hostname() const
{
    return m_ui->hostname->text();
}

QString DatabaseEdit::databaseName() const
{
    return m_ui->database->text();
}

QString DatabaseEdit::username() const
{
    return m_ui->username->text();
}

QString DatabaseEdit::pasword() const
{
    return m_ui->password->text();
}

void DatabaseEdit::setPort(int port)
{
    m_ui->port->setText(QString::number(port));
}

void DatabaseEdit::setDriver(int driver)
{
    m_ui->driver->setCurrentIndex(driver);
}

void DatabaseEdit::setDestination(int destination)
{
    m_destination = destination;
}

void DatabaseEdit::setHostname(const QString &hostname)
{
    m_ui->hostname->setText(hostname);
}

void DatabaseEdit::setDatabaseName(const QString &databaseName)
{
    m_ui->database->setText(databaseName);
}

void DatabaseEdit::setUsername(const QString &username)
{
    m_ui->username->setText(username);
}

void DatabaseEdit::setPassword(const QString &password)
{
    m_ui->password->setText(password);
}
