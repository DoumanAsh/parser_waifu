#pragma once
#include <QClipboard>

#include <QMainWindow>

#include "about.hpp"
#include "parser.hpp"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

private slots:
    void on_actionAbout_triggered();
    void clipboard_change();

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QClipboard *clipboard;

    //Child widgets
    About *about;

    //Parsers
    parser::Mecab mecab;
};
