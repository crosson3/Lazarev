#ifndef EVENT_H
#define EVENT_H

#include <QString>
#include <QJsonObject>
#include <QDate>

struct Event {
    QString name;
    QString description;
    QString date;
    QString costStr;
    QString format;

    bool isNameValid() const { return !name.trimmed().isEmpty(); }
    bool isDescValid() const { return !description.trimmed().isEmpty(); }
    bool isFormatValid() const { return !format.trimmed().isEmpty(); }

    bool isDateValid() const {
        return QDate::fromString(date.trimmed(), "dd.MM.yyyy").isValid();
    }

    bool isCostValid() const {
        if (costStr.trimmed().isEmpty()) return false;
        bool ok;
        double c = costStr.trimmed().replace(",", ".").toDouble(&ok);
        return ok && c >= 0;
    }

    bool isValid() const {
        return isNameValid() && isDescValid() && isDateValid() && isCostValid() && isFormatValid();
    }

    QJsonObject toJson() const {
        QJsonObject obj;
        obj["name"] = name.trimmed();
        obj["description"] = description.trimmed();
        obj["date"] = date.trimmed();
        obj["cost"] = costStr.trimmed();
        obj["format"] = format.trimmed();
        return obj;
    }

    static Event fromJson(const QJsonObject& obj) {
        Event e;
        e.name = obj["name"].toString();
        e.description = obj["description"].toString();
        e.date = obj["date"].toString();
        e.costStr = obj["cost"].toString();
        e.format = obj["format"].toString();
        return e;
    }
};

#endif
