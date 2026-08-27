#include "registrywindow.h"
#include <QVBoxLayout>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QHeaderView>

RegistryWindow::RegistryWindow(QWidget* parent) : QMainWindow(parent) {
    setWindowTitle("БД Пропусков (Лаб 5)");
    resize(600, 400);

    QWidget* coreWidget = new QWidget(this);
    setCentralWidget(coreWidget);

    mainTable = new QTableWidget(0, 2, this);
    mainTable->setHorizontalHeaderLabels({"Сотрудник", "Дата рождения"});
    mainTable->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    mainTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    mainTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    btnLoad = new QPushButton("Загрузить базу данных", this);
    btnLoad->setStyleSheet("background-color: #2c3e50; color: white; padding: 10px; font-weight: bold; border-radius: 5px;");

    QVBoxLayout* vbox = new QVBoxLayout(coreWidget);
    vbox->addWidget(mainTable);
    vbox->addWidget(btnLoad);

    connect(btnLoad, &QPushButton::clicked, this, &RegistryWindow::openDataFile);
    connect(mainTable, &QTableWidget::cellDoubleClicked, this, &RegistryWindow::onRowDoubleClicked);
}

RegistryWindow::~RegistryWindow() {
    for (R* obj : recordsList) {
        delete obj;
    }
    recordsList.clear();
}

void RegistryWindow::openDataFile() {
    QString path = QFileDialog::getOpenFileName(this, "Открыть базу", "", "Text Files (*.txt)");
    if (path.isEmpty()) return;

    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Ошибка", "Файл не читается!");
        return;
    }

    for (R* obj : recordsList) {
        delete obj;
    }
    recordsList.clear();

    QTextStream in(&file);
    in.setEncoding(QStringConverter::Utf8);

    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (line.isEmpty()) continue;

        QStringList p;
        for (const QString& item : line.split(",")) {
            p.append(item.trimmed());
        }

        if (p.size() < 7) continue;

        int code = p[0].toInt();

        if (code == 1) {
            RuP* obj = new RuP();
            obj->surname = p[1];
            obj->name = p[2];
            obj->patronymic = p[3];
            obj->date = {p[4].toInt(), p[5].toInt(), p[6].toInt()};
            recordsList.push_back(obj);
        }
        else if (code == 2) {
            AmP* obj = new AmP();
            obj->name = p[1];
            obj->middleName = p[2];
            obj->surname = p[3];
            obj->date = {p[5].toInt(), p[4].toInt(), p[6].toInt()};
            recordsList.push_back(obj);
        }
    }
    file.close();
    refreshView();
}

void RegistryWindow::refreshView() {
    mainTable->setRowCount(0);
    for (size_t i = 0; i < recordsList.size(); ++i) {
        mainTable->insertRow(i);
        mainTable->setItem(i, 0, new QTableWidgetItem(recordsList[i]->getFullName()));
        mainTable->setItem(i, 1, new QTableWidgetItem(recordsList[i]->getStandardDate()));
    }
}

void RegistryWindow::onRowDoubleClicked(int row, int col) {
    if (row < 0 || row >= static_cast<int>(recordsList.size())) return;

    if (recordsList[row]->Craft(this)) {
        delete recordsList[row];
        recordsList.erase(recordsList.begin() + row);
        refreshView();
    }
}
