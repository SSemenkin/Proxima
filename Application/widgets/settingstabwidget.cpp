#include "settingstabwidget.h"
#include "ui_settingstabwidget.h"

#include "widgets/databaseedit.h"
#include "databases/databasemanager.h"

SettingsTabWidget::SettingsTabWidget(QWidget *parent) :
    QTabWidget(parent),
    m_ui(new Ui::SettingsTabWidget)
{
    m_ui->setupUi(this);

    m_ui->horizontalLayout->addWidget(new DatabaseEdit(static_cast<int>(DatabaseManager::DatabaseDestination::CDR),
                                                       this));
    m_ui->horizontalLayout_2->addWidget(new DatabaseEdit(static_cast<int>(DatabaseManager::DatabaseDestination::EDR),
                                                       this));
}

SettingsTabWidget::~SettingsTabWidget()
{
    delete m_ui;
}
