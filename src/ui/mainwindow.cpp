#include <QGuiApplication>
#include <QCloseEvent>
#include <QMimeData>

#include "../app/config.hpp"
#include <utils.hpp>

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
            this->ui->original_text->setText(text);
            QString mecab_text(this->mecab.parse(std_string).c_str());
            this->ui->mecab_text->document()->setHtml(mecab_text);
        }
    }
}

void MainWindow::restoreUi() {
    this->ui->setupUi(this);
    this->restoreGeometry(this->settings.value("ui/geometry").toByteArray());
    this->restoreState(this->settings.value("ui/windowState").toByteArray());
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    settings(app::config::get_path(), QSettings::IniFormat),
    clipboard(QGuiApplication::clipboard()),
    about(new About(this))
{
    this->restoreUi();

    //TODO: We should be able to allow user to load it.
    this->settings.setValue("mecab/dictionary", QString::fromStdString(this->mecab.dict_path()));
    this->ui->mecab_text->document()->setDefaultStyleSheet("span { background: #D3D3D3; }");
    this->clipboard_change();

    connect(this->clipboard, SIGNAL(dataChanged()), this, SLOT(clipboard_change()));
}

void MainWindow::closeEvent(QCloseEvent* event) {
    this->settings.setValue("ui/geometry", this->saveGeometry());
    this->settings.setValue("ui/windowState", this->saveState());

    event->accept();
}

MainWindow::~MainWindow() {
    delete ui;
}
