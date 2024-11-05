#include "listgansta.h"
#include "ui_listgansta.h"

listgansta::listgansta(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::listgansta)
{
    ui->setupUi(this);
    setModal(true);
    QFile file("data_list.json");
    QByteArray all = file.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(all);


}

listgansta::~listgansta()
{
    delete ui;
}
