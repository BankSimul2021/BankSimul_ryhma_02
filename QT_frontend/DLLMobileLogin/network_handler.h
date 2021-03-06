#ifndef NETWORK_HANDLER_H
#define NETWORK_HANDLER_H

#include <QJsonDocument>
#include <QNetworkAccessManager>
#include <QObject>
#include <QtNetwork>

#include "ids_t.h"

class network_handler : public QObject {
    Q_OBJECT
public:
    explicit network_handler(QObject *parent = nullptr);
    ~network_handler();
    void request_token();
    void try_login(QString atm_token);
    void request_mobile_token(int card_id);
    void request_new_mobile_token(int card_id);
    void cancel_login_request(QString atm_token);

private:
    QNetworkReply *get_reply(QObject *sender);
    QJsonObject get_json_obj(QNetworkReply *reply);
    QNetworkAccessManager *p_manager;
    QString base_url = "http://astru.ddns.net:8080";

signals:
    void got_token(QString token);
    void logged_in(ids_t ids, int64_t card_num);
    void cancel_login();
    void got_mobile_token(QString mobile_token);

private slots:
    void handle_token_response();
};

#endif  // NETWORK_HANDLER_H
