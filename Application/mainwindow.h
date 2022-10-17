#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class SettingsTabWidget;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void createConnections();
    void showSettingsWidget();
    void onLineEditReturnPressed();
    void showError(const QString &description);
private:
    Ui::MainWindow *m_ui;
    QScopedPointer<SettingsTabWidget> m_settingsWidget;
};
#endif // MAINWINDOW_H
