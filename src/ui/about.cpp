#include "about.hpp"
#include "ui_about.h"

About::About(QWidget *parent) : QDialog(parent), ui(new Ui::About) {
    ui->setupUi(this);
    ui->label_Title->setText("Parser Waifu v" TW_VERSION);
    ui->label_Desc->setText("Simple japanese parser.");
}

About::~About() {
    delete ui;
}
