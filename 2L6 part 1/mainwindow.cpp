#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QFileDialog>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QTextStream>
#include <QMessageBox>

struct Event {
    QString name;
    QString desc;
    QString date;
    QString price;
    QString format;

    QJsonObject toJson() const {
        QJsonObject obj;
        obj["name"] = name;
        obj["desc"] = desc;
        obj["date"] = date;
        obj["format"] = format;

        bool ok;
        double p = price.toDouble(&ok);
        if (ok && p >= 0) {
            obj["price"] = p;
        } else {
            obj["price"] = price;
        }
        return obj;
    }
};

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_btnLoadTxt_clicked() {
    QString path = QFileDialog::getOpenFileName(this, "Открыть TXT", "", "Text Files (*.txt);;All Files (*)");
    if (path.isEmpty()) return;

    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл");
        return;
    }

    QTextStream in(&file);
    in.setEncoding(QStringConverter::Utf8);
    QString content = in.readAll().trimmed();
    file.close();

    QStringList p;
    if (content.contains('/')) {
        p = content.split('/');
    } else {
        p = content.split('\n');
    }

    if (p.size() >= 1) ui->editName->setText(p[0].trimmed());
    if (p.size() >= 2) ui->editDesc->setText(p[1].trimmed());
    if (p.size() >= 3) ui->editDate->setText(p[2].trimmed());
    if (p.size() >= 4) ui->editPrice->setText(p[3].trimmed());
    if (p.size() >= 5) ui->editFormat->setText(p[4].trimmed());
}

void MainWindow::on_btnOk_clicked() {
    Event ev;
    ev.name = ui->editName->text().trimmed();
    ev.desc = ui->editDesc->text().trimmed();
    ev.date = ui->editDate->text().trimmed();
    ev.price = ui->editPrice->text().trimmed();
    ev.format = ui->editFormat->text().trimmed();

    QFile file("events.json");
    QJsonArray array;

    if (file.exists()) {
        if (file.open(QIODevice::ReadOnly)) {
            array = QJsonDocument::fromJson(file.readAll()).array();
            file.close();
        }
    }

    array.append(ev.toJson());

    if (file.open(QIODevice::WriteOnly)) {
        file.write(QJsonDocument(array).toJson(QJsonDocument::Indented));
        file.close();
        QMessageBox::information(this, "Успех", "Объект успешно добавлен в events.json");

        ui->editName->clear();
        ui->editDesc->clear();
        ui->editDate->clear();
        ui->editPrice->clear();
        ui->editFormat->clear();
    } else {
        QMessageBox::critical(this, "Ошибка", "Не удалось записать в файл");
    }
}
