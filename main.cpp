#include <QtGui/QApplication>
#include "region_grabber.h"
#include "tray_icon.h"
#include "trigger_socket.h"

int main(int argc, char ** argv)
{
    QApplication a(argc, argv);

    TrayIcon * tray_icon = new TrayIcon();
    tray_icon->setVisible(true);

    a.setQuitOnLastWindowClosed(false);
    return a.exec();
}
