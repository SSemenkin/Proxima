#include "databaseedit.h"
#include "ui_databaseedit.h"

DatabaseEdit::DatabaseEdit(int destination,QWidget *parent) :
    QWidget(parent),
    m_ui(new Ui::DatabaseEdit)
  , m_destination(destination)
{
    m_ui->setupUi(this);
}

DatabaseEdit::~DatabaseEdit()
{
    delete m_ui;
}
