#include "dialogfromupdatefiles.h"
#include "ui_dialogfromupdatefiles.h"

dialogfromupdatefiles::dialogfromupdatefiles(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialogfromupdatefiles)
{
    ui->setupUi(this);
    setModal(true);
}

dialogfromupdatefiles::~dialogfromupdatefiles()
{
    delete ui;
}

void dialogfromupdatefiles::on_update_clicked()
{
    QString path = QFileDialog::getOpenFileName(nullptr, "Выберите архив","","Файл архива *.rar");
    if (!path.isEmpty())
    {
        QDir dir;
        if(!dir.exists("fileDir"))
        {
            dir.mkdir("fileDir");
        }
        else
        {
            dir.remove("fileDir");
            dir.mkdir("fileDir");
        }

        QFile::copy(path,"fileDir/update.rar");
    }
}
