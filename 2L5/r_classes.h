#ifndef R_CLASSES_H
#define R_CLASSES_H

#include <QString>
#include <QWidget>

struct BDate {
    int d;
    int m;
    int y;
};

class R {
public:
    QString surname;
    QString name;
    BDate date;

    virtual ~R() = default;

    virtual bool Craft(QWidget* parent) = 0;
    virtual QString getFullName() const = 0;
    virtual QString getPassContent() const = 0;

    QString getStandardDate() const {
        return QString("%1.%2.%3")
        .arg(date.d, 2, 10, QChar('0'))
            .arg(date.m, 2, 10, QChar('0'))
            .arg(date.y, 4, 10, QChar('0'));
    }
};

class RuP : public R {
public:
    QString patronymic;

    bool Craft(QWidget* parent) override;

    QString getFullName() const override {
        QString pat = (patronymic.isEmpty() || patronymic == "-") ? "-" : patronymic;
        return surname + " " + name + " " + pat;
    }

    QString getPassContent() const override {
        QString pat = (patronymic.isEmpty() || patronymic == "-") ? "" : patronymic + "<br>";
        return QString("<p style='font-size: 16px; line-height: 140%;'>"
                       "<b>%1</b><br>"
                       "<b>%2</b><br>"
                       "%3"
                       "<b>%4</b></p>")
            .arg(surname, name, pat, getStandardDate());
    }
};

class AmP : public R {
public:
    QString middleName;

    bool Craft(QWidget* parent) override;

    QString getFullName() const override {
        QString mid = (middleName.isEmpty() || middleName == "-") ? "" : middleName + " ";
        return name + " " + mid + surname;
    }

    QString getPassContent() const override {
        QString amDate = QString("%1-%2-%3")
        .arg(date.m, 2, 10, QChar('0'))
            .arg(date.d, 2, 10, QChar('0'))
            .arg(date.y, 4, 10, QChar('0'));

        QString mid = (middleName.isEmpty() || middleName == "-") ? "" : "<b>" + middleName + "</b><br>";

        return QString("<p style='font-size: 16px; line-height: 140%;'>"
                       "<b>%1</b><br>"
                       "%2"
                       "<b>%3</b><br><br>"
                       "<b>%4</b></p>")
            .arg(name, mid, surname, amDate);
    }
};

#endif // R_CLASSES_H
