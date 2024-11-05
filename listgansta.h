#ifndef LISTGANSTA_H
#define LISTGANSTA_H

#include <QDialog>
#include <QJsonDocument>
#include <QFile>

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
};

#endif // LISTGANSTA_H
