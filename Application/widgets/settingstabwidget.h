#ifndef SETTINGSTABWIDGET_H
#define SETTINGSTABWIDGET_H

#include <QTabWidget>

class Settings;

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
    void loadSettingsToUI();

private:
    Ui::SettingsTabWidget *m_ui;
    Settings &m_settings;
};

#endif // SETTINGSTABWIDGET_H
