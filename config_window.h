#ifndef CONFIG_WINDOW_H
#define CONFIG_WINDOW_H

#include <QWidget>
#include <QGroupBox>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QComboBox>
#include <QCheckBox>
#include <QListWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSettings>
#include <QByteArray>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkCookieJar>

#include <QtOAuth>

class ConfigWindow : public QFrame
{
    Q_OBJECT
public:
    ConfigWindow(QObject * parent, QSettings * settings);

signals:

public slots:
    void closeEvent(QCloseEvent *event);
    void newCurrentRow(int currentRow);

    void imgurAuthenticate();
    void imgurAuthenticate2();

    void minusAuthenticate();
    void puushAuthenticate();

    //void imgurAuthenticated();
    //void minusAuthenticated();
    //void puushAuthenticated();

private:
    QSettings * tray_settings;

    QObject * tray_parent;
    QListWidget * list_widget;

    QGroupBox * sss_config;
    QLabel * sss_status;
    QComboBox * sss_service;
    QLineEdit * sss_localdir;

    QGroupBox * imgur_config;
    QLabel * imgur_status;
    QLineEdit * imgur_username;
    QLineEdit * imgur_password;
    QPushButton * imgur_auth;

    QGroupBox * minus_config;
    QLabel * minus_status;
    QLineEdit * minus_username;
    QLineEdit * minus_password;
    QPushButton * minus_auth;

    QGroupBox * puush_config;
    QLabel * puush_status;
    QLineEdit * puush_username;
    QLineEdit * puush_password;
    QPushButton * puush_auth;

    QOAuth::Interface * oauth;

    QNetworkAccessManager * access_manager;
    QNetworkCookieJar * cookie_jar;

    QNetworkRequest * imgur_request;
    QNetworkRequest * minus_request;
    QNetworkRequest * puush_request;

    QNetworkReply * imgur_reply;
    QNetworkReply * minus_reply;
    QNetworkReply * puush_reply;
};

#endif // CONFIG_WINDOW_H
