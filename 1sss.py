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
    
def getTrigger():
    d, a, b = trigger_listen.readDatagram(trigger_listen.pendingDatagramSize())
    if d == 'shift':
        print 'Got shift trigger'
    elif d == 'ctrl':
        print 'Got ctrl trigger'
    else:
        print 'Got print trigger'

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
trigger_listen.readyRead.connect(getTrigger)

signal.signal(signal.SIGINT, sigint_cb)
app.exec_()