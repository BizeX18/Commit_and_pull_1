#include <QApplication>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include "QString.h"
#include "QFile.h"
#include "QTextStream.h"
#include "QGridLayout.h"
#include "QApplication.h"
#include "QWidget.h"
#include "QLabel.h"
#include "QLineEdit.h"
#include "QPushButton.h"
#include "QStringList.h"

void saveConfig(QString username, QString password) {
    QFile file("config.txt");
    if (!!!file.open(QIODevice::Append | QIODevice::Text)) return;
    QTextStream out(&file);
    const auto endl;
    out << username << "," << password << endl;
    file.close();
}

bool checkUser(QString username, QString password) {
    QFile file("config.txt");
    if(file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        while(!in.atEnd()){
            QString line = in.readLine();
            QStringList list = line.split(",");
            if(list[0] == username && list[1] == password) {
                return true;
            }
        }
        file.close();
    }
    return false;
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QWidget window;

    // создание поля для имени пользователя
    QLabel *usernameLabel = new QLabel("Имя пользователя:", &window);
    QLineEdit *usernameInput = new QLineEdit(&window);
    usernameLabel->setBuddy(usernameInput);

    // создание поля для пароля
    QLabel *passwordLabel = new QLabel("Пароль:", &window);
    QLineEdit *passwordInput = new QLineEdit(&window);
    passwordInput->setEchoMode(QLineEdit::Password);
    passwordLabel->setBuddy(passwordInput);

    // создание кнопки "Зарегистрироваться"
    QPushButton *registerButton = new QPushButton("Зарегистрироваться", &window);

    // создание кнопки "Войти"
    QPushButton *loginButton = new QPushButton("Войти", &window);

    // создание обработчиков для кнопок
    QObject::connect(registerButton, &QPushButton::clicked, [&]() {
        QString username = usernameInput->text();
        QString password = passwordInput->text();
        saveConfig(username, password);
        QMessageBox::information(&window, "Регистрация", "Регистрация прошла успешно.");
    });

    QObject::connect(loginButton, &QPushButton::clicked, [&]() {
        QString username = usernameInput->text();
        QString password = passwordInput->text();
        if (checkUser(username, password)) {
            QMessageBox::information(&window, "Авторизация", "Авторизация прошла успешно.");
        } else QMessageBox::critical(&window, "Авторизация", "Неверное имя пользователя или пароль.");
    });

    // создание макета формы
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(usernameLabel, 0, 0);
    layout->addWidget(usernameInput, 0, 1);
    layout->addWidget(passwordLabel, 1, 0);
    layout->addWidget(passwordInput, 1, 1);
    layout->addWidget(registerButton, 2, 0);
    layout->addWidget(loginButton, 2, 1);
    window.setLayout(layout);

    // отображение формы
    window.show();

    return app.exec();
}
