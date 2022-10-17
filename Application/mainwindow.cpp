#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "widgets/settingstabwidget.h"
#include "modelviews/datamodel.h"
#include "databases/databasemanager.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);

    DataModel *model = new DataModel(static_cast<int>(DatabaseManager::DatabaseDestination::CDR), this);
    m_ui->tableView->setModel(model);

    createConnections();
}

MainWindow::~MainWindow()
{
    delete m_ui;
}

void MainWindow::createConnections()
{
    connect(m_ui->actionSettings, &QAction::triggered, this, &MainWindow::showSettingsWidget);
    connect(m_ui->lineEdit, &QLineEdit::returnPressed, this, &MainWindow::onLineEditReturnPressed);

    DataModel *model = static_cast<DataModel*>(m_ui->tableView->model());
    connect(model, &DataModel::error, this,
            &MainWindow::showError);
    connect(model, &DataModel::inProgress, this, [this] () ->void {
      showError("Executor is busy.");
    });
}

void MainWindow::showSettingsWidget()
{
    if (m_settingsWidget.isNull()) {
        m_settingsWidget.reset(new SettingsTabWidget);
    }
    m_settingsWidget->show();
}

void MainWindow::onLineEditReturnPressed()
{
    static_cast<DataModel*>(m_ui->tableView->model())->updateData(m_ui->lineEdit->text());
}

void MainWindow::showError(const QString &description)
{
    QMessageBox::information(this, "Error", description);
}

