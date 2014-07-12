#include "listgenerator.h"
#include "ui_listgenerator.h"

ListGenerator::ListGenerator(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ListGenerator)
{
    ui->setupUi(this);

    readList("list.txt", v_ListUnit);

    createTableWidget();

}

ListGenerator::~ListGenerator()
{
    delete ui;
}



void ListGenerator::readList(std::string file_name, std::vector<ListUnit> &v)
{
    std::fstream list_file(file_name.c_str());
    if (!list_file){

        //FIXME: Need a message box!
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

void ListGenerator::createTableWidget()
{
    ui->tableWidget->setRowCount(v_ListUnit.size() + 1);
    conv_Vector2TableWidget();
}


void ListGenerator::conv_Vector2TableWidget()
{

    for (std::vector<ListUnit>::iterator iter = v_ListUnit.begin();
         iter != v_ListUnit.end();
         ++ iter){

        writeTableLine(*iter);

    }

}

void ListGenerator::conv_TableWidget2Vector()
{
    std::vector<ListUnit> v;
    int row = 0;
    while(ui->tableWidget->item(row, 0)){
        v.push_back(readTableLine(row));
        row ++;
    }
    v_ListUnit = v;
}

//FIXME: Reload the whole table when spinbox's value is updated.
//       This is not the best solution.
//       Find a way to changed currentRow of table when value of spinBox is changed.
void ListGenerator::updateTableWidget(int num)
{
    conv_TableWidget2Vector();
    conv_Vector2TableWidget();
}




void ListGenerator::writeTableLine(ListUnit listUnit)
{
    QSpinBox *spinBox = new QSpinBox;
    spinBox->setRange(0, 10000);
    spinBox->setValue(listUnit.quantity);

    connect(spinBox, SIGNAL(valueChanged(int)), this, SLOT(updateTableWidget(int)));

    ui->tableWidget->setItem(listUnit.num - 1, 0,  new QTableWidgetItem(QString::fromLocal8Bit(listUnit.name.c_str())));
    ui->tableWidget->setItem(listUnit.num - 1, 1,  new QTableWidgetItem(QString::fromLocal8Bit(listUnit.standard.c_str())));
//    ui->tableWidget->setItem(listUnit.num - 1, 2,  new QTableWidgetItem(QString::number(listUnit.quantity)));
    ui->tableWidget->setCellWidget(listUnit.num - 1, 2,  spinBox);
    ui->tableWidget->setItem(listUnit.num - 1, 3,  new QTableWidgetItem(QString::number(listUnit.price)));
    ui->tableWidget->setItem(listUnit.num - 1, 4,  new QTableWidgetItem(QString::number(listUnit.totalPrice)));
    ui->tableWidget->setItem(listUnit.num - 1, 5,  new QTableWidgetItem(listUnit.date.toString("yyyy.MM.dd")));

}


ListUnit ListGenerator::readTableLine(int lineNum)
{
    std::string t_name, t_standard;
    int t_num, t_quantity;
    double t_price, t_totalPrice;
    QDate t_date;

    t_num = lineNum + 1;
    t_name = ui->tableWidget->item(lineNum, 0)->text().toLocal8Bit();
    t_standard = ui->tableWidget->item(lineNum, 1)->text().toLocal8Bit();
    t_quantity = static_cast<QSpinBox*>(ui->tableWidget->cellWidget(lineNum, 2))->value();
    t_price = ui->tableWidget->item(lineNum, 3)->text().toDouble();
    t_totalPrice = ui->tableWidget->item(lineNum, 4)->text().toDouble();
    t_date = QDate::fromString(ui->tableWidget->item(lineNum, 5)->text(), "yyyy.MM.dd");

    ListUnit listUnit(t_num, t_name, t_standard, t_quantity, t_price, t_totalPrice, t_date);

    return listUnit;

}






void ListGenerator::printList()
{
    for (std::vector<ListUnit>::iterator iter = v_ListUnit.begin();
         iter != v_ListUnit.end();
         ++ iter)
        iter->printListUnit();
}
