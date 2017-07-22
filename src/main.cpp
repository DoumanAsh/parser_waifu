#include <QApplication>

#include "ui/message.hpp"
#include "ui/mainwindow.hpp"
#include "app/config.hpp"

int main(int argc, char *argv[]) {
    QApplication application(argc, argv);

    app::Config config(application.applicationDirPath().toStdString());
    MainWindow main_window;
    main_window.show();

    return application.exec();
}
