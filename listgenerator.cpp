#include "listgenerator.h"
#include "ui_listgenerator.h"

ListGenerator::ListGenerator(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ListGenerator)
{
    ui->setupUi(this);
}

ListGenerator::~ListGenerator()
{
    delete ui;
}


