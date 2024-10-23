#include "dialogsetpathtosave.h"
#include "ui_dialogsetpathtosave.h"

dialogsetpathtosave::dialogsetpathtosave(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialogsetpathtosave)
{
    ui->setupUi(this);
}

dialogsetpathtosave::~dialogsetpathtosave()
{
    delete ui;
}

void dialogsetpathtosave::on_pushButton_clicked()
{
    QString path = QFileDialog::getExistingDirectory(nullptr,"Выберите носитель для записи","",QFileDialog::ShowDirsOnly);
    QSettings set ("settings.ini", QSettings::IniFormat);
    set.beginGroup("AboutApp");
    set.setValue("pathToSave", path[0] + ":\\");
    set.endGroup();
    set.sync();

}
