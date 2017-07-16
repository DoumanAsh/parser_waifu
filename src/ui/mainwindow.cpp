#include <QGuiApplication>
#include <QMimeData>

#include "utils.hpp"

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

        if (utils::is_jp(text.toStdWString())) {
            this->ui->original_text->setText(text);
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
