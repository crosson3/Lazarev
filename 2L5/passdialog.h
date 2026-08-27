#ifndef PASSDIALOG_H
#define PASSDIALOG_H

#include <QDialog>

class PassDialog : public QDialog {
    Q_OBJECT
public:
    explicit PassDialog(const QString& infoHtml, QWidget *parent = nullptr);
};

#endif // PASSDIALOG_H
