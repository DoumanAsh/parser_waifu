#include <QGuiApplication>
#include <QMimeData>

#include "utils.hpp"
#include "parser.hpp"

#include "mainwindow.hpp"
#include "ui_mainwindow.h"

void MainWindow::on_actionAbout_triggered() {
    this->about->activateWindow();
    this->about->show();
}

void MainWindow::clipboard_change() {
    auto mime = this->clipboard->mimeData();

    if (mime->hasText()) {
        auto text = mime->text();

        auto std_string = text.toStdString();
        if (utils::is_jp(std_string)) {
            parser::Mecab mecab;

            this->ui->original_text->setText(text);
            QString mecab_text(mecab.parse(std_string).c_str());
            this->ui->mecab_text->setText(mecab_text);
        }
    }
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    clipboard(QGuiApplication::clipboard()),
    about(new About(this))
{
    ui->setupUi(this);

    connect(this->clipboard, SIGNAL(dataChanged()), this, SLOT(clipboard_change()));
}

MainWindow::~MainWindow() {
    delete ui;
}
