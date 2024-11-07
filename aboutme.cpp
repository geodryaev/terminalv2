#include "aboutme.h"
#include "ui_aboutme.h"

aboutMe::aboutMe(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::aboutMe)
{
    ui->setupUi(this);
    setModal(true);
    ui->myimage->setStyleSheet("background-image: url(:/source/photo.jpg);");
    QSettings set("settings.ini", QSettings::IniFormat);
    set.beginGroup("AboutApp");
    ui->version->setText(set.value("Version","ErrorReadSettings").toString());
    ui->creatorname->setText("DjJohnyBoy МПИ ФСБ");
    ui->aboutcreator->setText(set.value("Autor","ErrorReadSettings").toString());
    ui->aboutcreator->setWordWrap(true);
    set.endGroup();
}

aboutMe::~aboutMe()
{
    delete ui;
}
