#ifndef REGION_GRABBER_H
#define REGION_GRABBER_H

#include <QtGui/QWidget>

class RegionGrabber : public QWidget
{
    Q_OBJECT

public:
    RegionGrabber(QObject * parent);
    ~RegionGrabber();

public slots:
    void trigger();

private:
    QObject * tray_parent;
};

#endif // REGION_GRABBER_H
