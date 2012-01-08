#!/usr/bin/env python

import os
import sys
import signal
try:
    import ConfigParser as configparser
except ImportError: # Python 3
    import configparser

from PySide import QtCore, QtGui, QtNetwork

def sigint_cb(*args):
    os._exit(0)
    
class RegionGrabber(QtGui.QWidget):
    def __init__(self):
        QtGui.QWidget.__init__(self, None, QtCore.Qt.X11BypassWindowManagerHint \
                                   | QtCore.Qt.WindowStaysOnTopHint \
                                   | QtCore.Qt.FramelessWindowHint \
                                   | QtCore.Qt.Tool)
        self.desktop = QtGui.QPixmap.grabWindow(app.desktop().winId())
        self.resize(self.desktop.size())
        self.move(0, 0)
        self.setCursor(QtCore.Qt.CrossCursor)
        
    def trigger(self):
        global trigger_listen
        print "triggered"
        trigger_listen.readyRead.connect(self.trigger)
        self.setVisible(True)
        self.grabMouse()
        self.grabKeyboard()
    
    def keyPressEvent(self, e):
        if e.key() == QtCore.Qt.Key_Escape:
            print "escaped"
            self.setVisible(False)
            self.releaseKeyboard()
            self.releaseMouse()
            
    def paintEvent(self, e):
        painter = QtGui.QPainter(self)
        pal = QtGui.QPalette(QtGui.QToolTip.palette())
        font = QtGui.QToolTop.font()
        handleColor = pal.color(QtGui.QPalette.Active, QtGui.QPalette.Highlight)
        handleColor.setAlpha(160)
        overlayColor = QtGui.QColor(0, 0, 0, 160)
        textColor = pal.color(QtGui.QPalette.Active, QtGui.QPalette.Text)
        textBackgroundColor = None

app = QtGui.QApplication(sys.argv)

stmenu = QtGui.QMenu('1sss')
action_auth = stmenu.addAction("Authenticate to Imgur")
action_send = QtGui.QAction("Send to Imgur", stmenu)
action_send.setCheckable(True)
action_send.setChecked(True)
stmenu.addAction(action_send)
action_backup = QtGui.QAction("Save to ~/1sss", stmenu)
action_backup.setCheckable(True)
action_backup.setChecked(True)
stmenu.addAction(action_backup)
stmenu.addSeparator()
action_exit = stmenu.addAction("Exit")
action_exit.triggered.connect(sigint_cb)
sticon = QtGui.QIcon('1sss-32.png')
systray = QtGui.QSystemTrayIcon(sticon)
systray.setContextMenu(stmenu)
systray.setVisible(True)

trigger_listen = QtNetwork.QUdpSocket()
trigger_listen.bind(QtNetwork.QHostAddress("127.0.0.1"), 63949)
region_grabber = RegionGrabber()
trigger_listen.readyRead.connect(region_grabber.trigger)

signal.signal(signal.SIGINT, sigint_cb)
app.exec_()