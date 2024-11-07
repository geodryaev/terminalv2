#ifndef LISTGANSTA_H
#define LISTGANSTA_H

#include <QDebug>
#include <QDialog>
#include <QJsonDocument>
#include <QFile>
#include <QJsonObject>
#include <QJsonArray>
#include <QMap>
#include <QVector>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QDateTime>

namespace Ui {
class listgansta;
}

class listgansta : public QDialog
{
    Q_OBJECT

public:
    explicit listgansta(QWidget *parent = nullptr);
    ~listgansta();

private:
    Ui::listgansta *ui;
    QStandardItemModel model;
};

#endif // LISTGANSTA_H
