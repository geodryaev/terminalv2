#ifndef ABOUTME_H
#define ABOUTME_H

#include <QDialog>
#include <QSettings>

namespace Ui {
class aboutMe;
}

class aboutMe : public QDialog
{
    Q_OBJECT

public:
    explicit aboutMe(QWidget *parent = nullptr);
    ~aboutMe();

private:
    Ui::aboutMe *ui;
};

#endif // ABOUTME_H
