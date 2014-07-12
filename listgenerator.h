#ifndef LISTGENERATOR_H
#define LISTGENERATOR_H

#include <QMainWindow>
#include <QLabel>
#include <QString>
#include <QWidget>
#include <QPushButton>
#include <QSpinBox>
#include <QDebug>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <iostream>

#include "listunit.h"

namespace Ui {
class ListGenerator;
}

class ListGenerator : public QMainWindow
{
    Q_OBJECT

public:
    explicit ListGenerator(QWidget *parent = 0);
    ~ListGenerator();

private slots:
    void updateTableWidget(int num);

private:
    Ui::ListGenerator *ui;
    std::vector<ListUnit> v_ListUnit;

    void createTableWidget();

    void conv_Vector2TableWidget();
    void conv_TableWidget2Vector();
    void writeTableLine(ListUnit listUnit);
    ListUnit readTableLine(int lineNum);

    void readList(std::string file_name, std::vector<ListUnit> &v);
    void printList();

};

#endif // LISTGENERATOR_H
