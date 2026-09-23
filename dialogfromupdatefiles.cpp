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
    QString path = QFileDialog::getOpenFileName(nullptr, "Выберите архив","","Файл архива *.zip");
    if (path.isEmpty())
    {
        return;
    }

    const QString target = "fileDir/update.zip";
    const QString tmp = target + ".tmp";

    QDir().mkpath("fileDir");
    QFile::remove(tmp);
    // QFile::copy не перезаписывает файлы, поэтому копируем во временный и подменяем
    if (!QFile::copy(path, tmp) || (QFile::exists(target) && !QFile::remove(target)) || !QFile::rename(tmp, target))
    {
        QFile::remove(tmp);
        QMessageBox::warning(nullptr, "Ошибка", "Не удалось скопировать архив обновления");
        return;
    }

    QSettings set ("settings.ini", QSettings::IniFormat);
    set.beginGroup("UpdateInfo");
    set.setValue("date", QDateTime::currentDateTime());
    set.setValue("size", QFileInfo(target).size());
    set.endGroup();
    set.sync();

    emit changeData();
    QMessageBox::information(nullptr, "Внимание", "Архив обновления загружен");
}
