#include <QCoreApplication>
#include <QDir>

#include "config.hpp"

using namespace app;

QString config::get_path() {
    const QDir dir(QCoreApplication::applicationDirPath());
    return dir.filePath("pw.ini");
}
