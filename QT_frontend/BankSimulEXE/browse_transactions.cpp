#include "browse_transactions.h"

#include "main_window.h"
#include "ui_browse_transactions.h"

browse_transactions::browse_transactions(QWidget *parent)
    : QDialog(parent), ui(new Ui::browse_transactions) {
    ui->setupUi(this);
    p_timer = new QTimer;
    p_rest = new dll_rest_api;
    ui->transactions_view->setSelectionMode(QAbstractItemView::NoSelection);
    ui->transactions_view->setEditTriggers(QAbstractItemView::NoEditTriggers);

    connect(p_timer, &QTimer::timeout, this, [this] {
        time -= 1;
        if (time == 0)
            on_close_btn_clicked();
        else
            ui->time->setNum(time);
    });

    connect(p_rest, qOverload<customer_info_t>(&dll_rest_api::info_ready), this,
            [this](customer_info_t info) {
                ui->user_label->setText(info.first_name + " " + info.last_name);
                ui->address_label->setText(info.address);
                ui->phone_label->setText(info.phone_num);
            });
    connect(p_rest, qOverload<account_info_t>(&dll_rest_api::info_ready), this,
            [this](account_info_t info) {
                ui->balance_label->setText(QString().setNum(info.balance));
                ui->account_num_label->setText(info.account_num);
            });
    connect(p_rest, qOverload<QVector<transaction_t>>(&dll_rest_api::info_ready), this,
            [this](QVector<transaction_t> transactions) {
                ui->transactions_view->setRowCount(transactions.size());
                ui->transactions_view->setColumnCount(3);
                ui->transactions_view->setHorizontalHeaderLabels({"Päivä", "Aika", "Määrä"});

                for (int i = 0; i < ui->transactions_view->rowCount(); i++) {
                    QTableWidgetItem *date = new QTableWidgetItem(transactions[i].date);
                    QTableWidgetItem *time = new QTableWidgetItem(transactions[i].time);
                    QTableWidgetItem *sum =
                        new QTableWidgetItem(QString().setNum(transactions[i].sum));

                    ui->transactions_view->setItem(i, 0, date);
                    ui->transactions_view->setItem(i, 1, time);
                    ui->transactions_view->setItem(i, 2, sum);
                }
            });
}
browse_transactions::~browse_transactions() {
    delete ui;
    delete p_timer;
    delete p_rest;
}

void browse_transactions::on_close_btn_clicked() {
    p_timer->stop();
    this->close();
    main_wnd->show();

    p_ids = nullptr;
    main_wnd = nullptr;
}

void browse_transactions::on_log_out_btn_clicked() {
    p_timer->stop();
    this->close();
    emit main_wnd->logout();
}

void browse_transactions::transaction_menu(ids_t *ids, Main_window *main_wnd) {
    p_ids = ids;
    this->main_wnd = main_wnd;
    time = 30;
    ui->time->setNum(time);

    p_rest->get_customer_info(p_ids->customer_id);
    p_rest->get_account_info(p_ids->account_id);
    p_rest->get_transactions(p_ids->account_id, 0);
    p_timer->start(1000);
    this->show();
}

void browse_transactions::on_forward_btn_clicked() {
    p_rest->get_transactions(p_ids->account_id, ++page);
}

void browse_transactions::on_back_btn_clicked() {
    p_rest->get_transactions(p_ids->account_id, --page);
}
