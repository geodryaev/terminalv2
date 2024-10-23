#ifndef PASSWD_H
#define PASSWD_H

#include <QDialog>
#include "QVector"
#include "QPair"
#include "QVector"
#include "QMessageBox"

namespace Ui {
class passwd;
}

class passwd : public QDialog
{
    Q_OBJECT

public:
    explicit passwd(QWidget *parent = nullptr);
    ~passwd();

    bool getStatus(){return _result;}
public slots:
    void setResult();
private:
    enum statusPSWD {
        p_first,
        p_second,
        p_third,
    };

    void clearBtn();
    Ui::passwd *ui;
    QVector<QPushButton *> _vbtn;
    bool _result;
    QVector<QPair<int,int>> _send;
    int _countEnter;
    int _status;
};

#endif // PASSWD_H
