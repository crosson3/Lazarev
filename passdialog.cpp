#include "passdialog.h"
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QPainter>
#include <QPixmap>

PassDialog::PassDialog(const QString& infoHtml, QWidget *parent) : QDialog(parent) {
    setWindowTitle("Карточка пропуска");
    setFixedSize(380, 220);
    setStyleSheet("background-color: #ffffff; color: #222;");

    QGridLayout* grid = new QGridLayout(this);

    QLabel* photoBox = new QLabel(this);
    photoBox->setFixedSize(120, 140);
    photoBox->setStyleSheet("border: 2px solid #333; background: #fafafa;");
    photoBox->setAlignment(Qt::AlignCenter);

    QPixmap avatar(120, 140);
    avatar.fill(Qt::transparent);
    QPainter painter(&avatar);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(QPen(Qt::black, 3));
    painter.drawEllipse(45, 25, 30, 30); // Голова
    painter.drawArc(20, 65, 80, 80, 30 * 16, 120 * 16); // Плечи
    painter.end();
    photoBox->setPixmap(avatar);

    QLabel* textData = new QLabel(infoHtml, this);
    textData->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

    QPushButton* printBtn = new QPushButton("Печать", this);
    QPushButton* cancelBtn = new QPushButton("Отмена", this);

    printBtn->setStyleSheet("background-color: #0099ff; color: white; padding: 6px 15px; font-weight: bold; border: 2px solid black;");
    cancelBtn->setStyleSheet("background-color: #ff3333; color: white; padding: 6px 15px; font-weight: bold; border: 2px solid black;");

    grid->addWidget(photoBox, 0, 0, 1, 1);
    grid->addWidget(textData, 0, 1, 1, 2);
    grid->addWidget(printBtn, 1, 1, Qt::AlignBottom);
    grid->addWidget(cancelBtn, 1, 2, Qt::AlignBottom);

    connect(printBtn, &QPushButton::clicked, this, &QDialog::accept);
    connect(cancelBtn, &QPushButton::clicked, this, &QDialog::reject);
}
