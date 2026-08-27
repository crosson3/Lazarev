#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QFileDialog>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QMessageBox>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <algorithm>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    QStringList headers = {"Название", "Описание", "Дата", "Стоимость", "Формат"};

    ui->tableValid->setColumnCount(5);
    ui->tableValid->setHorizontalHeaderLabels(headers);
    ui->tableValid->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableValid->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->tableBroken->setColumnCount(5);
    ui->tableBroken->setHorizontalHeaderLabels(headers);
    ui->tableBroken->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableBroken->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_btnLoad_clicked() {
    QString path = QFileDialog::getOpenFileName(this, "Открыть JSON файл", "", "JSON Files (*.json);;All Files (*)");
    if (path.isEmpty()) return;

    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл");
        return;
    }

    QByteArray rawData = file.readAll();
    file.close();

    QJsonParseError parseError;
    QJsonDocument doc = QJsonDocument::fromJson(rawData, &parseError);

    if (!doc.isArray()) {
        QMessageBox::critical(this, "Ошибка JSON", "Файл поврежден или не содержит массив объектов:\n" + parseError.errorString());
        return;
    }

    const QJsonArray all = doc.array();
    std::vector<Event> validList;
    std::vector<Event> brokenList;

    for (const QJsonValue &val : all) {
        if (!val.isObject()) continue;

        Event ev(val.toObject());
        if (ev.isValid()) {
            validList.push_back(ev);
        } else {
            brokenList.push_back(ev);
        }
    }

    // Сортировка по полю "название" в обратном алфавитном порядке (Я -> А)
    std::sort(validList.begin(), validList.end(), [](const Event &a, const Event &b) {
        return a.name.localeAwareCompare(b.name) > 0;
    });

    fillTables(validList, brokenList);

    // Сохранение валидных в events_valid.json
    QFile validFile("events_valid.json");
    if (validFile.open(QIODevice::WriteOnly)) {
        QJsonArray validArr;
        for (const Event &e : validList) {
            validArr.append(e.toJson());
        }
        validFile.write(QJsonDocument(validArr).toJson(QJsonDocument::Indented));
        validFile.close();
    }

    // Сохранение битых в events_broken.json
    QFile brokenFile("events_broken.json");
    if (brokenFile.open(QIODevice::WriteOnly)) {
        QJsonArray brokenArr;
        for (const Event &e : brokenList) {
            brokenArr.append(e.toJson());
        }
        brokenFile.write(QJsonDocument(brokenArr).toJson(QJsonDocument::Indented));
        brokenFile.close();
    }

    QMessageBox::information(this, "Готово",
                             QString("Данные успешно разделены и сохранены!\n"
                                     "Корректных: %1 (в events_valid.json)\n"
                                     "С ошибками: %2 (в events_broken.json)")
                                 .arg(validList.size()).arg(brokenList.size()));
}

void MainWindow::fillTables(const std::vector<Event> &validList, const std::vector<Event> &brokenList) {
    ui->tableValid->setRowCount(0);
    ui->tableBroken->setRowCount(0);

    for (const Event &e : validList) {
        int row = ui->tableValid->rowCount();
        ui->tableValid->insertRow(row);

        ui->tableValid->setItem(row, 0, new QTableWidgetItem(e.name));
        ui->tableValid->setItem(row, 1, new QTableWidgetItem(e.desc));
        ui->tableValid->setItem(row, 2, new QTableWidgetItem(e.date));
        ui->tableValid->setItem(row, 3, new QTableWidgetItem(e.price));
        ui->tableValid->setItem(row, 4, new QTableWidgetItem(e.format));
    }

    QColor errorColor(255, 150, 150);

    for (const Event &e : brokenList) {
        QStringList broken = e.getBrokenFields();
        int row = ui->tableBroken->rowCount();
        ui->tableBroken->insertRow(row);

        auto createItem = [&](const QString &val, const QString &key) {
            QTableWidgetItem *item = new QTableWidgetItem(val);
            if (broken.contains(key)) {
                item->setBackground(errorColor);
            }
            return item;
        };

        ui->tableBroken->setItem(row, 0, createItem(e.name,   "name"));
        ui->tableBroken->setItem(row, 1, createItem(e.desc,   "desc"));
        ui->tableBroken->setItem(row, 2, createItem(e.date,   "date"));
        ui->tableBroken->setItem(row, 3, createItem(e.price,  "price"));
        ui->tableBroken->setItem(row, 4, createItem(e.format, "format"));
    }
}
