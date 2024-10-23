#include "QFile"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "passwd.h"

bool passwdCheack()
{
    passwd passwdsCheack;
    passwdsCheack.show();
    passwdsCheack.exec();
    return passwdsCheack.getStatus();
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->showFullScreen();
    this->setWindowModality(Qt::ApplicationModal);
    this->setStyleSheet("background-image: url(:/source/unnamed.jpg); background-repeat: no-repeat; background-position: center;");
    myWidget support;
    if (QFileInfo::exists("settings.ini"))
    {
        support.setDefaultSettings();
    }
    QList<QString> list = support.getListDepartament();

    QStringList qslis;
    QListWidgetItem* item ;
    for (QString strElem : list)
    {
        item  = new QListWidgetItem(strElem, ui->listDepartament);
    }
    ui->listDepartament->setStyleSheet("QListWidget {color: white; font-size: 20px;}");

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_dowloadUP_clicked()
{
    QList <QListWidgetItem *> item = ui->listDepartament->selectedItems();
    if (item.isEmpty())
    {
        QMessageBox::information(nullptr, "Внимание","Вы не выбрали свое подразделение");
    }
    else
    {
        QSettings set("settings.ini", QSettings::IniFormat);
        set.beginGroup("AboutApp");
        QString pathToSave = set.value("pathToSave", "-112").toString();
        if (pathToSave == "-112")
        {
            QMessageBox::information(nullptr, "Ошибка пути", "Нет пути сохранения, обращаемся к админу");
        }
        QFile file("history_dowload.json");
        if (file.open(QIODevice::ReadWrite) | QIODevice::Text)
        {
            QJsonDocument doc ;
            QJsonObject jObj;
            QJsonObject jObjHistory;
            if (file.size()>0)
            {
                file.seek(0);
                QByteArray read = file.readAll();
                doc = QJsonDocument::fromJson(read);
                if (doc.isObject())
                {
                    jObj = doc.object();
                }
            }
            jObjHistory = jObj["history"].toObject();
            jObjHistory [QDateTime::currentDateTime().toString()] = item[0]->text();
            jObj["history"] = jObjHistory;
            doc = QJsonDocument(jObj);
            file.resize(0);
            file.write(doc.toJson());
            file.close();
        }
    }

}

void MainWindow::on_men_updat_triggered()
{
    //    if (passwdCheack())                 ---- заменить
    if (true)
    {
        dialogfromupdatefiles dil;
        dil.show();
        dil.exec();
    }
}

void MainWindow::on_path_to_save_triggered()
{
    if (true)
    {
        dialogsetpathtosave dil;
        dil.show();
        dil.exec();

    }
}

void MainWindow::on_set_default_triggered()
{
    if (true)
    {

    }
}
