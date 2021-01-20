#include "Quit.h"
#include "ui_Quit.h"

Quit::Quit(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Quit)
{
    ui->setupUi(this);
}

Quit::~Quit()
{
    delete ui;
}

void Quit::on_Yes_clicked()
{
    qApp -> quit();
}

void Quit::on_No_clicked()
{
    close();
}
