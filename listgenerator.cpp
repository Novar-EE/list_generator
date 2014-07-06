#include "listgenerator.h"
#include "ui_listgenerator.h"

ListGenerator::ListGenerator(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ListGenerator)
{
    ui->setupUi(this);

    readList("list.txt", v_ListUnit);
    convVector2TableWidget();

}

ListGenerator::~ListGenerator()
{
    delete ui;
}



void ListGenerator::readList(std::string file_name, std::vector<ListUnit> &v)
{
    std::fstream list_file(file_name.c_str());
    if (!list_file){

        qDebug() << "No file!";

    }

    std::string file_line;
    int num = 1;
    while(std::getline(list_file, file_line)){
        std::stringstream line_stream;
        line_stream << file_line;
        std::string name, standard, price;
        line_stream >> name >> standard >> price;
        ListUnit listUnit(num, name, standard, 0, std::atof(price.c_str()), 0.0);

        v.push_back(listUnit);

        num ++;
    }

}


void ListGenerator::convVector2TableWidget()
{
    ui->tableWidget->setRowCount(v_ListUnit.size() + 1);

    for (std::vector<ListUnit>::iterator iter = v_ListUnit.begin();
         iter != v_ListUnit.end();
         ++ iter){

        writeTableLine(*iter);

    }

}


void ListGenerator::writeTableLine(ListUnit listUnit)
{

    ui->tableWidget->setItem(listUnit.num - 1, 0,  new QTableWidgetItem(QString::fromLocal8Bit(listUnit.name.c_str())));
    ui->tableWidget->setItem(listUnit.num - 1, 1,  new QTableWidgetItem(QString::fromLocal8Bit(listUnit.standard.c_str())));
    ui->tableWidget->setItem(listUnit.num - 1, 2,  new QTableWidgetItem(QString::number(listUnit.quantity)));
    ui->tableWidget->setItem(listUnit.num - 1, 3,  new QTableWidgetItem(QString::number(listUnit.price)));
    ui->tableWidget->setItem(listUnit.num - 1, 4,  new QTableWidgetItem(QString::number(listUnit.totalPrice)));
    ui->tableWidget->setItem(listUnit.num - 1, 5,  new QTableWidgetItem(listUnit.date.toString("yyyy.MM.dd")));

}
