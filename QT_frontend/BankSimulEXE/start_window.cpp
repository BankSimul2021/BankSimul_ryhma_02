#include "start_window.h"

#include "ui_start_window.h"

start_window::start_window(QWidget *parent) : QMainWindow(parent), ui(new Ui::start_window) {
    ui->setupUi(this);
    p_pincode = new DLLPincode;
    p_main_window = new Main_window;
    p_rest = new dll_rest_api;

    p_pincode->Main(false);
    p_main_window->set_ids(1);
    p_main_window->show();

    connect(p_rest, &dll_rest_api::logged_in, this, &start_window::logged_in);
    connect(p_rest, &dll_rest_api::status_ready, this, &start_window::get_status);
    connect(p_main_window, &Main_window::logout, this, &start_window::logout);

    connect(p_pincode, SIGNAL(send_pin(QByteArray)), this, SLOT(pin_received(QByteArray)));
    connect(p_rest, SIGNAL(wrong_pin(int)), p_pincode, SLOT(Wrong_PIN(int)));
    connect(p_rest, SIGNAL(card_locked()), p_pincode, SLOT(Locked_card()));
    connect(p_rest, SIGNAL(logged_in(ids_t)), p_pincode, SLOT(Logged_in()));
}

start_window::~start_window() {
    delete ui;

    delete p_pincode;
    p_pincode = nullptr;

    delete p_main_window;
    p_main_window = nullptr;

    delete p_rest;
    p_rest = nullptr;
}

void start_window::logged_in(ids_t ids) {
    p_main_window->set_ids(ids);
    p_main_window->show();
}

void start_window::pin_received(QByteArray hash) {
    long long card_num = 21488175058;
    p_rest->login(hash, card_num);
}

void start_window::card_inserted() {  // Showing the DLLPincode ui when card is inserted
    this->close();
    p_rest->get_card_status(21488175058);
}

void start_window::get_status(bool locked) {
    p_pincode->Main(locked);
    p_main_window->show();
}

void start_window::logout() {
    p_main_window->close();
    delete p_main_window;
    p_main_window = new Main_window;
    delete p_rest;
    p_rest = new dll_rest_api;
    connect(p_main_window, &Main_window::logout, this, &start_window::logout);
    this->show();

    p_main_window->set_ids(1);
    p_main_window->show();
}
