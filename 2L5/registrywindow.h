#ifndef REGISTRYWINDOW_H
#define REGISTRYWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QPushButton>
#include <vector>
#include "r_classes.h"

class RegistryWindow : public QMainWindow {
    Q_OBJECT

public:
    RegistryWindow(QWidget* parent = nullptr);
    ~RegistryWindow();

private slots:
    void openDataFile();
    void onRowDoubleClicked(int row, int col);

private:
    QTableWidget* mainTable;
    QPushButton* btnLoad;

    std::vector<R*> recordsList;

    void refreshView();
};

#endif // REGISTRYWINDOW_H
