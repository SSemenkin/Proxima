#ifndef SETTINGSTABWIDGET_H
#define SETTINGSTABWIDGET_H

#include <QTabWidget>

namespace Ui {
class SettingsTabWidget;
}

class SettingsTabWidget : public QTabWidget
{
    Q_OBJECT

public:
    explicit SettingsTabWidget(QWidget *parent = nullptr);
    ~SettingsTabWidget();

private:
    Ui::SettingsTabWidget *m_ui;
};

#endif // SETTINGSTABWIDGET_H
