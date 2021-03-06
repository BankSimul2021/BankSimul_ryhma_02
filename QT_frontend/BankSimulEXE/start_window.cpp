#include "start_window.h"

#include <dllserialport.h>

#include "ui_start_window.h"

start_window::start_window(QWidget *parent) : QMainWindow(parent), ui(new Ui::start_window) {
    ui->setupUi(this);
    p_pincode = new DLLPincode;
    p_main_window = new Main_window;
    p_rest = new dll_rest_api;
    p_mobile = new dll_mobile_login;

    connect(p_mobile, &dll_mobile_login::logged_in, this,
            qOverload<ids_t, int64_t>(&start_window::logged_in));
    connect(p_rest, &dll_rest_api::logged_in, this, qOverload<ids_t>(&start_window::logged_in));
    connect(p_rest, &dll_rest_api::status_ready, this, &start_window::get_status);
    connect(p_main_window, &Main_window::logout, this, &start_window::logout);

    connect(p_pincode, SIGNAL(send_pin(QByteArray)), this, SLOT(pin_received(QByteArray)));
    connect(p_rest, SIGNAL(wrong_pin(int)), p_pincode, SLOT(Wrong_PIN(int)));
    connect(p_rest, SIGNAL(card_locked()), p_pincode, SLOT(Locked_card()));
    connect(p_rest, SIGNAL(logged_in(ids_t)), p_pincode, SLOT(Logged_in()));
    connect(p_pincode, SIGNAL(locked()), this, SLOT(logout()));

    p_serial_port = new DLLSerialPort;
    connect(p_serial_port, &DLLSerialPort::card_read, this, &start_window::card_inserted);
    p_serial_port->read_card();
}

start_window::~start_window() {
    delete ui;

    delete p_pincode;
    p_pincode = nullptr;

    delete p_main_window;
    p_main_window = nullptr;
    delete p_serial_port;
    delete p_rest;
    delete p_mobile;
}

void start_window::logged_in(ids_t ids) {
    p_main_window->set_card_num(card_num);
    p_main_window->set_ids(ids);
    p_main_window->show_ui();
}

void start_window::pin_received(QByteArray hash) { p_rest->login(hash, card_num); }

void start_window::card_inserted(QString num) {  // Showing the DLLPincode ui when card is inserted
    num.remove("\r\n-");
    num.remove("\r\n>");
    qDebug() << num.toULongLong(nullptr, 16);
    card_num = num.toLongLong(nullptr, 16);

    p_rest->get_card_status(card_num);
}

void start_window::get_status(bool locked) {
    p_pincode->Main(locked);
    this->close();
}

void start_window::logout() {
    p_main_window->close();
    delete p_main_window;
    p_main_window = new Main_window;
    connect(p_main_window, &Main_window::logout, this, &start_window::logout);
    this->show();

    p_serial_port->read_card();
}

void start_window::logged_in(ids_t ids, int64_t card_num) {
    p_main_window->set_card_num(card_num);
    p_main_window->set_ids(ids);
    p_main_window->show_ui();
    this->close();
}

void start_window::on_mobile_btn_clicked() { p_mobile->login(); }
