#include <QGuiApplication>
#include <QCloseEvent>
#include <QMimeData>

#include "../app/config.hpp"

#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include "styles.hpp"

void MainWindow::on_actionAbout_triggered() {
    this->about->activateWindow();
    this->about->show();
}

void MainWindow::process_text(QString text) {
    auto std_string = text.toStdString();

    this->ui->original_text->setText(text);
    QString mecab_text(this->mecab.parse(std_string).c_str());
    this->ui->mecab_text->document()->setHtml(mecab_text);
}

void MainWindow::clipboard_change() {
    static QRegExp jp_re(u8"[\u3000-\u303F]|[\u3040-\u309F]|[\u30A0-\u30FF]|[\uFF00-\uFFEF]|[\u4E00-\u9FAF]");
    auto mime = this->clipboard->mimeData();

    if (mime->hasText()) {
        auto text = mime->text();
        if (jp_re.indexIn(text) != -1) {
            //It might be a better idea to just have worker thread
            this->parser_timer->stop();
            connect(this->parser_timer, &QTimer::timeout, this, [this, text] () {this->process_text(text);});
            //TODO: will make time configurable
            this->parser_timer->start(0);
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
    about(new About(this)),
    parser_timer(new QTimer(this))
{
    this->restoreUi();

    //TODO: We should be able to allow user to load it.
    this->settings.setValue("mecab/dictionary", QString::fromStdString(this->mecab.dict_path()));
    this->ui->mecab_text->document()->setDefaultStyleSheet(styles::MECAB_CSS);
    this->clipboard_change();

    this->parser_timer->setSingleShot(true);

    connect(this->clipboard, &QClipboard::dataChanged, this, &MainWindow::clipboard_change);
}

void MainWindow::closeEvent(QCloseEvent* event) {
    this->settings.setValue("ui/geometry", this->saveGeometry());
    this->settings.setValue("ui/windowState", this->saveState());

    event->accept();
}

MainWindow::~MainWindow() {
    delete ui;
}
