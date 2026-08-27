#include "registrationform.h"
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QMessageBox>
#include <QRegularExpression>
#include <QStandardPaths>
#include <QDir>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QPixmap>
#include <QTextStream>

RegistrationForm::RegistrationForm(QWidget *parent) : QWidget(parent) {
    setWindowTitle("Регистрация");
    setFixedSize(650, 420);

    existingNicknames << "admin" << "user123" << "moderator";

    setStyleSheet(
        "QWidget { background-color: #2b2b2b; color: #ffffff; font-family: 'Segoe UI', Arial; font-size: 13px; }"
        "QLineEdit { background-color: #3c3f41; border: 2px solid #555555; border-radius: 4px; padding: 4px; color: #ffffff; }"
        "QLineEdit:focus { border: 2px solid #007acc; }"
        "QCheckBox { spacing: 5px; }"
        "QCheckBox::indicator { width: 16px; height: 16px; border: 2px solid #555555; background-color: #3c3f41; border-radius: 3px; }"
        "QCheckBox::indicator:checked { background-color: #007acc; border: 2px solid #007acc; }"
        "QPushButton { background-color: #3c3f41; border: 2px solid #555555; border-radius: 12px; padding: 6px 15px; font-weight: bold; }"
        "QPushButton:hover { background-color: #4e5254; border-color: #007acc; }"
        "QPushButton:pressed { background-color: #007acc; }"
        );

    QVBoxLayout *leftLayout = new QVBoxLayout();
    lblPhotoPreview = new QLabel("Фото");
    lblPhotoPreview->setFixedSize(150, 150);
    lblPhotoPreview->setAlignment(Qt::AlignCenter);
    lblPhotoPreview->setStyleSheet("border: 3px solid #ffffff; background-color: #1e1e1e; font-size: 16px; font-weight: bold;");

    btnLoadPhoto = new QPushButton("Загрузить");
    btnLoadPhoto->setFixedWidth(120);

    leftLayout->addWidget(lblPhotoPreview, 0, Qt::AlignCenter);
    leftLayout->addWidget(btnLoadPhoto, 0, Qt::AlignCenter);
    leftLayout->addStretch();

    QGridLayout *formLayout = new QGridLayout();
    formLayout->setHorizontalSpacing(15);
    formLayout->setVerticalSpacing(10);

    leFirstName = new ClickableLineEdit();
    leLastName = new ClickableLineEdit();
    leNickname = new ClickableLineEdit();
    leIdKey = new ClickableLineEdit();
    leEmail = new ClickableLineEdit();
    lePassword = new ClickableLineEdit();
    lePassword->setEchoMode(QLineEdit::Password);

    formLayout->addWidget(new QLabel("Имя"), 0, 0);
    formLayout->addWidget(leFirstName, 0, 1);
    formLayout->addWidget(new QLabel("Фамилия"), 1, 0);
    formLayout->addWidget(leLastName, 1, 1);
    formLayout->addWidget(new QLabel("Никнейм"), 2, 0);
    formLayout->addWidget(leNickname, 2, 1);
    formLayout->addWidget(new QLabel("ID-Key"), 3, 0);
    formLayout->addWidget(leIdKey, 3, 1);

    formLayout->setRowMinimumHeight(4, 15);

    formLayout->addWidget(new QLabel("Почта"), 5, 0);
    formLayout->addWidget(leEmail, 5, 1);
    formLayout->addWidget(new QLabel("Пароль"), 6, 0);
    formLayout->addWidget(lePassword, 6, 1);

    QHBoxLayout *topLayout = new QHBoxLayout();
    topLayout->addLayout(leftLayout);
    topLayout->addSpacing(20);
    topLayout->addLayout(formLayout);

    QLabel *lblServers = new QLabel("Сервера:");
    lblServers->setStyleSheet("font-weight: bold;");

    cbEurope = new QCheckBox("Европа");
    cbAsia = new QCheckBox("Азия");
    cbAmerica = new QCheckBox("Америка");

    QHBoxLayout *serversLayout = new QHBoxLayout();
    serversLayout->addWidget(cbEurope);
    serversLayout->addWidget(cbAsia);
    serversLayout->addWidget(cbAmerica);
    serversLayout->addStretch();

    QVBoxLayout *bottomLeftLayout = new QVBoxLayout();
    bottomLeftLayout->addWidget(lblServers);
    bottomLeftLayout->addLayout(serversLayout);

    btnRegister = new QPushButton("Регистрация");
    btnRegister->setFixedSize(160, 45);
    btnRegister->setStyleSheet("QPushButton { border-radius: 18px; font-size: 14px; background-color: #3c3f41; } QPushButton:hover { background-color: #007acc; }");

    QHBoxLayout *bottomLayout = new QHBoxLayout();
    bottomLayout->addLayout(bottomLeftLayout);
    bottomLayout->addWidget(btnRegister, 0, Qt::AlignBottom | Qt::AlignRight);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(25, 25, 25, 25);
    mainLayout->addLayout(topLayout);
    mainLayout->addSpacing(20);
    mainLayout->addLayout(bottomLayout);

    connect(btnLoadPhoto, &QPushButton::clicked, this, &RegistrationForm::selectPhoto);
    connect(btnRegister, &QPushButton::clicked, this, &RegistrationForm::processRegistration);
}

void RegistrationForm::selectPhoto() {
    QString filePath = QFileDialog::getOpenFileName(this, "Выберите аватар", "", "Изображения (*.png *.jpg *.jpeg *.bmp)");
    if (!filePath.isEmpty()) {
        selectedPhotoPath = filePath;
        QPixmap pix(filePath);
        lblPhotoPreview->setPixmap(pix.scaled(lblPhotoPreview->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
}

QString RegistrationForm::encryptPassword(const QString &password) {
    const char key = 'K';
    QByteArray bytes = password.toUtf8();
    for (int i = 0; i < bytes.size(); ++i) {
        bytes[i] = bytes[i] ^ key;
    }
    return QString::fromLatin1(bytes.toBase64());
}

bool RegistrationForm::validateFields() {

    if (leFirstName->text().trimmed().isEmpty() || leLastName->text().trimmed().isEmpty() ||
        leNickname->text().trimmed().isEmpty() || leIdKey->text().trimmed().isEmpty() ||
        leEmail->text().trimmed().isEmpty() || lePassword->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Валидация", "Заполните все текстовые поля формы!");
        return false;
    }

    QRegularExpression nameRegex("^[A-Za-zА-Яа-яЁё\\-]+$");
    if (!nameRegex.match(leFirstName->text().trimmed()).hasMatch()) {
        QMessageBox::warning(this, "Ошибка Имени", "Имя должно содержать только буквы!");
        return false;
    }
    if (!nameRegex.match(leLastName->text().trimmed()).hasMatch()) {
        QMessageBox::warning(this, "Ошибка Фамилии", "Фамилия должна содержать только буквы!");
        return false;
    }

    QString currentNick = leNickname->text().trimmed();
    QString desktopPath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    QString userFolderPath = desktopPath + "/Accounts/" + currentNick;

    if (existingNicknames.contains(currentNick, Qt::CaseInsensitive) || QDir(userFolderPath).exists()) {
        QMessageBox::warning(this, "Ошибка Никнейма", "Указанный Никнейм уже занят!");
        return false;
    }

    QRegularExpression idRegex("^[A-Za-zА-Яа-яЁё]\\d{3}-\\d{2}[A-Za-zА-Яа-яЁё]-[A-Za-zА-Яа-яЁё]$");
    if (!idRegex.match(leIdKey->text().trimmed()).hasMatch()) {
        QMessageBox::warning(this, "Ошибка ID-Key", "ID-Key должен соответствовать формату: А111-11А-А");
        return false;
    }

    QRegularExpression emailRegex("^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,}$");
    if (!emailRegex.match(leEmail->text().trimmed()).hasMatch()) {
        QMessageBox::warning(this, "Ошибка Email", "Введен некорректный адрес почты!");
        return false;
    }

    if (!cbEurope->isChecked() && !cbAsia->isChecked() && !cbAmerica->isChecked()) {
        QMessageBox::warning(this, "Ошибка Сервера", "Выберите хотя бы один сервер!");
        return false;
    }

    return true;
}

void RegistrationForm::processRegistration() {
    if (!validateFields()) return;

    QString nick = leNickname->text().trimmed();
    QString desktopPath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    QString userFolderPath = desktopPath + "/Accounts/" + nick;

    QDir dir;
    if (!dir.mkpath(userFolderPath)) {
        QMessageBox::critical(this, "Ошибка системы", "Не удалось создать папку на Рабочем столе.");
        return;
    }

    QString targetPhotoPath = userFolderPath + "/avatar.png";
    if (!selectedPhotoPath.isEmpty() && QFile::exists(selectedPhotoPath)) {
        if (QFile::exists(targetPhotoPath)) QFile::remove(targetPhotoPath);
        QFile::copy(selectedPhotoPath, targetPhotoPath);
    } else {
        QPixmap defaultPix(150, 150);
        defaultPix.fill(QColor(60, 63, 65));
        defaultPix.save(targetPhotoPath, "PNG");
    }

    QStringList servers;
    if (cbEurope->isChecked()) servers << "Европа";
    if (cbAsia->isChecked()) servers << "Азия";
    if (cbAmerica->isChecked()) servers << "Америка";

    QJsonObject jsonProfile;
    jsonProfile["Имя"] = leFirstName->text().trimmed();
    jsonProfile["Фамилия"] = leLastName->text().trimmed();
    jsonProfile["Никнейм"] = nick;
    jsonProfile["ID-Key"] = leIdKey->text().trimmed();
    jsonProfile["Почта"] = leEmail->text().trimmed();
    jsonProfile["Сервера"] = servers.join(", ");

    QFile jsonFile(userFolderPath + "/profile.json");
    if (jsonFile.open(QIODevice::WriteOnly)) {
        jsonFile.write(QJsonDocument(jsonProfile).toJson(QJsonDocument::Indented));
        jsonFile.close();
    }

    QString cipherPassword = encryptPassword(lePassword->text());
    QFile txtFile(userFolderPath + "/credentials.txt");
    if (txtFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&txtFile);
        out.setEncoding(QStringConverter::Utf8);
        out << leEmail->text().trimmed() << "/" << cipherPassword;
        txtFile.close();
    }

    existingNicknames << nick;
    QMessageBox::information(this, "Успех", "Регистрация прошла успешно!\nФайлы сохранены в папку Accounts на Рабочем столе.");
}
