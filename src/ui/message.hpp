#pragma once

#include <string>

#include <QString>
#include <QMessageBox>

namespace ui {
    namespace message {
        class Pop {
            public:
                enum class Type {
                    None = QMessageBox::NoIcon,
                    Question = QMessageBox::Question,
                    Information = QMessageBox::Information,
                    Warning = QMessageBox::Warning,
                    Error = QMessageBox::Critical,
                };

            public:
                ///Sets pop-up window's title
                Pop& title(const std::string& title);
                Pop& title(const QString& title);

                ///Sets pop-up main text
                Pop& text(const std::string& text);
                Pop& text(const QString& text);

                ///Sets pop-up details
                Pop& details(const std::string& text);
                Pop& details(const QString& text);

                ///Sets type of pop-up
                Pop& type(Type type);

                ///Executes pop-up
                int run();
            private:
                QMessageBox inner;
        };
    }
}
