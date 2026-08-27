#include "r_classes.h"
#include "passdialog.h"

bool RuP::Craft(QWidget* parent) {
    PassDialog dialog(this->getPassContent(), parent);
    return dialog.exec() == QDialog::Accepted;
}

bool AmP::Craft(QWidget* parent) {
    PassDialog dialog(this->getPassContent(), parent);
    return dialog.exec() == QDialog::Accepted;
}
