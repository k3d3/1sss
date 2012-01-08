#include "region_grabber.h"

RegionGrabber::RegionGrabber(QObject * parent)
    : QWidget(0, Qt::X11BypassWindowManagerHint | Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint | Qt::Tool)
{
    this->tray_parent = parent;
}

RegionGrabber::~RegionGrabber()
{

}

void RegionGrabber::trigger() {

}
