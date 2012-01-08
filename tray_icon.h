#ifndef TRAY_ICON_H
#define TRAY_ICON_H

#include <QApplication>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include <QSettings>

#include <config_window.h>
#include <trigger_socket.h>

class TrayIcon : public QSystemTrayIcon
{
    Q_OBJECT
public:
    TrayIcon();

signals:

public slots:
    void slotExit();
    void slotConfig();

private:
    QSettings * settings;

    TriggerSocket * trigger_socket;
    ConfigWindow * config_window;

    QMenu * context_menu;
    QAction * action_config;
    QAction * action_send;
    QAction * action_backup;
    QAction * action_exit;

    QIcon icon;

};

#endif // TRAY_ICON_H
