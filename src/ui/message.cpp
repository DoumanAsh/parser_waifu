#include "message.hpp"

using namespace ui::message;

Pop& Pop::title(const std::string& title) {
    inner.setWindowTitle(QString::fromStdString(title));
    return *this;
}

Pop& Pop::title(const QString& title) {
    inner.setWindowTitle(title);
    return *this;
}

Pop& Pop::text(const std::string& text) {
    inner.setText(QString::fromStdString(text));
    return *this;
}

Pop& Pop::text(const QString& text) {
    inner.setText(text);
    return *this;
}

Pop& Pop::details(const std::string& text) {
    inner.setInformativeText(QString::fromStdString(text));
    return *this;
}

Pop& Pop::details(const QString& text) {
    inner.setInformativeText(text);
    return *this;
}

Pop& Pop::type(Pop::Type type) {
    inner.setIcon(static_cast<QMessageBox::Icon>(type));
    return *this;
}

int Pop::run() {
    return inner.exec();
}
