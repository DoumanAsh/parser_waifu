#pragma once
#include <QClipboard>
#include <QSettings>
#include <QTimer>

#include <QMainWindow>

#include "about.hpp"
#include "parser/parser.hpp"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

private slots:
    void on_actionAbout_triggered();
    void process_text(QString text);
    void clipboard_change();
    void closeEvent(QCloseEvent* event) override;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    /**
     * Restores UI state from settings.
     */
    void restoreUi();

private:
    Ui::MainWindow *ui;

    QClipboard *clipboard;

    QSettings settings;

    //Timers
    QTimer *parser_timer;

    //Child widgets
    About *about;

    //Parsers
    parser::Mecab mecab;
};
