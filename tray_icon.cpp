#include "tray_icon.h"

TrayIcon::TrayIcon() :
    QSystemTrayIcon(0)
{
    bool firstRun = false;

    settings = new QSettings("k3d3","1sss");
    trigger_socket = new TriggerSocket();

    if (settings->value("firstRun", false) == false) {
        firstRun = true;
    }
    config_window = new ConfigWindow(this, settings);

    context_menu = new QMenu();

    action_config = new QAction("Configure 1sss...", context_menu);
    action_send = new QAction("Send to Image Service", context_menu);
    action_send->setCheckable(true);
    if (settings->value("online_service", 0) == 0) {
        action_send->setDisabled(true);
    }
    else if (settings->value("send_online", false) == true) {
        action_send->setChecked(true);
    }

    action_backup = new QAction("Save to Local Directory", context_menu);
    action_backup->setCheckable(true);
    if (settings->value("send_local", false) == true) {
        action_backup->setChecked(true);
    }
    action_exit = new QAction("Exit", context_menu);

    context_menu->addAction(action_config);
    context_menu->addAction(action_send);
    context_menu->addAction(action_backup);
    context_menu->addSeparator();
    context_menu->addAction(action_exit);

    icon = QIcon("1sss-32.png");
    setIcon(icon);
    setContextMenu(context_menu);

    if (firstRun) {
        config_window->setVisible(true);
    }

    connect(action_config, SIGNAL(triggered()), this, SLOT(slotConfig()));
    connect(action_exit, SIGNAL(triggered()), this, SLOT(slotExit()));
}

void TrayIcon::slotConfig()
{
    config_window->setVisible(true);
}

void TrayIcon::slotExit()
{
    QApplication::quit();
}
