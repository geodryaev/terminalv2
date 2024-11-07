#include "listgansta.h"
#include "ui_listgansta.h"

listgansta::listgansta(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::listgansta)
{
    ui->setupUi(this);
    setModal(true);

    QMap<QString, QVector<QString>> arr;

    QFile file("history_dowload.json");
    file.open(QIODevice::ReadOnly);
    QByteArray all = file.readAll();
    QJsonDocument docJson = QJsonDocument::fromJson(all);
    QJsonObject objJson = docJson.object();
    objJson = objJson["history"].toObject();




    for (auto it = objJson.begin(); it != objJson.end(); it++)
    {
        arr[QDateTime::fromMSecsSinceEpoch(static_cast<qint64>(it.key().toLongLong())).toString("dd.MM.yyyy ddd")].push_back(it.value().toString());
    }
    file.close();

    model.setHorizontalHeaderLabels({"Название"});
    QStandardItem *rootItem = model.invisibleRootItem();
    for (QMap<QString, QVector<QString>>::iterator i = --arr.end(); i != arr.begin() - 1; i--)
    {
        QStandardItem * parantModel = new QStandardItem(i.key());
        for (auto elem : i.value())
        {
            parantModel->appendRow(new QStandardItem (elem));
        }
        rootItem->appendRow(parantModel);
    }
    ui->treeHistory->setModel(&model);
    ui->treeHistory->setWindowTitle("Список биндитов");

}

listgansta::~listgansta()
{
    delete ui;
}
