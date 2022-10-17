#include "settingstabwidget.h"
#include "ui_settingstabwidget.h"

#include "widgets/databaseedit.h"
#include "databases/databasemanager.h"
#include "settings.h"

SettingsTabWidget::SettingsTabWidget(QWidget *parent) :
    QTabWidget(parent),
    m_ui(new Ui::SettingsTabWidget)
  , m_settings(*Settings::instance())
{
    m_ui->setupUi(this);

    loadSettingsToUI();
}

SettingsTabWidget::~SettingsTabWidget()
{
    delete m_ui;
}

void SettingsTabWidget::loadSettingsToUI()
{
    m_ui->horizontalLayout->addWidget(new DatabaseEdit(static_cast<int>(DatabaseManager::DatabaseDestination::CDR),
                                                       this));
    m_ui->horizontalLayout_2->addWidget(new DatabaseEdit(static_cast<int>(DatabaseManager::DatabaseDestination::EDR),
                                                       this));

    QVector<DatabaseParams> params = m_settings.getDatabasesParams();

    for (const DatabaseParams &args : params) {

    }
}
