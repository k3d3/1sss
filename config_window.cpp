#include "config_window.h"

#include <QDebug>

ConfigWindow::ConfigWindow(QObject * parent, QSettings * settings) :
    QFrame(0)
{
    tray_parent = parent;
    tray_settings = settings;

    access_manager = new QNetworkAccessManager();
    cookie_jar = new QNetworkCookieJar();
    access_manager->setCookieJar(cookie_jar);

    QStringList list_items;
    list_items << "1sss Settings" << "Imgur Authentication" << "Minus Authentication" << "Puush Authentication";
    list_widget = new QListWidget();
    list_widget->addItems(list_items);
    list_widget->setCurrentRow(0);
    list_widget->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
    list_widget->setMaximumWidth(160);

    /* SETTINGS WINDOW */
    sss_config = new QGroupBox("1sss", this);
    sss_config->setVisible(true);

    QVBoxLayout * sss_vbox = new QVBoxLayout();
    sss_status = new QLabel("No services are currently configured!", sss_config);
    sss_vbox->addWidget(sss_status);
    sss_vbox->addSpacing(20);

    QLabel * sss_service_label = new QLabel("Image Service");
    sss_service = new QComboBox();
    sss_service->addItem("None");
    if (tray_settings->value("imgur_auth", false) == true) {
        sss_service->insertItem(1, "Imgur");
    }
    if (tray_settings->value("minus_auth", false) == true) {
        sss_service->insertItem(1, "Minus");
    }
    if (tray_settings->value("imgur_auth", false) == true) {
        sss_service->insertItem(1, "Puush");
    }

    QLabel * sss_localdir_label = new QLabel("Local Save Directory");
    sss_localdir = new QLineEdit();
    sss_localdir->setText(settings->value("local_dir", "~/1sss").toString());

    QGridLayout * sss_grid = new QGridLayout();
    sss_grid->addWidget(sss_service_label, 0, 0, 1, 1);
    sss_grid->addWidget(sss_service, 0, 1, 1, 1);
    sss_grid->addWidget(sss_localdir_label, 1, 0, 1, 1);
    sss_grid->addWidget(sss_localdir, 1, 1, 1, 1);
    sss_grid->setColumnStretch(0, 0);
    sss_grid->setColumnStretch(1, 1);
    sss_vbox->addLayout(sss_grid);
    sss_vbox->addStretch();
    sss_config->setLayout(sss_vbox);
    /* SETTINGS WINDOW */

    /* IMGUR WINDOW */
    imgur_config = new QGroupBox("Imgur", this);
    imgur_config->setVisible(false);

    QVBoxLayout * imgur_vbox = new QVBoxLayout();
    QHBoxLayout * imgur_hbox = new QHBoxLayout();

    QVBoxLayout * imgur_username_vbox = new QVBoxLayout();
    QLabel * imgur_username_label = new QLabel("Imgur Username");
    imgur_username = new QLineEdit(imgur_config);
    imgur_username_vbox->addWidget(imgur_username_label);
    imgur_username_vbox->addWidget(imgur_username);
    imgur_hbox->addLayout(imgur_username_vbox);

    QVBoxLayout * imgur_password_vbox = new QVBoxLayout();
    QLabel * imgur_password_label = new QLabel("Imgur Password");
    imgur_password = new QLineEdit(imgur_config);
    imgur_password->setEchoMode(QLineEdit::Password);
    imgur_password_vbox->addWidget(imgur_password_label);
    imgur_password_vbox->addWidget(imgur_password);
    imgur_hbox->addLayout(imgur_password_vbox);

    imgur_auth = new QPushButton("Authenticate", imgur_config);
    imgur_status = new QLabel("Imgur is not authenticated", imgur_config);

    imgur_vbox->addLayout(imgur_hbox);
    imgur_vbox->addWidget(imgur_auth);
    imgur_vbox->addWidget(imgur_status);
    imgur_vbox->addStretch();

    imgur_config->setLayout(imgur_vbox);
    /* IMGUR WINDOW */

    /* MINUS WINDOW */
    minus_config = new QGroupBox("Minus", this);
    minus_config->setVisible(false);

    QVBoxLayout * minus_vbox = new QVBoxLayout();
    QHBoxLayout * minus_hbox = new QHBoxLayout();

    QVBoxLayout * minus_username_vbox = new QVBoxLayout();
    QLabel * minus_username_label = new QLabel("Minus Username");
    minus_username = new QLineEdit(minus_config);
    minus_username_vbox->addWidget(minus_username_label);
    minus_username_vbox->addWidget(minus_username);
    minus_hbox->addLayout(minus_username_vbox);

    QVBoxLayout * minus_password_vbox = new QVBoxLayout();
    QLabel * minus_password_label = new QLabel("Minus Password");
    minus_password = new QLineEdit(minus_config);
    minus_password->setEchoMode(QLineEdit::Password);
    minus_password_vbox->addWidget(minus_password_label);
    minus_password_vbox->addWidget(minus_password);
    minus_hbox->addLayout(minus_password_vbox);

    minus_auth = new QPushButton("Authenticate", minus_config);
    minus_status = new QLabel("Minus is not authenticated", minus_config);

    minus_vbox->addLayout(minus_hbox);
    minus_vbox->addWidget(minus_auth);
    minus_vbox->addWidget(minus_status);
    minus_vbox->addStretch();

    minus_config->setLayout(minus_vbox);
    /* MINUS WINDOW */

    /* PUUSH WINDOW */
    puush_config = new QGroupBox("Puush", this);
    puush_config->setVisible(false);

    QVBoxLayout * puush_vbox = new QVBoxLayout();
    QHBoxLayout * puush_hbox = new QHBoxLayout();

    QVBoxLayout * puush_username_vbox = new QVBoxLayout();
    QLabel * puush_username_label = new QLabel("Puush Username");
    puush_username = new QLineEdit(puush_config);
    puush_username_vbox->addWidget(puush_username_label);
    puush_username_vbox->addWidget(puush_username);
    puush_hbox->addLayout(puush_username_vbox);

    QVBoxLayout * puush_password_vbox = new QVBoxLayout();
    QLabel * puush_password_label = new QLabel("Puush Password");
    puush_password = new QLineEdit(puush_config);
    puush_password->setEchoMode(QLineEdit::Password);
    puush_password_vbox->addWidget(puush_password_label);
    puush_password_vbox->addWidget(puush_password);
    puush_hbox->addLayout(puush_password_vbox);

    puush_auth = new QPushButton("Authenticate", puush_config);
    puush_status = new QLabel("Puush is not authenticated", minus_config);

    puush_vbox->addLayout(puush_hbox);
    puush_vbox->addWidget(puush_auth);
    puush_vbox->addWidget(puush_status);
    puush_vbox->addStretch();

    puush_config->setLayout(puush_vbox);
    /* PUUSH WINDOW */

    QHBoxLayout * top_layout = new QHBoxLayout();
    top_layout->addWidget(list_widget);
    top_layout->addWidget(sss_config);
    top_layout->addWidget(imgur_config);
    top_layout->addWidget(minus_config);
    top_layout->addWidget(puush_config);

    setLayout(top_layout);
    resize(640,480);
    connect(imgur_auth, SIGNAL(clicked()), this, SLOT(imgurAuthenticate()));
    connect(minus_auth, SIGNAL(clicked()), this, SLOT(minusAuthenticate()));
    connect(puush_auth, SIGNAL(clicked()), this, SLOT(puushAuthenticate()));
    connect(list_widget, SIGNAL(currentRowChanged(int)), this, SLOT(newCurrentRow(int)));
}

void ConfigWindow::newCurrentRow(int currentRow)
{
    sss_config->setVisible(currentRow == 0);
    imgur_config->setVisible(currentRow == 1);
    minus_config->setVisible(currentRow == 2);
    puush_config->setVisible(currentRow == 3);
}

void ConfigWindow::imgurAuthenticate() {
    /*qDebug() << imgur_username->text() << imgur_password->text();
    oauth = new QOAuth::Interface;
    oauth->setConsumerKey("a");
    oauth->setConsumerSecret("b");
    oauth->setRequestTimeout(10000); // 10 seconds

    QOAuth::ParamMap reply = oauth->requestToken("http://api.imgur.com/oauth/request_token", QOAuth::POST);
    qDebug() << oauth->error();
    if (oauth->error() != QOAuth::NoError) {
        return;
    }
    QByteArray token = reply.value(QOAuth::tokenParameterName());
    QByteArray tokenSecret = reply.value(QOAuth::tokenSecretParameterName());
    qDebug() << token << tokenSecret;

    QOAuth::ParamMap args;// = new QOAuth::ParamMap;
    args.insert(QByteArray("username"),imgur_username->text().toUtf8());
    args.insert(QByteArray("password"),imgur_password->text().toUtf8());

    reply = oauth->accessToken("http://api.imgur.com/oauth/authorize", QOAuth::POST, token, tokenSecret, QOAuth::HMAC_SHA1, args);
    qDebug() << oauth->error();
    if (oauth->error() != QOAuth::NoError) {
        return;
    }*/

    if (imgur_auth->text() == "Authenticate") {
        const QByteArray post_data = "username="+QUrl::toPercentEncoding(imgur_username->text())+"&password="+QUrl::toPercentEncoding(imgur_password->text())+"&remember=remember&submit=";
        imgur_request = new QNetworkRequest(QUrl("https://imgur.com/signin"));
        imgur_reply = access_manager->post(*imgur_request, post_data);
        connect(imgur_reply, SIGNAL(finished()), this, SLOT(imgurAuthenticate2()));
    }
    else if (imgur_auth->text() == "Reauthenticate") {
        imgur_auth->setText("Authenticate");
        imgur_status->setText("Imgur is not authenticated");
        imgur_username->setDisabled(false);
        imgur_password->setDisabled(false);
        tray_settings->setValue("imgur_cookie", "");
        tray_settings->setValue("imgur_auth", false);
    }
}

void ConfigWindow::imgurAuthenticate2() {
    int http_code = imgur_reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    qDebug() << http_code;
    if (http_code == 200) {
        imgur_status->setText("Your credentials were incorrect");
        return;
    }
    else if (http_code == 302) {
        QList<QNetworkCookie> cookies = cookie_jar->cookiesForUrl(QUrl("https://imgur.com"));
        // It appears that IMGURCOOKIE is always first, let's hope it stays that way
        tray_settings->setValue("imgur_cookie", cookies.first().value());
        tray_settings->setValue("imgur_auth", true);
        imgur_status->setText("Imgur is authenticated");
        imgur_auth->setText("Reauthenticate");
        imgur_username->setDisabled(true);
        imgur_username->setText("");
        imgur_password->setDisabled(true);
        imgur_password->setText("");
    }
}

void ConfigWindow::minusAuthenticate() {
    qDebug() << "asdf";
}

void ConfigWindow::puushAuthenticate() {
    qDebug() << "asdf";
}

void ConfigWindow::closeEvent(QCloseEvent *event) {
    Q_UNUSED(event);
    qDebug() << "asdf";
}
