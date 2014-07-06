#ifndef LISTGENERATOR_H
#define LISTGENERATOR_H

#include <QMainWindow>

namespace Ui {
class ListGenerator;
}

class ListGenerator : public QMainWindow
{
    Q_OBJECT

public:
    explicit ListGenerator(QWidget *parent = 0);
    ~ListGenerator();

private:
    Ui::ListGenerator *ui;
};

#endif // LISTGENERATOR_H
