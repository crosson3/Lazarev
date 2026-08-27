#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QStringList>
#include <QJsonObject>
#include <QJsonValue>
#include <QDate>
#include <vector>

struct Event {
    QString name;
    QString desc;
    QString date;
    QString price;
    QString format;

    Event() = default;

    Event(const QJsonObject &obj) {
        auto getStr = [&](const QString &key) -> QString {
            QJsonValue v = obj[key];
            if (v.isString()) return v.toString();
            if (v.isDouble()) return QString::number(v.toDouble());
            return "";
        };

        name = getStr("name");
        desc = getStr("desc");
        date = getStr("date");
        price = getStr("price");
        format = getStr("format");
    }

    bool isNameValid() const { return !name.trimmed().isEmpty(); }
    bool isDescValid() const { return !desc.trimmed().isEmpty(); }
    bool isFormatValid() const { return !format.trimmed().isEmpty(); }

    bool isDateValid() const {
        if (date.trimmed().isEmpty()) return false;
        return QDate::fromString(date.trimmed(), "dd.MM.yyyy").isValid();
    }

    bool isPriceValid() const {
        QString p = price.trimmed();
        if (p.isEmpty()) return false;
        p.replace(',', '.');
        bool ok;
        double val = p.toDouble(&ok);
        return ok && val >= 0;
    }

    QStringList getBrokenFields() const {
        QStringList broken;
        if (!isNameValid())   broken << "name";
        if (!isDescValid())   broken << "desc";
        if (!isDateValid())   broken << "date";
        if (!isPriceValid())  broken << "price";
        if (!isFormatValid()) broken << "format";
        return broken;
    }

    bool isValid() const {
        return getBrokenFields().isEmpty();
    }

    QJsonObject toJson() const {
        QJsonObject obj;
        obj["name"] = name.trimmed();
        obj["desc"] = desc.trimmed();
        obj["date"] = date.trimmed();
        obj["format"] = format.trimmed();

        QString p = price.trimmed();
        p.replace(',', '.');
        bool ok;
        double val = p.toDouble(&ok);
        if (ok && val >= 0) {
            obj["price"] = val;
        } else {
            obj["price"] = price.trimmed();
        }
        return obj;
    }
};

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnLoad_clicked();

private:
    Ui::MainWindow *ui;
    void fillTables(const std::vector<Event> &validList, const std::vector<Event> &brokenList);
};

#endif // MAINWINDOW_H
