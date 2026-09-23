#include "listgansta.h"
#include "ui_listgansta.h"

listgansta::listgansta(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::listgansta)
{
    ui->setupUi(this);
    setModal(true);

    QMap<QDate, QVector<QString>> arr;

    QFile file("history_dowload.json");
    if (file.open(QIODevice::ReadOnly))
    {
        QJsonDocument docJson = QJsonDocument::fromJson(file.readAll());
        file.close();
        QJsonObject objJson = docJson.object()["history"].toObject();

        for (auto it = objJson.begin(); it != objJson.end(); it++)
        {
            arr[QDateTime::fromMSecsSinceEpoch(it.key().toLongLong()).date()].push_back(it.value().toString());
        }
    }

    model.setHorizontalHeaderLabels({"Название"});
    QStandardItem *rootItem = model.invisibleRootItem();
    // Самые свежие дни сверху
    QMapIterator<QDate, QVector<QString>> i(arr);
    i.toBack();
    while (i.hasPrevious())
    {
        i.previous();
        QStandardItem * parantModel = new QStandardItem(i.key().toString("dd.MM.yyyy ddd"));
        for (const auto &elem : i.value())
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
